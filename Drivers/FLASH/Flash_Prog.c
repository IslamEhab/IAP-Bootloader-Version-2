/*
 * Flash_Prog.c
 *
 *  Created on: Jun 19, 2020
 *      Author: Islam Ehab
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Flash_Reg.h"
#include "Flash_Init.h"

/**
 * @brief 	Erase Flash Funtion
 * @param 	Pointer to Flash Configuration Struct
 * @retval  Return_Status
 */
Return_Status FLASH_Erase(Flash_Configurations *xFlashConfig)
{
	u32 i = 0;
	//FLASH_Unlock();

	/* Erase BANK by BANK or BOTH BANKS */
	if(xFlashConfig -> Erase_Type == FLASH_ERASE_MASS)
	{
		FLASH_Mass_Erase(xFlashConfig);
	}

	/* Wait till Last Operation  */
	if(FLASH_Wait_Till_Operation_End() == OK)
	{

		/* Erase By Sectors */


			for(i=(xFlashConfig ->Sector) ; i< (xFlashConfig->Num_of_Secotrs + xFlashConfig ->Sector); i++)
			{
				FLASH_Sector_Erase((u8)(xFlashConfig->Voltage_Range), i);

				if(FLASH_Wait_Till_Operation_End() == OK)
				{
					FLASH->CR &= ~(FLASH_CR_SNB_CLR | FLASH_CR_SER);

				}
			}

		vidFLASH_FlushCaches();
	}
	return OK;
}

/**
 * @brief 	Program Flash Funtion
 * @param 	u32Programming_Type: Type of Flash Programming
 *			you can find this value @ref FLASH_PROGRAM_TYPE
 *
 *			u32Address: Address of FLash that data will be burned
 *
 *			u64Data: Data that will be written on flash, it can be
 *			either byte, half word, word or double word
 * @retval Return_Status
 */

Return_Status FLASH_Program(u32 u32Programming_Type, u32 u32Address, u64 u64Data)
{
	if(FLASH_Wait_Till_Operation_End() == OK)
	{
		if(u32Programming_Type == FLASH_PROGRAM_TYPE_BYTE)
		{
			/* Program Byte (8-Bit) at the given address */
			vidFLASH_ProgramByte(u32Address, (u8) u64Data);
		}
		else if (u32Programming_Type == FLASH_PROGRAM_TYPE_HALF_WORD)
		{
			/* Program Half Word (16-Bit) at the given address */
			vidFLASH_ProgramHalfWord(u32Address, (u16) u64Data);
		}
		else if (u32Programming_Type == FLASH_PROGRAM_TYPE_WORD)
		{
			/* Program Word (32-Bit) at the given address */
			vidFLASH_ProgramWord(u32Address, (u32) u64Data);
		}
		else
		{
			/* Program Double Word (64-Bit) at the given address */
			vidFLASH_ProgramDoubleWord(u32Address, (u64) u64Data);
		}

	}
	else
	{
		return NOK;
	}
	return OK;
}

/**
 * @brief 	Wait till Flash End Operation Funtion
 * @param 	None
 * @retval Return Status (If ok -> OK)
 */
Return_Status FLASH_Wait_Till_Operation_End(void)
{
	/* Wait For Flash to end its ongoing operation */
	while((FLASH -> SR & FLASH_SR_BSY_FLAG) != 0);

	/* Check if End of operation Flag is reset or not */
	if((FLASH -> SR & FLASH_SR_EOP_FLAG) != 0)
	{
		/* Reset it by writing 1 on its bit */
		FLASH -> SR |= FLASH_SR_EOP_FLAG;
	}

	return OK;
}

/**
 * @brief 	Flash Unlock Option Bytes Function
 * @param 	None
 * @retval Return Status (If ok -> OK)
 */
Return_Status FLASH_Unlock_OB_Sequence(void)
{
	if((FLASH -> OPTCR & FLASH_OPTCR_OPTLOCK) != 0)
	{
		FLASH -> OPTKEYR = FLASH_OB_KEY1;
		FLASH -> OPTKEYR = FLASH_OB_KEY2;
	}
	else
	{
		return NOK;
	}
	return OK;
}

