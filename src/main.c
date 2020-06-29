/*
 * main.c
 *
 *  Created on: June, 16, 2020
 *      Author: Islam Ehab
 */

#include "main.h"
#include <stdint.h>

#define BL_DEBUG_MSG_ENG
#define BL_RX_LEN  200

USART_Config husart1;
GPIO_PIN_INIT hgpio = {0};

u8 Supported_Commands[] = {
		BL_GET_VER,
		BL_GET_HELP,
		BL_GET_CID,
		BL_GET_RDP_STATUS,
		BL_GO_TO_ADDR,
		BL_FLASH_ERASE,
		BL_MEM_WRITE,
		BL_READ_SECTOR_P_STATUS,
		BL_OTP_READ,
		BL_DIS_R_W_PROTECT,
		BL_FLASH_MASS_ERASE };

u8 BL_Rx_Buffer[BL_RX_LEN];
extern volatile u32 DELAY_X;

static void Hardware_Init(void);
static void GPIO_Peripheral_Configuration(void);
static void USART1_Configuration(void);
void Test_Button_LEDs(void);
void printmsg(char* format, ...);
void Hardware_RegInit(void)
{
	vidCRC_InitReg();
	vidUSART_InitReg(USART1);
	vidGPIO_Init_Reg();
	vidRCC_RegInit();
	vidSysTick_Reset();
}







int main(void)
{

	Hardware_Init();
	GPIO_Peripheral_Configuration();
	USART1_Configuration();



	printmsg("Hello From Test App!! \r\n");


	if(u8GPIO_GetPinValue(GPIOA, PIN0) == GPIO_VALUE_SET)
	{
		printmsg("BL DEBUG MSG: Buttonb is pressed, Going to BL Mood \n\r");


		vidGPIO_SetPinValue(GPIOG, PIN13, GPIO_VALUE_SET);
		_delay_ms(1000);
        vidGPIO_SetPinValue(GPIOG, PIN13, GPIO_VALUE_RESET);
		_delay_ms(1000);

        vidGPIO_SetPinValue(GPIOG, PIN13, GPIO_VALUE_SET);



		Bootloader_UART_Read_Data();

	}

	else
	{
		printmsg("BL DEBUG MSG: Button is NOT Pressed, Go to user code \n\r");

        vidGPIO_SetPinValue(GPIOG, PIN14, GPIO_VALUE_SET);
		_delay_ms(1000);
        vidGPIO_SetPinValue(GPIOG, PIN14, GPIO_VALUE_RESET);
		_delay_ms(1000);


		Bootloader_Jump_To_User_Application();


	}

}

/**
  * @brief  BootLoader Instruction Selection
  * 		Receives the instruction from the host (PC Python code)
  * 		and then start execute it
  * @Param  None
  * @retval None
**/
void Bootloader_UART_Read_Data(void)
{
	u8 Rx_Length = 0;
	while(1)
	{
		/* Clear the Buffer */
		memset(BL_Rx_Buffer, 0, 200);

		/* Read the First byte (Command Length) */

		vidUSART_Receive(USART1, &husart1, &BL_Rx_Buffer[0], 1);

		Rx_Length = BL_Rx_Buffer[0];


		vidUSART_Receive(USART1, &husart1, &BL_Rx_Buffer[1], Rx_Length);

		/* Conditional Statment for command */
		switch(BL_Rx_Buffer[1])
		{
		case BL_GET_VER:
			BootLoader_Handle_GetVer_CMD(BL_Rx_Buffer);
			break;

		case BL_GET_HELP:
			BootLoader_Handle_GetHelp_CMD(BL_Rx_Buffer);
			break;

		case BL_GET_CID:
			BootLoader_Handle_GetCID_CMD(BL_Rx_Buffer);
			break;

		case BL_GET_RDP_STATUS:
			BootLoader_Handle_GetRDP_CMD(BL_Rx_Buffer);
			break;

		case BL_GO_TO_ADDR:
			BootLoader_Handle_Go_CMD(BL_Rx_Buffer);
			break;

		case BL_FLASH_ERASE:
			BootLoader_Handle_Flash_Erase_CMD(BL_Rx_Buffer);
			break;

		case BL_MEM_WRITE:
			BootLoader_Handle_Mem_Write_CMD(BL_Rx_Buffer);
			break;

		case BL_EN_RW_PROTECT:
			BootLoader_Handle_Enable_RW_Protection(BL_Rx_Buffer);
			break;

		case BL_MEM_READ:
			BootLoader_Handle_Mem_Read(BL_Rx_Buffer);
			break;

		case BL_READ_SECTOR_P_STATUS:
			BootLoader_Handle_Read_Sector_Status(BL_Rx_Buffer);
			break;

		case BL_OTP_READ:
			BootLoader_Handle_Read_OTP(BL_Rx_Buffer);
			break;

		case BL_DIS_R_W_PROTECT:
			BootLoader_Handle_Disable_RW_Protection(BL_Rx_Buffer);
			break;

		case BL_FLASH_MASS_ERASE:
			BootLoader_Handle_Flash_Mass_Erase_CMD(BL_Rx_Buffer);
			break;

		default:
			printmsg("BL_DEBUG_MSG: Invalid Command \n");
			break;
		}

	}
}

