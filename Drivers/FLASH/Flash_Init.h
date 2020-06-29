/*
 * Flash_Init.h
 *
 *  Created on: Jun 19, 2020
 *      Author: islam
 */

#ifndef FLASH_INIT_H_
#define FLASH_INIT_H_

typedef struct{

	u32 Erase_Type;		/* Mass Erase or Sector Erase
	 	 	 	 	 	 You Can Find These values @Ref FLASH_ERASE */

	u32 Banks;			/* Select Which Bank to Erase When Mass Erase Chosen
	 	 	 	 	 	 You Can Find these values @Ref FLASH_BANK */

	u32 Sector;			/* Starting Sector To Erase When Mass Erase is NOT Chosen
	 	 	 	 	 	 You Can Find these values @Ref FLASH_SECTOR */

	u32 Num_of_Secotrs;	/* Number of Sectors That you Want to Erase
	 	 	 	 	 	 This Value must be from 1 to (Max Num of Sectors (23) - Value of Initial Sector */

	u32 Voltage_Range;	/* Voltage Range that your controller work on
	 	 	 	 	 	 You Can Find these values @Ref FLASH_VOLTAGE_RANGE */


}Flash_Configurations;

/* @DefGroup: FLASH_ERASE */
#define FLASH_ERASE_SECTORS				0x00
#define FLASH_ERASE_MASS				0x01

/* @DefGroup: FLASH_BANK */
#define FLASH_BANK_1					0x01
#define FLASH_BANK_2					0x02
#define FLASH_BANK_BOTH					0x03

/* @DefGroup: FLASH_SECTOR */
#define FLASH_SECTOR_0					0x00
#define FLASH_SECTOR_1					0x01
#define FLASH_SECTOR_2					0x02
#define FLASH_SECTOR_3					0x03
#define FLASH_SECTOR_4					0x04
#define FLASH_SECTOR_5					0x05
#define FLASH_SECTOR_6					0x06
#define FLASH_SECTOR_7					0x07
#define FLASH_SECTOR_8					0x08
#define FLASH_SECTOR_9					0x09
#define FLASH_SECTOR_10					0x0A
#define FLASH_SECTOR_11					0x0B
#define FLASH_SECTOR_12					0x0C
#define FLASH_SECTOR_13					0x0D
#define FLASH_SECTOR_14					0x0E
#define FLASH_SECTOR_15					0x0F
#define FLASH_SECTOR_16					0x10
#define FLASH_SECTOR_17					0x11
#define FLASH_SECTOR_18					0x12
#define FLASH_SECTOR_19					0x13
#define FLASH_SECTOR_20					0x14
#define FLASH_SECTOR_21					0x15
#define FLASH_SECTOR_22					0x16
#define FLASH_SECTOR_23					0x17


/* @DefGroup: FLASH_VOLTAGE_RANGE */
#define FLASH_VOLATGE_RANGE_1			0x00		/* Device Voltage Range:  1.8V -> 2.1V */
#define FLASH_VOLATGE_RANGE_2			0x01		/* Device Voltage Range:  2.1V -> 2.7V */
#define FLASH_VOLATGE_RANGE_3			0x02		/* Device Voltage Range:  2.7V -> 3.6V */
#define FLASH_VOLATGE_RANGE_4			0x03		/* Device Voltage Range:  2.7V -> 3.6V + External Source */


/* @DefGroup: FLASH_PROGRAM_TYPE */
#define FLASH_PROGRAM_TYPE_BYTE			0x00
#define FLASH_PROGRAM_TYPE_HALF_WORD	0x01
#define FLASH_PROGRAM_TYPE_WORD			0x02

/*											FLASH OPTCR Defines 							  		 */
#define FLASH_OPTCR_OPTLOCK				(0x1<<0)	/* Option Byter Lock							 */
#define FLASH_OPTCR_OPTSRTR				(0x1<<1)	/* Option Bytes Start Operations		 		 */
#define FLASH_OPTCR_BOR_LEVEL_3			0x00		/* BOR Level 1									 */
#define FLASH_OPTCR_BOR_LEVEL_2			0x04		/* BOR Level 2 								 	 */
#define FLASH_OPTCR_BOR_LEVEL_1			0x08		/* BOR Level 1 									 */
#define FLASH_OPTCR_BOR_LEVEL_OFF		0x0C		/* BOR Level Off								 */
#define FLASH_OPTCR_BFB2				(0x1<<4)	/* Dual-Bank Boot Option Byte				 	 */
#define FLASH_OPTCR_WDG_SW				(0x1<<5)	/* After Reset WatchDog SW Option Byte Value	 */
#define FLASH_OPTCR_nRST_STOP			(0x1<<6)	/* After Reset Stop Option Byte Value 		 	 */
#define FLASH_OPTCR_nRST_STDBY			(0x1<<7)	/* After Reset StandBy Option Byte Value 		 */
#define FLASH_OPTCR_DB1M				(0x1<<30)	/* Dual Bank on 1Mbyte Flash Memory Device	     */
#define FLASH_OPTCR_SPRMOD				(0x1<<31)	/* Selection of Protection Mode for nWPRi Bits 	 */