/**
 * @brief 	Flash Unlock Function
 * @param 	None
 * @retval Return Status (If ok -> OK)
 */
Return_Status FLASH_Unlock_Sequence(void)
{
	if((FLASH-> CR & FLASH_CR_LOCK) != 0)
	{
		FLASH->KEYR = FLASH_KEY1;
		FLASH->KEYR = FLASH_KEY2;

		if((FLASH-> CR & FLASH_CR_LOCK) != 0)
		{
			return NOK;
		}
	}
	return OK;
}

/**
 * @brief 	Flash lock Function
 * @param 	None
 * @retval Return Status (If ok -> OK)
 */
Return_Status FLASH_Lock_Sequence(void)
{
	FLASH->CR |= FLASH_CR_LOCK;

	if((FLASH->CR & FLASH_CR_LOCK) == 1)
		return OK;
	else
		return NOK;
}

/**
 * @brief  Flash lock Option Bytes Function
 * @param  None
 * @retval Return Status (If ok -> OK)
 */
Return_Status FLASH_Lock_OB_Sequence(void)
{
	FLASH->OPTCR |= FLASH_OPTCR_OPTLOCK;
	return OK;
}

/**
 * @brief  Flash Disable Read Write Protection Function
 * @param  None
 * @retval Return Status (If ok -> OK)
 */
Return_Status FLASH_Disable_Read_Write_Protection(void)
{
	/* Wait For Flash to end its ongoing operation */
	while((FLASH -> SR & FLASH_SR_BSY_FLAG) != 0);


	if((FLASH -> OPTCR & FLASH_OPTCR_SPRMOD) == 1)
	{
		/* nWRP used as Read Write Protection */
		/* nWRP Bits should be 0 to disable the R/W Protection */

		/* Clear Protection, Put all bits to 1 after reset SPRMOD Bit */
		/* Here we have 2 Option Bytes, so OPTCR For first Option Byte */
		FLASH -> OPTCR  &= ~(0xFFF << 16);

		/* OPTCR1 For the second Option Byte */
		FLASH -> OPTCR1 &= ~(0xFFF << 16);

		/* Set OPSTRT (Option Start Bit) */
		FLASH -> OPTCR |= FLASH_OPTCR_OPTSRTR;

		/* Wait For Flash to end its ongoing operation */
		while((FLASH -> SR & FLASH_SR_BSY_FLAG) != 0);

		return OK;
	}
	else if ((FLASH -> OPTCR & FLASH_OPTCR_SPRMOD) == 0)
	{
		/* nWRP used as Write Protection */
		/* nWRP Bits should be 1 to disable the Write Protection */

		/* Clear Protection, Put all bits to 1 after reset SPRMOD Bit */
		/* Here we have 2 Option Bytes, so OPTCR For first Option Byte */
		FLASH -> OPTCR  |= (0xFFF << 16);

		/* OPTCR1 For the second Option Byte */
		FLASH -> OPTCR1 |= (0xFFF << 16);

		/* Set OPSTRT (Option Start Bit) */
		FLASH -> OPTCR |= FLASH_OPTCR_OPTSRTR;

		/* Wait For Flash to end its ongoing operation */
		while((FLASH -> SR & FLASH_SR_BSY_FLAG) != 0);

		return OK;
	}



#if 0
	/* Clear SPRMOD Bit (Selection of Protection Mode for nWPRi) */
	FLASH -> OPTCR &= ~(FLASH_OPTCR_SPRMOD);

	/* Clear Protection, Put all bits to 1 after reset SPRMOD Bit */
	/* Here we have 2 Option Bytes, so OPTCR For first Option Byte */
	FLASH -> OPTCR  |= (0xFFF << 16);

	/* OPTCR1 For the second Option Byte */
	FLASH -> OPTCR1 |= (0xFFF << 16);

	/* Set OPSTRT (Option Start Bit) */
	FLASH -> OPTCR |= FLASH_OPTCR_OPTSRTR;

	/* Wait For Flash to end its ongoing operation */
	while((FLASH -> SR & FLASH_SR_BSY_FLAG) != 0);

	return OK;
#endif
return NOK;
}