/**
  * @brief  Jump to user app if the user button not pressed
  * @Param  None
  * @retval None
**/
void Bootloader_Jump_To_User_Application(void)
{
	/* Function Pointer to Hold the Address of Reset Handler of User Application */
	void (*App_Reset_Handler)(void);


	printmsg("BL_DEBUG_MSG: Bootloader_Jumb_To_User_Application \n");

	/* Configure the MSP by Reading the value of the sector 2 base address */
	uint32_t MSP_Address = *(volatile uint32_t*)SECTOR2_BASE_ADDRESS;
	printmsg("BL_DEBUG_MSG: MSP Value = %#x\n",MSP_Address);


	__set_MSP(MSP_Address);

	/* Fetch the reset handler address of user application
	 * From Location SECTOR2_BASE_ADDRESS + 4
	 */
	uint32_t ResetHandler_Address = *(volatile uint32_t*)(SECTOR2_BASE_ADDRESS + 4);

	/* Assign the ResetHandler address of user application
	 * To Function Pointer
	 */
	App_Reset_Handler = (void*) ResetHandler_Address;
	printmsg("BL_DEBUG_MSG: User Application Reset Handler Value = %#x\n",ResetHandler_Address);


	/* Jump to Reset Handler Address of User Application By Calling the Function*/
	App_Reset_Handler();
}



/**
  * @brief Print message using USART Terminal
  * @param pointer to user message
  * @retval None
  */
void printmsg(char* format, ...)
{
#ifdef BL_DEBUG_MSG_EN
char str[80];

va_list args;
va_start(args, format);
vsprintf(str, format, args);
//HAL_UART_Transmit(&huart1, str, sizeof(str), HAL_MAX_DELAY);
vidUSART_SendString(USART1,(u8*) str,strlen(str));

va_end(args);


#endif
}

/**
  * @brief Hardware Initialization Function
  * @param None
  * @retval None
  */
static void Hardware_Init(void)
{
	//vidRCC_RegInit();
	vidRCC_Init();
	vidNVIC_Init();

	vidSYSTICK_Init(89999);
	vidRCC_EnableClock(RCC_CRC);
	vidRCC_EnableClock(RCC_GPIOA);
	vidRCC_EnableClock(RCC_GPIOG);
	vidRCC_EnableClock(RCC_GPIOD);
	vidRCC_EnableClock(RCC_USART1);
	vidRCC_EnableClock(RCC_USART2);
	vidRCC_EnableClock(RCC_DMA2E);

	vidGPIO_Init_Reg();


}

/**
  * @brief 	GPIO Peripherals Initialization Function
  * @param 	None
  * @retval None
  */
static void GPIO_Peripheral_Configuration(void)
{

	/* USART1 Config */
	hgpio.GPIO_PIN    	= (PIN9);
	hgpio.GPIO_MODE   	= GPIO_MODE_AF;
	hgpio.GPIO_OUT	  	= GPIO_OUT_PP;
	hgpio.GPIO_SPEED  	= GPIO_SPEED_ULTRA;
	hgpio.GPIO_PULL   	= GPIO_PULL_NO;

	vidGPIO_Init(GPIOA,&hgpio);
	vidGPIO_AlternateFunction(GPIOA,(PIN9),AF7);

	hgpio.GPIO_PIN		= PIN10;
	hgpio.GPIO_MODE		= GPIO_MODE_AF;
	hgpio.GPIO_OUT		= GPIO_OUT_PP;
	hgpio.GPIO_SPEED	= GPIO_SPEED_ULTRA;
	hgpio.GPIO_PULL		= GPIO_PULL_NO;

	vidGPIO_Init(GPIOA, &hgpio);
	vidGPIO_AlternateFunction(GPIOA,PIN10,AF7);


	/* Configuration for PushButton PA0 */
	hgpio.GPIO_PIN		= PIN0;
	hgpio.GPIO_MODE		= GPIO_MODE_IN;
	hgpio.GPIO_PULL		= GPIO_PULL_DOWN;
	hgpio.GPIO_OUT		= 0;
	hgpio.GPIO_SPEED	= GPIO_SPEED_LOW;

	vidGPIO_Init(GPIOA, &hgpio);

	 /* Configuration for LEDs PG13, PG14 */
	hgpio.GPIO_PIN		= PIN13;
	hgpio.GPIO_MODE		= GPIO_MODE_GPO;
	hgpio.GPIO_OUT		= GPIO_OUT_PP;
	hgpio.GPIO_PULL		= GPIO_PULL_NO;
	hgpio.GPIO_SPEED	= GPIO_SPEED_HIGH;
	vidGPIO_Init(GPIOG,&hgpio);

	hgpio.GPIO_PIN		= PIN14;
	vidGPIO_Init(GPIOG,&hgpio);


}

