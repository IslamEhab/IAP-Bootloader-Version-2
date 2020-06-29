
#include "STD_TYPES.h"
#include "Debug_Reg.h"
#include "Debug_Init.h"



/**
 * @brief	MCU ID Getter
 * @param 	None
 * @retval 	MCU ID
 */
u16 u16Get_MCU_ID(void)
{
	u16 MCU_ID = 0;
	MCU_ID = (u16)(DBGMCU_REG -> IDCODE & 0x0FFF);
	return MCU_ID;
}

/**
 * @brief	MCU Revison ID Getter
 * @param 	None
 * @retval 	MCU Revison ID
 */
u16 u16Get_MCU_Revision_ID(void)
{
	u16 MCU_REV_ID = 0;
	MCU_REV_ID = (u16)(DBGMCU_REG -> IDCODE & 0xFFFF0000);
	return MCU_REV_ID;
}