/**
 * @brief  Flash Enable Read Protection Function
 * @param  None
 * @retval Return Status (If ok -> OK)
 */
Return_Status FLASH_Enable_Read_Write_Protection(u32 Sector_Number, u8 Protection_Type)
{
	u32 Write_Protected_Sectors_Bank1 = 0;
	u32 Write_Protected_Sectors_Bank2 = 0;
	/* Wait For Flash to end its ongoing operation */
	while((FLASH -> SR & FLASH_SR_BSY_FLAG) != 0);

	if(Protection_Type == 2)
	{
		/* Read and Write Protection */

		/* Set SPRMOD Bit (Selection of Protection Mode for nWPRi) */
		FLASH -> OPTCR |= (FLASH_OPTCR_SPRMOD);

		/* To Get Write Protected Sectors on Bank 1 */
		Write_Protected_Sectors_Bank1 = ( (~(FLASH -> OPTCR & (0xFFF << 16))) & (0xFFF << 16) );
		FLASH -> OPTCR  &= ~(0xFFF << 16);
		FLASH -> OPTCR  |= (Write_Protected_Sectors_Bank1);


		Write_Protected_Sectors_Bank2 = ( (~(FLASH -> OPTCR1 & (0xFFF << 16))) & (0xFFF << 16) );
		FLASH -> OPTCR1 &= ~(0xFFF << 16);
		FLASH -> OPTCR1 |= (Write_Protected_Sectors_Bank2 );


		if(Sector_Number <= (11))
		{
			//FLASH -> OPTCR &= ~(0xFFF << 16);

			switch(Sector_Number)
			{
			case 0:
				FLASH -> OPTCR |= (SECTOR0_RW);
				break;

			case 1:
				FLASH -> OPTCR |= (SECTOR1_RW);
				break;

			case 2:
				FLASH -> OPTCR |= (SECTOR2_RW);
				break;

			case 3:
				FLASH -> OPTCR |= (SECTOR3_RW);
				break;

			case 4:

				FLASH -> OPTCR |= (SECTOR4_RW);

				break;

			case 5:
				FLASH -> OPTCR |= (SECTOR5_RW);
				break;

			case 6:
				FLASH -> OPTCR |= (SECTOR6_RW);
				break;

			case 7:
				FLASH -> OPTCR |= (SECTOR7_RW);
				break;

			case 8:
				FLASH -> OPTCR |= (SECTOR8_RW);
				break;

			case 9:
				FLASH -> OPTCR |= (SECTOR9_RW);
				break;

			case 10:
				FLASH -> OPTCR |= (SECTOR10_RW);
				break;

			case 11:
				FLASH -> OPTCR |= (SECTOR11_RW);
				break;

			default:
				return NOK;
				break;
			}

		}
		else if((Sector_Number >= (12)) && (Sector_Number <= (23)) )
		{
			Sector_Number-=12;
			//FLASH -> OPTCR1 &= ~(0xFFF << 16);

			//FLASH -> OPTCR1 &= ~(Sector_Number<<16);
			switch(Sector_Number)
			{
				case 0:
					FLASH -> OPTCR1 |= (SECTOR0_RW);
				break;

				case 1:
					FLASH -> OPTCR1 |= (SECTOR1_RW);
				break;

				case 2:
					FLASH -> OPTCR1 |= (SECTOR2_RW);
				break;

				case 3:
					FLASH -> OPTCR1 |= (SECTOR3_RW);
				break;

				case 4:
					FLASH -> OPTCR1 |= (SECTOR4_RW);
				break;

				case 5:
					FLASH -> OPTCR1 |= (SECTOR5_RW);
				break;

				case 6:
					FLASH -> OPTCR1 |= (SECTOR6_RW);
				break;

				case 7:
					FLASH -> OPTCR1 |= (SECTOR7_RW);
				break;

				case 8:
					FLASH -> OPTCR1 |= (SECTOR8_RW);
				break;

				case 9:
					FLASH -> OPTCR1 |= (SECTOR9_RW);
				break;

				case 10:
					FLASH -> OPTCR1 |= (SECTOR10_RW);
				break;

				case 11:
					FLASH -> OPTCR1 |= (SECTOR11_RW);
				break;

				default:
					return NOK;
				break;
			}
		}

		FLASH -> OPTCR |= FLASH_OPTCR_OPTSRTR;

		/* Wait For Flash to end its ongoing operation */
		while((FLASH -> SR & FLASH_SR_BSY_FLAG) != 0);
	}
	return OK;

}