/**
  * @brief 	USART1 Configuration Initialization Function
  * @param 	None
  * @retval None
  */
static void USART1_Configuration(void)
{

	husart1.Parity   		= NO;
	husart1.OverSampling	= NO;
	husart1.WordLength 		= Data_Bits_8;
	husart1.StopBit			= One_Bit;
	husart1.Mode			= (Receiver | Transmitter);
	husart1.BaudRate 		= BR115200;

	vidUSART_Init(USART1, &husart1);


}

/******************* BootLoader APIs Implementation ********************/

/**
 * @brief Read the BootLoader Version on the MCU
 * @Param  Pointer to Received data from Host
 * @retval Bootloader Version Number (1 Byte)
**/
void BootLoader_Handle_GetVer_CMD(u8 *pBuffer)
{

	u8 BL_Version;


	/* Verify CheckSum */
	printmsg("BL_DEBUG_MSG: BootLoader Handler Get Version \n");

	/* Total Length of the Command Line */
	u32 Command_Packet_Len = BL_Rx_Buffer[0]+1;

	/* Extract the CRC from Host */
	u32 Host_CRC = *((u32 *)(BL_Rx_Buffer+Command_Packet_Len - 4) );

	if(! BootLoader_Verify_CRC(&BL_Rx_Buffer[0], Command_Packet_Len - 4, Host_CRC))
	{
		printmsg("BL_DEBUG_MSG: CheckSum Sucess \n");

		/* Used to send the Command size to C / Python Script
		 * In Host device
		 */
		BootLoader_Send_ACK(pBuffer[0], 1);

		BL_Version = Get_BootLoader_Version();
		printmsg("BL_DEBUG_MSG: BL Version: %d %#x\n", BL_Version, BL_Version);
		BootLoader_UART_Write_Data(&BL_Version, 1);
	}

	/* CRC Not Correct */
	else
	{
		printmsg("BL_DEBUG_MSG: CheckSum Fail !!\n");
		BootLoader_Send_NACK();
	}


}

/**
 * @brief Know what are the Supported Commands
 * @Param  Pointer to Received data from Host
 * @retval All Supported Commands (10 Bytes)
**/
void BootLoader_Handle_GetHelp_CMD(u8 *pBuffer)
{
	printmsg("BL_DEBUG_MSG: BootLoader_Handle_GetHelp_CMD \n");

	/* Total Length of the Command Line */
	u32 Command_Packet_Len = BL_Rx_Buffer[0]+1;

	/* Extract the CRC from Host */
	u32 Host_CRC = *((u32 *) (BL_Rx_Buffer + Command_Packet_Len - 4) );

	if(! BootLoader_Verify_CRC(&BL_Rx_Buffer[0], Command_Packet_Len - 4, Host_CRC))
	{
		printmsg("BL_DEBUG_MSG: CheckSum Sucess \n");

		/* Used to send the Command size to C / Python Script
		 * In Host device
		 */
		BootLoader_Send_ACK(pBuffer[0], sizeof(Supported_Commands));
		BootLoader_UART_Write_Data(Supported_Commands, sizeof(Supported_Commands));
	}
	else{
		printmsg("BL_DEBUG_MSG: CheckSum Failed /n");
		BootLoader_Send_NACK();
	}
}

/**
 * @brief Read The MCU Chip ID Number
 * @Param  Pointer to Received data from Host
 * @retval Chip ID Number (2 Bytes)
 */
void BootLoader_Handle_GetCID_CMD(u8 *pBuffer)
{
	u16 C_ID = 0;
	printmsg("BL_DEBUG_MSG: BootLoader_Handle_GetCID_CMD \n");

	/* Total Length of the Command Line */
	u32 Command_Packet_Len = BL_Rx_Buffer[0]+1;

	/* Extract the CRC from Host */
	u32 Host_CRC = *((u32 *) (BL_Rx_Buffer + Command_Packet_Len - 4) );

	if(! BootLoader_Verify_CRC(&BL_Rx_Buffer[0], Command_Packet_Len - 4, Host_CRC))
	{
		printmsg("BL_DEBUG_MSG: CheckSum Sucess \n");

		/* Used to send the Command size to C / Python Script
		 * In Host device
		 */
		BootLoader_Send_ACK(pBuffer[0], 2);
		C_ID = Get_MCU_CID();
		printmsg("BL_DEBUG_MSG:MCU id : %d %#x !!\n",C_ID, C_ID);

		BootLoader_UART_Write_Data((u8* )&C_ID, 2);
	}
	else{
		printmsg("BL_DEBUG_MSG: CheckSum Failed /n");
		BootLoader_Send_NACK();
	}
}

/**
 * @brief Read the FLASH Protection Level
 * @Param  Pointer to Received data from Host
 * @retval Flash Protection Level (1 Byte)
 */
