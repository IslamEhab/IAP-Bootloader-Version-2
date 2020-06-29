/*
 * CRC_Init.h
 *
 *  Created on: Jun 15, 2020
 *      Author: Islam Ehab
 */

#ifndef CRC_CRC_INIT_H_
#define CRC_CRC_INIT_H_

#include "CRC_Reg.h"

#define CRC_RESET			0x01


u32 u32CRC_Calculate(CRC_REG* CRC_Handle, u32 *pBuffer, u32 Len);

u32 u32CRC_Accumulate(CRC_REG* CRC_Handle, u32 *pBuffer, u32 Len);

void vidCRC_Reset(CRC_REG* CRC_Handle);

void vidCRC_InitReg(void);



#endif /* CRC_CRC_INIT_H_ */