u32 u32FLASH_Read_Protection_Level(void)
{
	u32 Temp1 = (~(*(volatile u16*)OPTCR_nWRP_Value) & 0xFFF);

	u32 Temp2 = (((~(*(volatile u16*)OPTCR1_nWRP_Value)) & 0xFFF)<<12);

	u32 Temp3 = Temp1 | Temp2;
	//return (u16)(*(volatile u16*)OPTCR_nWRP_Value);
	return Temp3;
}

/**
 * @brief  Flash Enable Write Protection Function
 * @param  None
 * @retval Return Status (If ok -> OK)
 */
Return_Status FLASH_Enable_Write_Protection(u32 Sector_Number, u8 Protection_Type)
{
	/* Wait For Flash to end its ongoing operation */
	while((FLASH -> SR & FLASH_SR_BSY_FLAG) != 0);

	if(Protection_Type == 1)
	{
		/* Write Protection Only */

		/* Clear SPRMOD Bit (Selection of Protection Mode for nWPRi) */
		FLASH -> OPTCR &= ~(FLASH_OPTCR_SPRMOD);

		if(Sector_Number <= (11))
		{
			switch(Sector_Number)
			{
			case 0:
				FLASH -> OPTCR &= ~(SECTOR0_RW);
				break;

			case 1:
				FLASH -> OPTCR &= ~(SECTOR1_RW);
				break;

			case 2:
				FLASH -> OPTCR &= ~(SECTOR2_RW);
				break;

			case 3:
				FLASH -> OPTCR &= ~(SECTOR3_RW);
				break;

			case 4:
				FLASH -> OPTCR &= ~(SECTOR4_RW);
				break;

			case 5:
				FLASH -> OPTCR &= ~(SECTOR5_RW);
				break;

			case 6:
				FLASH -> OPTCR &= ~(SECTOR6_RW);
				break;

			case 7:
				FLASH -> OPTCR &= ~(SECTOR7_RW);
				break;

			case 8:
				FLASH -> OPTCR &= ~(SECTOR8_RW);
				break;

			case 9:
				FLASH -> OPTCR &= ~(SECTOR9_RW);
				break;

			case 10:
				FLASH -> OPTCR &= ~(SECTOR10_RW);
				break;

			case 11:
				FLASH -> OPTCR &= ~(SECTOR11_RW);
				break;

			default:
				return NOK;
				break;

			}
			//FLASH -> OPTCR &= ~(Sector_Number<<16);
		}
		else if((Sector_Number >= (12)) && (Sector_Number <= (23)) )
		{
			Sector_Number-=12;
			//FLASH -> OPTCR1 &= ~(Sector_Number<<16);
			switch(Sector_Number)
			{
			case 0:
				FLASH -> OPTCR1 &= ~(SECTOR0_RW);
				break;

			case 1:
				FLASH -> OPTCR1 &= ~(SECTOR1_RW);
				break;

			case 2:
				FLASH -> OPTCR1 &= ~(SECTOR2_RW);
				break;

			case 3:
				FLASH -> OPTCR1 &= ~(SECTOR3_RW);
				break;

			case 4:
				FLASH -> OPTCR1 &= ~(SECTOR4_RW);
				break;

			case 5:
				FLASH -> OPTCR1 &= ~(SECTOR5_RW);
				break;

			case 6:
				FLASH -> OPTCR1 &= ~(SECTOR6_RW);
				break;

			case 7:
				FLASH -> OPTCR1 &= ~(SECTOR7_RW);
				break;

			case 8:
				FLASH -> OPTCR1 &= ~(SECTOR8_RW);
				break;

			case 9:
				FLASH -> OPTCR1 &= ~(SECTOR9_RW);
				break;

			case 10:
				FLASH -> OPTCR1 &= ~(SECTOR10_RW);
				break;

			case 11:
				FLASH -> OPTCR1 &= ~(SECTOR11_RW);
				break;

			default:
				return NOK;
				break;
			}
		}

		FLASH -> OPTCR |= FLASH_OPTCR_OPTSRTR;

		/* Wait For Flash to end its ongoing operation */
		while((FLASH -> SR & FLASH_SR_BSY_FLAG) != 0);

	}
	return OK;
}


