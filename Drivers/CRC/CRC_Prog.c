/*
 * CRC_Prog.c
 *
 *  Created on: Jun 15, 2020
 *      Author: Islam Ehab
 */

#include "STD_TYPES.h"
#include "CRC_Reg.h"
#include "CRC_Init.h"


/*
 * @Brife	Calculate the 32-bit CRC Value of the 32-bit data input
 * 			Start with previous computed CRC Value as initialized value
 * @Param	CRC_Handle  	Pointer to CRC_REG Struct which has the registers
 * @Param	pBuffer 		Pointer to Data input
 * @Param	Len				Length of input data to be computed
 * @Return	u32 CRC_Answer	CRC Value after computation
*/
u32 u32CRC_Accumulate(CRC_REG* CRC_Handle, u32 pBuffer[], u32 Len)
{

	u32 Index;
	u32 Temp = 0U;

	//vidCRC_InitReg(CRC_Handle);
	for(Index=0U; Index<Len; Index++)
	{
		/* Load Data to CRC Data Register */
		CRC_Handle -> DR = pBuffer[Index];
	}
	Temp = CRC_Handle -> DR;

	return Temp;
}

/*
 * @Brife	Calculate the 32-bit CRC Value of the 32-bit data input
 * 			Start with CRC_Handle->DR as initialized value (0xFFFF FFFF)
 * @Param	CRC_Handle  	Pointer to CRC_REG Struct which has the registers
 * @Param	pBuffer 		Pointer to Data input
 * @Param	Len				Length of input data to be computed
 * @Return	u32 CRC_Answer	CRC Value after computation
 * */
u32 u32CRC_Calculate(CRC_REG* CRC_Handle, u32 *pBuffer, u32 Len)
{
	u32 i;
	u32 CRC_Answer = 0;

	/* Reset CRC Data Register Before starting calculating the CRC Value
	 * Reset done by Set the 0th Bit in CR Register
	*/
	CRC_Handle -> CR |= CRC_RESET;

	for(i=0; i<Len; i++)
	{
		/* Load Data to CRC Data Register */
		CRC_Handle -> DR = pBuffer[i];
	}
	CRC_Answer = CRC_Handle -> DR;

	return CRC_Answer;
}

/*
 * @Brife	Reset the CRC Engine
 * 			Start with CRC_Handle->DR as initialized value (0xFFFF FFFF)
 * @Param	CRC_Handle  	Pointer to CRC_REG Struct which has the registers
 * @Return	None
 * */
void vidCRC_Reset(CRC_REG* CRC_Handle)
{
	/* Reset CRC Data Register Before starting calculating the CRC Value
	 * Reset done by Set the 0th Bit in CR Register
	*/
	CRC_Handle -> CR |= CRC_RESET;
}

 void vidCRC_InitReg(void)
{
	 CRC_Engine -> DR  = 0xFFFFFFFF;
	 CRC_Engine -> IDR = 0x00000000;
	 CRC_Engine -> CR  = 0x00000000;
}