/*											FLASH ACR Defines 								  		 */
#define FLASH_ACR_ICEN					(0x02<<8)	/* Flash Instruction Cache Enable 				 */
#define FLASH_ACR_ICRST					(0x08<<8)	/* Flash Instruction Cache Reset 				 */
#define FLASH_ACR_DCEN					(0x04<<8)	/* Flash Data Cache Enable 						 */
#define FLASH_ACR_DCRST					(0x01<<12)	/* Flash Data Cache Reset  						 */

#define FLASH_SR_BSY_FLAG				0x10000		/* Flash Busy Flag 								 */
#define FLASH_SR_EOP_FLAG				0x00001		/* Flash End of Operation Flag 					 */

/*											FLASH CR Defines 								  		  */
#define FLASH_CR_LOCK					0x80000000	/* Flash Lock Bit 								  */
#define FLASH_CR_PSIZE_8				0x000		/* Flash Program Size 8  bit (at Voltage Range 1) */
#define FLASH_CR_PSIZE_16				0x100		/* Flash Program Size 16 bit (at Voltage Range 2) */
#define FLASH_CR_PSIZE_32				0x200		/* Flash Program Size 32 bit (at Voltage Range 3) */
#define FLASH_CR_PSIZE_64				0x300		/* Flash Program Size 64 bit (at Voltage Range 3) */
#define FLASH_CR_MER_BANK_1				0x04
#define	FLASH_CR_MER_BANK_2				0x8000
#define FLASH_CR_MER_BOTH				(FLASH_CR_MER_BANK_1 | FLASH_CR_MER_BANK_2)
#define FLASH_CR_START					0x10000
#define FLASH_CR_SNB_CLR				0xF8
#define FLASH_CR_SER					0x02
#define FLASH_CR_PG						0x01		/* Flash Programming Activated 					  */

#define FLASH_KEY1						0x45670123
#define FLASH_KEY2						0xCDEF89AB


#define FLASH_OB_KEY1					0x08192A3B
#define FLASH_OB_KEY2					0x4C5D6E7F

#define SECTOR0_RW						(1    << 16)/* Sector 0  Programming in OPTCR/1 Register 	  */
#define SECTOR1_RW						(2    << 16)/* Sector 1  Programming in OPTCR/1 Register	  */
#define SECTOR2_RW						(4    << 16)/* Sector 2  Programming in OPTCR/1 Register	  */
#define SECTOR3_RW						(8    << 16)/* Sector 3  Programming in OPTCR/1 Register	  */
#define SECTOR4_RW						(16   << 16)/* Sector 4  Programming in OPTCR/1 Register   	  */
#define SECTOR5_RW						(32   << 16)/* Sector 5  Programming in OPTCR/1 Register 	  */
#define SECTOR6_RW						(64   << 16)/* Sector 6  Programming in OPTCR/1 Register 	  */
#define SECTOR7_RW						(128  << 16)/* Sector 7  Programming in OPTCR/1 Register   	  */
#define SECTOR8_RW						(256  << 16)/* Sector 8  Programming in OPTCR/1 Register 	  */
#define SECTOR9_RW						(512  << 16)/* Sector 9  Programming in OPTCR/1 Register 	  */
#define SECTOR10_RW						(1024 << 16)/* Sector 10 Programming in OPTCR/1 Register 	  */
#define SECTOR11_RW						(2048 << 16)/* Sector 11 Programming in OPTCR/1 Register 	  */

#define OPTCR_nWRP_Value				0x40023C16U
#define OPTCR1_nWRP_Value				0x40023C1AU

Return_Status FLASH_Erase(Flash_Configurations *xFlashConfig);
Return_Status FLASH_Unlock_Sequence(void);
Return_Status FLASH_Lock_Sequence(void);
Return_Status FLASH_Wait_Till_Operation_End(void);
Return_Status FLASH_Disable_Read_Write_Protection(void);
Return_Status FLASH_Enable_Write_Protection(u32 Sector_Number, u8 Protection_Type);
Return_Status FLASH_Enable_Read_Write_Protection(u32 Sector_Number, u8 Protection_Type);
Return_Status FLASH_Lock_OB_Sequence(void);
u32 u32FLASH_Read_Protection_Level(void);
Return_Status FLASH_Unlock_OB_Sequence(void);
Return_Status FLASH_Mass_Erase(Flash_Configurations *xFlashConfig);
Return_Status FLASH_Sector_Erase(u8 u8Voltage_Range, u32 u32Sector);
Return_Status FLASH_Program(u32 u32Programming_Type, u32 u32Address, u64 u64Data);
void vidFLASH_ProgramByte(u32 u32Address, u8 u8Data);
void vidFLASH_ProgramHalfWord(u32 u32Address, u16 u16Data);
void vidFLASH_ProgramWord(u32 u32Address, u32 u32Data);
void vidFLASH_ProgramDoubleWord(u32 u32Address, u64 u64Data);
void vidFLASH_FlushCaches(void);
#endif /* FLASH_INIT_H_ */