/**
 * @brief 	Mass Erase (Bank 1 - Bank 2 - or Both) Function
 * @param 	Pointer to Flash Configuration Struct
 * @retval  Return Status (If ok -> OK)
 */
Return_Status FLASH_Mass_Erase(Flash_Configurations *xFlashConfig)
{
	if(FLASH_Wait_Till_Operation_End() == OK)
	{
		FLASH->CR &= ~(FLASH_CR_PSIZE_64);

		if(xFlashConfig ->Banks == FLASH_BANK_1)
		{
			/* Only Bank 1 Will be Erased */
			FLASH -> CR |= FLASH_CR_MER_BANK_1;
		}
		else if (xFlashConfig ->Banks == FLASH_BANK_2)
		{
			/* Only Bank 1 Will be Erased */
			FLASH -> CR |= FLASH_CR_MER_BANK_2;
		}
		else
		{
			/* Both Banks will be erased */
			FLASH -> CR |= FLASH_CR_MER_BOTH;
		}
		FLASH -> CR |= (FLASH_CR_START | ((u32) xFlashConfig ->Voltage_Range << 8U) );

		if(FLASH_Wait_Till_Operation_End() == OK)
		{
			/* When finish writing to flash, Disable the MER Bit */
			FLASH -> CR &= ~(FLASH_CR_MER_BOTH);
		}
		vidFLASH_FlushCaches();
	return OK;
	}

	return NOK;
}

/**
 * @brief 	Mass Erase (Bank 1 - Bank 2 - or Both) Helper Function
 * @param 	u8Voltage_Range : To Decide the program Parallelism
 * 			u32Bank			: To Know which bank will be erased or both
 * @retval 	Return Status (OK if everything fine)
 */
Return_Status FLASH_Sector_Erase(u8 u8Voltage_Range, u32 u32Sector)
{
	u32 Temp = 0;

	switch(u8Voltage_Range)
	{
	case FLASH_VOLATGE_RANGE_1:
		Temp =	FLASH_CR_PSIZE_8;
		break;

	case FLASH_VOLATGE_RANGE_2:
		Temp = FLASH_CR_PSIZE_16;
		break;

	case FLASH_VOLATGE_RANGE_3:
		Temp = FLASH_CR_PSIZE_32;
		break;

	case FLASH_VOLATGE_RANGE_4:
		Temp = FLASH_CR_PSIZE_64;
		break;

	default:
		Temp = -1;
		break;

	}

	if(Temp != -1)
	{
		/* If Sector > Sector 11
		 * Increament Sector num by 4
		 * due to invalid values at this region
		 */
		if (u32Sector > FLASH_SECTOR_11)
		{
			u32Sector +=4;
		}


		/* Clear the bits */
		FLASH->CR &= ~(FLASH_CR_PSIZE_64);

		FLASH->CR |= Temp;

		/* Clear Sector Selector Bits */
		FLASH->CR &= ~(FLASH_CR_SNB_CLR);

		FLASH->CR |=(FLASH_CR_SER | (u32Sector<<3) );

		FLASH->CR |= FLASH_CR_START;

		return OK;
	}
	else
	{
		return NOK;
	}
}

/**
 * @brief 	Flush Instruction
 * @param 	None
 * @retval None
 */
