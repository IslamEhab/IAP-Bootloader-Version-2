/*
 * SYSTICK_Init.h
 *
 *  Created on: Feb 16, 2020
 *      Author: Islam Ehab
 */

#ifndef SYSTICK_INIT_H_
#define SYSTICK_INIT_H_

//void SysTick_Handler1(void);
void vidSysTick_Reset(void);
void _delay_ms(u32 u32Delay);
void vidSYSTICK_Init(u32 u32Load);

#endif /* SYSTICK_INIT_H_ */
