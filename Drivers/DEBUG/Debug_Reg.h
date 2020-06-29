/*
 * DEBUG_Reg.h
 *
 *  Created on: Jun 18, 2020
 *      Author: Islam Ehab
 */

#ifndef DEBUG_REG_H_
#define DEBUG_REG_H_

typedef struct{
	volatile u32 IDCODE;		// Device ID Code
	volatile u32 CR;			// Configuration Register
	volatile u32 APB1_FZ;		// APB1 Freeze Register
	volatile u32 APB2_FZ;		// APB2 Freeze Register
}DBGMCU;

#define DBGMCU_REG           ((DBGMCU*) 0xE0042000UL)


#endif /* DEBUG_REG_H_ */