void vidFLASH_FlushCaches(void)
{
	/* Flush Instruction Cache */
	if((FLASH->ACR & FLASH_ACR_ICEN) != 0)
	{
		/* Disable Flush Instruction */
		FLASH->ACR &= ~(FLASH_ACR_ICEN);

		/* Reset Flush Instruction */
		FLASH->ACR |=  FLASH_ACR_ICRST;
		FLASH->ACR &= ~(FLASH_ACR_ICRST);

		/* Enable Flush Instruction */
		FLASH->ACR |= FLASH_ACR_ICEN;

	}

	/* Flush Data Cache */
	if((FLASH->ACR & FLASH_ACR_DCEN) != 0)
	{
		/* Disable Flush Instruction */
		FLASH->ACR &= ~(FLASH_ACR_DCEN);
		/* Reset Flush Instruction */
		FLASH->ACR |=  FLASH_ACR_DCRST;
		FLASH->ACR &= ~(FLASH_ACR_DCRST);

		/* Enable Flush Instruction */
		FLASH->ACR |= FLASH_ACR_DCEN;
	}
}

/**
 * @brief 	Byte Programming of Flash Function
 * @param 	u32Address: Address that data will be saved in flash
 *
 * 			u8Data:		Byte chunk of data that will be saved
 * @retval	 None
 */
void vidFLASH_ProgramByte(u32 u32Address, u8 u8Data)
{
	/* If Previos Operation ends, go to program the new data */
	FLASH->CR &= ~(FLASH_CR_PSIZE_64);

	FLASH->CR |= FLASH_CR_PSIZE_8;
	FLASH->CR |= FLASH_CR_PG;
	*(volatile u8*)u32Address = u8Data;

}

/**
 * @brief 	Half Word Programming of Flash Function
 * @param 	u32Address: Address that data will be saved in flash
 *
 * 			u16Data:	Half Word chunk of data that will be saved
 * @retval	 None
 */
void vidFLASH_ProgramHalfWord(u32 u32Address, u16 u16Data)
{
	/* If Previos Operation ends, go to program the new data */
	FLASH->CR &= ~(FLASH_CR_PSIZE_64);

	FLASH->CR |= FLASH_CR_PSIZE_8;
	FLASH->CR |= FLASH_CR_PG;

	*(volatile u16*)u32Address = u16Data;
}

/**
 * @brief 	Word Programming of Flash Function
 * @param 	u32Address: Address that data will be saved in flash
 *
 * 			u32Data:	Word chunk of data that will be saved
 * @retval	 None
 */
void vidFLASH_ProgramWord(u32 u32Address, u32 u32Data)
{
	/* If Previos Operation ends, go to program the new data */
	FLASH->CR &= ~(FLASH_CR_PSIZE_64);

	FLASH->CR |= FLASH_CR_PSIZE_8;
	FLASH->CR |= FLASH_CR_PG;

	*(volatile u32*)u32Address = u32Data;
}

/**
 * @brief 	Double Word Programming of Flash Function
 * @param 	u32Address: Address that data will be saved in flash
 *
 * 			u64Data:	Double Word chunk of data that will be saved
 * @retval	 None
 */
void vidFLASH_ProgramDoubleWord(u32 u32Address, u64 u64Data)
{
	/* If Previos Operation ends, go to program the new data */
	FLASH->CR &= ~(FLASH_CR_PSIZE_64);

	FLASH->CR |= FLASH_CR_PSIZE_8;
	FLASH->CR |= FLASH_CR_PG;

	/* ARM Cortex M4 Supports 32 Bit instruction
	 * Here we will write in 2 times
	 * every time is 32 bit data wide
	 */
	*(volatile u32*)u32Address = (u32)u64Data;

	/* use ISB: Instruction Sync Barrier Assembly Instrction
	 * to ensure the instruction fetch buffer is updated with the
	 * new instructions
	 */

	asm("isb 0xF":::"memory");

	/* Program the second 32 Bit */
	*(volatile u32*)(u32Address + 4) = (u32)(u64Data >> 32);


}