void BootLoader_Handle_GetRDP_CMD(u8 *pBuffer)
{
	u8 RDP_Value = 0;
	printmsg("BL_DEBUG_MSG: BootLoader_Handle_GetRDP_CMDD \n");

	/* Total Length of the Command Line */
	u32 Command_Packet_Len = BL_Rx_Buffer[0]+1;

	/* Extract the CRC from Host */
	u32 Host_CRC = *((u32 *) (BL_Rx_Buffer + Command_Packet_Len - 4) );

	if(! BootLoader_Verify_CRC(&BL_Rx_Buffer[0], Command_Packet_Len - 4, Host_CRC))
	{
		printmsg("BL_DEBUG_MSG: CheckSum Sucess \n");

		/* Used to send the Command size to C / Python Script
		 * In Host device
		 */
		BootLoader_Send_ACK(pBuffer[0], 1);
		RDP_Value = Get_Flash_RDP_Level();
		printmsg("BL_DEBUG_MSG:MCU id : %d %#x !!\n",RDP_Value, RDP_Value);

		BootLoader_UART_Write_Data(&RDP_Value, 1);
	}
	else{
		printmsg("BL_DEBUG_MSG: CheckSum Failed /n");
		BootLoader_Send_NACK();
	}
}

/**
 * @brief Jump Bootloader to Specrific Address
 * @Param  Pointer to Received data from Host
 * @retval Success or Fail (1 Byte)
**/
void BootLoader_Handle_Go_CMD(u8 *pBuffer)
{
	u32 Go_Address = 0;
	u8 Address_Valid 	= ADDRESS_VALID;
	u8 Address_Invalid	= ADDRESS_INVALID;
	void (*Jump_to_Address)(void);

	printmsg("BL_DEBUG_MSG: BootLoader_Handle_Go_CMD \n");
	/* Total Length of the Command Line */
	u32 Command_Packet_Len = BL_Rx_Buffer[0]+1;

	/* Extract the CRC from Host */
	u32 Host_CRC = *((u32 *) (BL_Rx_Buffer + Command_Packet_Len - 4) );

	if(! BootLoader_Verify_CRC(&BL_Rx_Buffer[0], Command_Packet_Len - 4, Host_CRC))
	{
		printmsg("BL_DEBUG_MSG: CheckSum Sucess \n");

		/* Used to send the Command size to C / Python Script
		 * In Host device
		 */
		BootLoader_Send_ACK(pBuffer[0], 1);

		/* Extract Go to Address From Host Application */
		Go_Address = *((volatile u32*)&pBuffer[2] );
		printmsg("BL_DEBUG_MSG:GO addr: %#x\n",Go_Address);

		/* Check the address if it's valid or not
		 * (Not an OTP address or Peripheral Address )
		 */

		if( (Verify_Address(Go_Address) == ADDRESS_VALID))
		{
			/* Send 0x01 to host which is Valid Address Acknowledgment */
			BootLoader_UART_Write_Data(&Address_Valid, 1);


			u32 ResetHandler_Address = *(volatile u32*)(Go_Address + 4);

			/* Pointer to void Function to go to that address */
			Jump_to_Address = (void*)(ResetHandler_Address);

			printmsg("BL_DEBUG_MSG: jumping to go address! \n");

			/* Jump to User Application (Go_Address) */

			/* Disable IRQ */
			asm("MOV R0,#1");
			asm("MSR PRIMASK,R0");
			Jump_to_Address();
		}
		else
	{
		printmsg("BL_DEBUG_MSG:GO addr invalid ! \n");
		/* Send 0x00 to host which is Invalid Address Acknowledgment */
		BootLoader_UART_Write_Data(&Address_Invalid, 1);

	}


	}
	else{
		printmsg("BL_DEBUG_MSG: CheckSum Failed /n");
		BootLoader_Send_NACK();

	}
}

void BootLoader_Handle_Flash_Mass_Erase_CMD(u8 *pBuffer)
{
	u8 Erase_Status = 0;

	printmsg("BL_DEBUG_MSG: BootLoader_Handle_Flash_Mass_Erase_CMD \n");
	/* Total Length of the Command Line */
	u32 Command_Packet_Len = BL_Rx_Buffer[0]+1;

	/* Extract the CRC from Host */
	u32 Host_CRC = *((u32 *) (BL_Rx_Buffer + Command_Packet_Len - 4) );

	if(! BootLoader_Verify_CRC(&BL_Rx_Buffer[0], Command_Packet_Len - 4, Host_CRC))
	{
		printmsg("BL_DEBUG_MSG: CheckSum Sucess \n");

		/* Used to send the Command size to C / Python Script
		 * In Host device
		 */
		BootLoader_Send_ACK(pBuffer[0], 1);
		printmsg("BL_DEBUG_MSG:initial_sector : %d  no_ofsectors: %d\n",pBuffer[2],pBuffer[3]);

		vidGPIO_SetPinValue(GPIOG, PIN14, GPIO_VALUE_SET);
		Erase_Status = Execute_Flash_Mass_Erase();
		printmsg("BL_DEBUG_MSG: flash erase status: %#x\n",Erase_Status);
		vidGPIO_SetPinValue(GPIOG, PIN14, GPIO_VALUE_RESET);

		BootLoader_UART_Write_Data(&Erase_Status, 1);
	}

	else
	{
		printmsg("BL_DEBUG_MSG: CheckSum Failed /n");
		BootLoader_Send_NACK();

	}
}

