/*
 * CRC_Reg.h
 *
 *  Created on: Jun 15, 2020
 *      Author: Islam Ehab
 */

#ifndef CRC_CRC_REG_H_
#define CRC_CRC_REG_H_

typedef struct{

	volatile u32 DR;			//Data Register
	volatile u32 IDR;			//Independent Data Register
	volatile u32 CR;			//Control Register
}CRC_REG;

#define CRC_Engine  ((CRC_REG*) 0x40023000)


#endif /* CRC_CRC_REG_H_ */
