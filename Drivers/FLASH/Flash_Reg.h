/*
 * Flash_Reg.h
 *
 *  Created on: Jun 19, 2020
 *      Author: islam
 */

#ifndef FLASH_REG_H_
#define FLASH_REG_H_


typedef struct{

	volatile u32 ACR;			//Access Control Register
	volatile u32 KEYR;			//Key Register
	volatile u32 OPTKEYR;		//Option Key Register (Option Bytes)
	volatile u32 SR;			//Status Register
	volatile u32 CR;			//Control Register
	volatile u32 OPTCR;			//Option Control Registerb (Option Bytes for Bank 1)
	volatile u32 OPTCR1;		//Option Control Registerb (Option Bytes for Bank 2)


}FLASH_REG;

#define FLASH		((FLASH_REG*) 0x40023C00)


#endif /* FLASH_REG_H_ */