/**
 * @brief Mass Erase or Sector Erase of user FLASH
 * @Param  Pointer to Received data from Host
 * @retval Success or Fail (1 Byte)
**/
void BootLoader_Handle_Flash_Erase_CMD(u8 *pBuffer)
	{

		u8 Erase_Status = 0;

		printmsg("BL_DEBUG_MSG: BootLoader_Handle_Flash_Erase_CMD \n");
		/* Total Length of the Command Line */
		u32 Command_Packet_Len = BL_Rx_Buffer[0]+1;

		/* Extract the CRC from Host */
		u32 Host_CRC = *((u32 *) (BL_Rx_Buffer + Command_Packet_Len - 4) );

		if(! BootLoader_Verify_CRC(&BL_Rx_Buffer[0], Command_Packet_Len - 4, Host_CRC))
		{
			printmsg("BL_DEBUG_MSG: CheckSum Sucess \n");

			/* Used to send the Command size to C / Python Script
			 * In Host device
			 */
			BootLoader_Send_ACK(pBuffer[0], 1);
	        printmsg("BL_DEBUG_MSG:initial_sector : %d  no_ofsectors: %d\n",pBuffer[2],pBuffer[3]);

	        vidGPIO_SetPinValue(GPIOG, PIN14, GPIO_VALUE_SET);
			Erase_Status = Execute_Flash_Erase(pBuffer[2], pBuffer[3]);
	        printmsg("BL_DEBUG_MSG: flash erase status: %#x\n",Erase_Status);
	        vidGPIO_SetPinValue(GPIOG, PIN14, GPIO_VALUE_RESET);


	        BootLoader_UART_Write_Data(&Erase_Status, 1);
		}
		else
		{
			printmsg("BL_DEBUG_MSG: CheckSum Failed /n");
			BootLoader_Send_NACK();

		}
	}

/**
 * @brief 	Write Data into Different Memory types of MCU
 * 			Like (SRAM1, SRAM2, etc)
 * @Param  Pointer to Received data from Host
 * @retval 	Success or Fail (1 Byte)
**/
void BootLoader_Handle_Mem_Write_CMD(u8 *pBuffer)
{
	u8  Write_Status 		= 0x00;

	u8	 Payload_Len		= pBuffer[6];
	u32 Mem_Address		= *((u32*) (&pBuffer[2]) );


	printmsg("BL_DEBUG_MSG: BootLoader_Handle_Mem_Write_CMD \n");
	/* Total Length of the Command Line */
	u32 Command_Packet_Len = BL_Rx_Buffer[0]+1;

	/* Extract the CRC from Host */
	u32 Host_CRC = *((u32 *) (BL_Rx_Buffer + Command_Packet_Len - 4) );

	if(! BootLoader_Verify_CRC(&BL_Rx_Buffer[0], Command_Packet_Len - 4, Host_CRC))
	{
		printmsg("BL_DEBUG_MSG: CheckSum Sucess \n");

		/* Used to send the Command size to C / Python Script
		 * In Host device
		 */
		BootLoader_Send_ACK(pBuffer[0], 1);
		printmsg("BL_DEBUG_MSG: mem write address : %#x\n",Mem_Address);

		if(Verify_Address(Mem_Address) == ADDRESS_VALID)
		{
			printmsg("BL_DEBUG_MSG: valid mem write address\n");

			vidGPIO_SetPinValue(GPIOG, PIN14, GPIO_VALUE_SET);

			Write_Status = Execute_Mem_Write(&pBuffer[7], Mem_Address, Payload_Len);

			printmsg("BL_DEBUG_MSG: flash erase status: %#x\n",Write_Status);

			vidGPIO_SetPinValue(GPIOG, PIN14, GPIO_VALUE_RESET);

			BootLoader_UART_Write_Data(&Write_Status, 1);

		}

		else
		{
			printmsg("BL_DEBUG_MSG: Invalid Mem_Write Address \n");
			Write_Status = ADDRESS_INVALID;
			BootLoader_UART_Write_Data(&Write_Status, 1);
		}

	}
	else
	{
		printmsg("BL_DEBUG_MSG: CheckSum Failed /n");
		BootLoader_Send_NACK();
	}

}

