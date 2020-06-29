/*
 * main.h
 *
 *  Created on: Jun 16, 2020
 *      Author: Islam Ehab
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>
#include <stdarg.h>
#include "string.h"


#include "STD_TYPES.h"
#include "RCC_Init.h"
#include "SYSTICK_Init.h"
#include "NVIC_Init.h"
#include "Debug_Init.h"
#include "DMA_Reg.h"
#include "DMA_Init.h"
#include "GPIO_Init.h"
#include "GPIO_REG.h"
#include "USART_Init.h"
#include "USART_Reg.h"
#include "CRC_Init.h"
#include "Flash_Init.h"
#include "Flash_Reg.h"
//#include "NVIC_Reg.h"
#define SCB_VTOR   *((volatile u32*)0xE000ED08)


#ifndef   __STATIC_FORCEINLINE
  #define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static __inline
#endif

#ifndef   __ASM
  #define __ASM                                  __asm
#endif
__STATIC_FORCEINLINE void __set_MSP(u32 topOfMainStack)
{
	__ASM volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
}

/* BootLoader Function Prototype */
void Bootloader_UART_Read_Data(void);
void Bootloader_Jump_To_User_Application(void);

void BootLoader_Handle_GetVer_CMD(u8 *pBuffer);
void BootLoader_Handle_GetHelp_CMD(u8 *pBuffer);
void BootLoader_Handle_GetCID_CMD(u8 *pBuffer);
void BootLoader_Handle_GetRDP_CMD(u8 *pBuffer);
void BootLoader_Handle_Go_CMD(u8 *pBuffer);
void BootLoader_Handle_Flash_Erase_CMD(u8 *pBuffer);
void BootLoader_Handle_Flash_Mass_Erase_CMD(u8 *pBuffer);
void BootLoader_Handle_Mem_Write_CMD(u8 *pBuffer);
void BootLoader_Handle_Enable_RW_Protection(u8 *pBuffer);
void BootLoader_Handle_Mem_Read(u8 *pBuffer);
void BootLoader_Handle_Read_Sector_Status(u8 *pBuffer);
void BootLoader_Handle_Read_OTP(u8 *pBuffer);
void BootLoader_Handle_Disable_RW_Protection(u8 *pBuffer);

void BootLoader_Send_ACK(u8 Command, u8 Follow_Length);
void BootLoader_Send_NACK(void);
u8 BootLoader_Verify_CRC(u8 *pData, u32 len, u32 crc_host);
u8 Get_BootLoader_Version(void);
u32 Read_OptionByte_Protection_Status(void);
u16 Get_MCU_CID(void);
u8 Config_Flash_Sector_RW_Protection(u32 Sector_Number, u8 Protection_Mode, u8 Disable_State);
u8 Verify_Address(u32 Address);
u8 Execute_Flash_Erase(u8 Sector_Number, u8 Number_of_Sectors);
u8 Execute_Flash_Mass_Erase(void);
u8 Execute_Mem_Write(u8 *pBuffer, u32 Mem_Address, u32 Len);
u8 Get_Flash_RDP_Level(void);
void BootLoader_UART_Write_Data(u8 *pBuffer, u32 Len);

/*************** BootLoader Command Defines *******************/

/* Read Bootloader Version from MCU */
#define BL_GET_VER						0x51

/* Know what commands supported by this Bootloader */
#define BL_GET_HELP						0x52

/* Read the MCU Chip ID Number */
#define BL_GET_CID						0x53

/* Read the FLASH Protection Level */
#define BL_GET_RDP_STATUS				0x54

/* Jump to spicified address */
#define BL_GO_TO_ADDR					0x55

/* Mass Erase or a sector erase */
#define BL_FLASH_ERASE					0x56

/* Write Data to different type of memories (SRAM1, 2, etc) */
#define BL_MEM_WRITE					0x57

/* Enable Read/Write Protection */
#define BL_EN_RW_PROTECT				0x58

/* read data from different memories of the microcontroller */
#define BL_MEM_READ						0x59

/* read all the sector protection status */
#define BL_READ_SECTOR_P_STATUS			0x5A

/* read the OTP contents */
#define BL_OTP_READ						0x5B

/* disable read/write protection on different sectors of the user flash */
#define BL_DIS_R_W_PROTECT				0x5C

/* Mass Erase for Flash */
#define BL_FLASH_MASS_ERASE				0x5E

/****************** BootLoader Command Defines Ends ************************/

#define SECTOR2_BASE_ADDRESS  		 	0x08008000
#define SECTOR3_BASE_ADDRESS  			0x0800C000
#define ACK								0xA5
#define BL_NACK							0x7F

#define VERIFY_CRC_SUCCESS   			0
#define VERIFY_CRC_FAIL					1


#define ADDRESS_VALID					0x00
#define ADDRESS_INVALID					0x01
#define INVALID_SECTOR					0x04


#define SYSTEM_MEMORY_BASE				0x1FFF0000

#define SRAM1_SIZE						112*1024
#define SRAM2_SIZE						16*1028
#define SRAM3_SIZE						64*1024
#define BKPSRAM_SIZE					4*1024
#define SYSTEM_MEMORY_SIZE				30*1024

#define SRAM1_BASE            			0x20000000
#define SRAM2_BASE  					0x2001C000
#define SRAM3_BASE						0x20020000
#define	FLASH_BASE						0x08000000
#define BKPSRAM_BASE					0x40024000

#define SRAM1_END						(SRAM1_BASE + SRAM1_SIZE)
#define SRAM2_END						(SRAM2_BASE + SRAM2_SIZE)
#define SRAM3_END						(SRAM3_BASE + SRAM3_SIZE)
#define BKPSRAM_END						(BKPSRAM_BASE + BKPSRAM_SIZE)
#define FLASH_END             			0x081FFFFFUL
#define SYSTEM_MEMORY_END				(SYSTEM_MEMORY_BASE + SYSTEM_MEMORY_SIZE)

/* BootLoader Version 1 */
#define BL_VERSION 						0x10



#endif /* MAIN_H_ */