/**
 * @brief  Enable or Disable Read/Write Protection on Different Sectors on FLASH
 * @Param  Pointer to Received data from Host
 * @retval Success or Fail (1 Byte)
**/
void BootLoader_Handle_Enable_RW_Protection(u8 *pBuffer)
{
	u8 Status = 0;

	printmsg("BL_DEBUG_MSG: BootLoader_Handle_Flash_Erase_CMD \n");
	/* Total Length of the Command Line */
	u32 Command_Packet_Len = BL_Rx_Buffer[0]+1;

	/* Extract the CRC from Host */
	u32 Host_CRC = *((u32 *) (BL_Rx_Buffer + Command_Packet_Len - 4) );

	if(! BootLoader_Verify_CRC(&BL_Rx_Buffer[0], Command_Packet_Len - 4, Host_CRC))
	{
		printmsg("BL_DEBUG_MSG: CheckSum Sucess \n");

		/* Used to send the Command size to C / Python Script
		 * In Host device
		*/
		BootLoader_Send_ACK(pBuffer[0], 1);
		Status = Config_Flash_Sector_RW_Protection(pBuffer[2], pBuffer[3], 0);
        printmsg("BL_DEBUG_MSG: flash erase status: %#x\n",Status);

        BootLoader_UART_Write_Data(&Status, 1);
	}
	else
	{
		printmsg("BL_DEBUG_MSG: CheckSum Failed /n");
		BootLoader_Send_NACK();
	}

}

/**
 * @brief  Read the FLASH
 * @Param  Pointer to Received data from Host
 * @retval Memory Content of Desired Host Length
**/
void BootLoader_Handle_Mem_Read(u8 *pBuffer)
{
	volatile u32 Address = 0;
	u32 Val = 0;
	u32 ReadLength = 0;

	printmsg("BL_DEBUG_MSG: BootLoader_Handle_Flash_Mass_Erase_CMD \n");
	/* Total Length of the Command Line */
	u32 Command_Packet_Len = BL_Rx_Buffer[0]+1;
	ReadLength = BL_Rx_Buffer[6];

	/* Extract the CRC from Host */
	u32 Host_CRC = *((u32 *) (BL_Rx_Buffer + Command_Packet_Len - 4) );

	if(! BootLoader_Verify_CRC(&BL_Rx_Buffer[0], Command_Packet_Len - 4, Host_CRC))
	{
		printmsg("BL_DEBUG_MSG: CheckSum Sucess \n");

		/* Used to send the Command size to C / Python Script
		 * In Host device
		 */
		BootLoader_Send_ACK(pBuffer[0], ReadLength + 1);

		FLASH_Unlock_Sequence();

		Address = *(u32 *) &BL_Rx_Buffer[10];

		Val = *(u32 *)Address;

		BootLoader_UART_Write_Data((u8*) &Val, ReadLength + 1);
	}
	else{
		printmsg("BL_DEBUG_MSG: CheckSum Failed /n");
		BootLoader_Send_NACK();
	}

}

/**
  * @brief  Read All Sectores Protection Status
  * @Param  Pointer to Received data from Host
  * @retval ALl Sectors Status (2 Bytes)
**/
void BootLoader_Handle_Read_Sector_Status(u8 *pBuffer)
{
	u32 Status = 0;

	printmsg("BL_DEBUG_MSG: BootLoader_Handle_Flash_Erase_CMD \n");
	/* Total Length of the Command Line */
	u32 Command_Packet_Len = BL_Rx_Buffer[0]+1;

	/* Extract the CRC from Host */
	u32 Host_CRC = *((u32 *) (BL_Rx_Buffer + Command_Packet_Len - 4) );

	if(! BootLoader_Verify_CRC(&BL_Rx_Buffer[0], Command_Packet_Len - 4, Host_CRC))
	{
		printmsg("BL_DEBUG_MSG: CheckSum Sucess \n");

		/* Used to send the Command size to C / Python Script
		 * In Host device
		*/
		BootLoader_Send_ACK(pBuffer[0], 4);

		Status = Read_OptionByte_Protection_Status();
        printmsg("BL_DEBUG_MSG: nWRP status: %#x\n",Status);
        BootLoader_UART_Write_Data((u8*)&Status, 4);

	}
	else
	{
		printmsg("BL_DEBUG_MSG: CheckSum Failed /n");
		BootLoader_Send_NACK();
	}
}

/**
  * @brief  Read the OTP Content
  * @Param  Pointer to Received data from Host
  * @retval OTP Content
**/
void BootLoader_Handle_Read_OTP(u8 *pBuffer)
{

}

/**
  * @brief  Disable Read Write Protection
  * @Param  Pointer to Received data from Host
  * @retval void
**/
void BootLoader_Handle_Disable_RW_Protection(u8 *pBuffer)
{
	u8 Status = 0;

	printmsg("BL_DEBUG_MSG: BootLoader_Handle_Disable_RW_Protetction_CMD \n");
	/* Total Length of the Command Line */
	u32 Command_Packet_Len = BL_Rx_Buffer[0]+1;

	/* Extract the CRC from Host */
	u32 Host_CRC = *((u32 *) (BL_Rx_Buffer + Command_Packet_Len - 4) );

	if(! BootLoader_Verify_CRC(&BL_Rx_Buffer[0], Command_Packet_Len - 4, Host_CRC))
	{
		printmsg("BL_DEBUG_MSG: CheckSum Sucess \n");

		/* Used to send the Command size to C / Python Script
		 * In Host device
		*/
		BootLoader_Send_ACK(pBuffer[0], 1);
		Status = Config_Flash_Sector_RW_Protection(0, 0, 1);
        printmsg("BL_DEBUG_MSG: flash erase status: %#x\n",Status);

        BootLoader_UART_Write_Data(&Status, 1);
	}
	else
	{
		printmsg("BL_DEBUG_MSG: CheckSum Failed /n");
		BootLoader_Send_NACK();
	}
}


/********************** Helper Function to BootLoader ************************/
void BootLoader_Send_ACK(u8 Command, u8 Follow_Length)
{
	/* Sending 2 Bytes: ACK and Follow Command Length */
	u8 ACK_Buf[2];
	ACK_Buf[0] = ACK;
	ACK_Buf[1] = Follow_Length;

	vidUSART_SendString(USART1, ACK_Buf, 2);

}

void BootLoader_Send_NACK(void)
{
	u8 Nack = BL_NACK;
	vidUSART_SendString(USART1, &Nack, 1);
}

u8 BootLoader_Verify_CRC(u8 *pData, u32 len, u32 crc_host)
{
	u32 i = 0;
	u32 CRC_Value = 0xFF;

	for(i=0; i < len; i++)
	{
		u32 i_data = pData[i];
		CRC_Value = u32CRC_Accumulate(CRC_Engine, &i_data, 1);
	}


	/* Reset CRC Calculation Unit */
	vidCRC_Reset(CRC_Engine);
	if(CRC_Value == crc_host)
	{
		return VERIFY_CRC_SUCCESS;
	}
	else
	{
		return VERIFY_CRC_FAIL;
	}
}

/* Read Chip ID From DEBUG_IDCODE Register
 * In STM32F429, This Register holds the value of
 * Revision ID (Bit 31:16) and
 * Device ID (Bit 11:0) which is here 0x419
 *  */
u16 Get_MCU_CID(void)
{
	u16 CID = 0;
	CID = u16Get_MCU_ID();
	return CID;

}

/* Get Flash Level of protection by reading
 * The Option Bytes value
 * In STM32F429 There are 4 bytes of Option bytes
 * Each 2 bytes for each bank
 * Getting Flash Level of protection by reading
 * the second byte in address 0x1FFFC000
 * */
u8 Get_Flash_RDP_Level(void)
{
	u8 RDP_Status = 0;

	volatile u32 *Ptr_to_OptionByteAddress = (u32*)0x1FFFC000;
	RDP_Status = (u8)(*Ptr_to_OptionByteAddress >> 8);
	return RDP_Status;
}

/* Check if The Go_Address is valid or not
 * Valid Addresses:
 * 		-System Memory (Has the ST BootLoader)
 * 		-SRAM1 Memory
 * 		-SRAM2 Memory
 * 		-SRAM3 Memory
 * 		-Backup SRAM Memory
 * 		-External Memory
 * 		-Flash Memory (Main Memory with its both Banks)
 *
 * Invalid Adresses:
 * 		-CCM Memory (Accessed by D-Bus through CPU Only)
 * 		-Peripheral Addresses
*/
u8 Verify_Address(u32 Address)
{

	if((Address >= SRAM1_BASE) && (Address <= SRAM1_END))
	{
		return ADDRESS_VALID;
	}

	else if((Address >= SRAM2_BASE) && (Address <= SRAM2_END))
	{
		return ADDRESS_VALID;
	}

	else if((Address >= SRAM3_BASE) && (Address <= SRAM3_END))
	{
		return ADDRESS_VALID;
	}

	else if((Address >= FLASH_BASE) && (Address <= FLASH_END))
	{
		return ADDRESS_VALID;
	}

	else if((Address >= BKPSRAM_BASE) && (Address <= BKPSRAM_END))
	{
		return ADDRESS_VALID;
	}

	else if((Address >= SYSTEM_MEMORY_BASE) && (Address <= SYSTEM_MEMORY_END))
	{
		return ADDRESS_VALID;
	}
	else
	{
		return ADDRESS_INVALID;
	}
}

/* Used to Mass Erase the Flash
 * Both Bank 1 and Bank 2 */
u8 Execute_Flash_Mass_Erase(void)
{
	Flash_Configurations Flash_Config = {0};
	u8 Status = 3;
	Flash_Config.Erase_Type	= FLASH_ERASE_MASS;
	Flash_Config.Banks		= FLASH_BANK_BOTH;

	// Unlock Flash To Start Writing on it
	FLASH_Unlock_Sequence();

	// Work in 2.7 -> 3.6V
	Flash_Config.Voltage_Range 	= FLASH_VOLATGE_RANGE_3;

	Status = (u8)FLASH_Mass_Erase(&Flash_Config);

	// Lock the Flash again after writing on it
	FLASH_Lock_Sequence();
	return Status;
}

/* In STM32F429 we have 2 Banks
 * Each bank has 12 sectors
*/
u8 Execute_Flash_Erase(u8 Sector_Number, u8 Number_of_Sectors)
{


	Flash_Configurations Flash_Config = {0};
	u8 Remaining_Sectors = 0;
	u8 Status = -1;


	if((Sector_Number == 0xFF ) || (Sector_Number <=23))
	{

		// Mass Erase To All FLash Content (BootLoader also will be erased)
		if(Sector_Number == 0xFF)
		{
			Flash_Config.Erase_Type	= FLASH_ERASE_MASS;
			Flash_Config.Banks		= FLASH_BANK_BOTH;

		}
		// First Bank
		else if( (Sector_Number>=0) && (Sector_Number <=11) )
		{
			//Calculating how many sectors need to be erased
			Remaining_Sectors = 11 - Sector_Number;
			if(Number_of_Sectors > Remaining_Sectors)
			{
				Number_of_Sectors 		= Remaining_Sectors;
			}
			Flash_Config.Erase_Type		= FLASH_ERASE_SECTORS;
			Flash_Config.Sector			= Sector_Number;	//Inintial Sector
			Flash_Config.Num_of_Secotrs	= Number_of_Sectors;

			Flash_Config.Banks			= FLASH_BANK_1;
		}
		//Second Bank
		else if( (Sector_Number>=12) && (Sector_Number <=23) )
		{
			//Calculating how many sectors need to be erased
			Remaining_Sectors = 23 - Sector_Number;
			if(Number_of_Sectors > Remaining_Sectors)
			{
				Number_of_Sectors = Remaining_Sectors;
			}
			Flash_Config.Erase_Type		= FLASH_ERASE_SECTORS;
			Flash_Config.Sector			= Sector_Number;	//Inintial Sector
			Flash_Config.Num_of_Secotrs	= Number_of_Sectors;


		}

		// Unlock Flash To Start Writing on it
		FLASH_Unlock_Sequence();

		// Work in 2.7 -> 3.6V
		Flash_Config.Voltage_Range 	= FLASH_VOLATGE_RANGE_3;

		Status = (u8)FLASH_Erase(&Flash_Config);

		// Lock the Flash again after writing on it
		FLASH_Lock_Sequence();
		return Status;
	}
	return INVALID_SECTOR;

}

/* Used to take Binaries from Host application
 * and write it into Flash
 * NOTE: Maximum Packet = 255 bytes
 * So, it will be used more than 1 time
 * to flash the entire image
*/
u8 Execute_Mem_Write(u8 *pBuffer, u32 Mem_Address, u32 Len)
{
	uint8_t  Status = OK;
	uint32_t i = 0;

	/* Unlock FLash to start writing on it */
	FLASH_Unlock_Sequence();

	/* Program the FLash Byte by Byte */
	for(i=0; i<Len; i++)
	{
		Status = FLASH_Program(FLASH_PROGRAM_TYPE_BYTE, Mem_Address + i, pBuffer[i]);

	}
	FLASH_Lock_Sequence();
	return Status;

}

/*@Brife:  Helper Function used to Serve Flash Read Write Protection
 *@Param:  Sector_Details : Sector Number
 *		   Protection_Mode: 1->Write Protection , 2->R/W Protection
 *		   Disable_State  : 1->Disable R/W Protection to All Sectors
 *@Retval: 0 if Success
 * */
u8 Config_Flash_Sector_RW_Protection(u32 Sector_Number, u8 Protection_Mode, u8 Disable_State)
{
	if(Disable_State == 1)
	{
		FLASH_Unlock_OB_Sequence();

		FLASH_Disable_Read_Write_Protection();

		FLASH_Lock_OB_Sequence();

		return 0;
	}

	if(Protection_Mode == 1)
	{
		FLASH_Unlock_OB_Sequence();
		FLASH_Enable_Write_Protection(Sector_Number, Protection_Mode);
		FLASH_Lock_OB_Sequence();
		return 0;

	}

	else if (Protection_Mode == 2)
	{
		FLASH_Unlock_OB_Sequence();
		FLASH_Enable_Read_Write_Protection(Sector_Number, Protection_Mode);
		FLASH_Lock_OB_Sequence();
		return 0;
	}
	return -1;
}


u32 Read_OptionByte_Protection_Status(void)
{
	return u32FLASH_Read_Protection_Level();
}

u8 Get_BootLoader_Version(void)
{
	return (u8) BL_VERSION;
}

void BootLoader_UART_Write_Data(u8 *pBuffer, u32 Len)
{

		vidUSART_SendString(USART1, pBuffer, Len);


	//HAL_UART_Transmit(C_UART, pBuffer, Len, HAL_MAX_DELAY);
}

/* USER CODE END 4 */


