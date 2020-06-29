/*
 * RCC_Prog.c
 *
 *  Created on: Feb 12, 2020
 *      Author: Islam Ehab
 */


#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "RCC_Reg.h"
#include "RCC_Init.h"


/***************Function Definition***************/
/*               Choose HSE as I/P               */
/*      Generate CLK 72Mhz & For USB 48MHz       */
/*Open CLK To PLLSAI & PLLI2S For Audio Interface*/
/*         and LCD Display with FREQ 72MHz       */
/*PLL Calculations:                              */
void vidRCC_Init(void)
{

	SET_BIT(RCC -> CR, 0);   			//Enable High Speed Interal CLK  16MHz
	while(!((RCC -> CR)& 0x00000002));	//Wait Until HSI is Stable


/*	RCC -> CR 			= 0x33037F83;
	RCC -> PLLCFGR 		= 0x03401204;
	RCC -> CFGR			= 0x0000100A;
	RCC -> CSR			= 0x1E000000;
	RCC -> PLLI2SCFGR	= 0x24003000;
	RCC -> PLLSAICFGR	= 0X24000C80;*/

//	CLR_BIT(RCC -> PLLCFGR,22);			//HSE I\P To PLL & PLLI2S
//
//	RCC -> PLLCFGR    |= 0x0300168A;
//	RCC -> PLLI2SCFGR |= 0x22001680;
//	RCC -> PLLSAICFGR |= 0x22001680;


}


void vidRCC_RegInit(void)
{
	RCC -> CR &= ~(0xFFFFFFFF);
	RCC -> AHB1ENR   &= ~(0xFFFFFFFF);
	RCC -> AHB1LPENR &= ~(0xFFFFFFFF);
	RCC -> AHB1RSTR  &= ~(0xFFFFFFFF);
	RCC -> AHB2ENR	 &= ~(0xFFFFFFFF);
	RCC -> AHB2LPENR &= ~(0xFFFFFFFF);
	RCC -> AHB2RSTR  &= ~(0xFFFFFFFF);
	RCC -> AHB3ENR   &= ~(0xFFFFFFFF);
	RCC -> AHB3LPENR &= ~(0xFFFFFFFF);
	RCC -> AHB3RSTR  &= ~(0xFFFFFFFF);
	RCC -> APB1ENR   &= ~(0xFFFFFFFF);
	RCC -> APB1LPENR &= ~(0xFFFFFFFF);
	RCC -> APB1RSTR  &= ~(0xFFFFFFFF);
	RCC -> APB2ENR   &= ~(0xFFFFFFFF);
	RCC -> APB2LPENR &= ~(0xFFFFFFFF);
	RCC -> APB2RSTR  &= ~(0xFFFFFFFF);
	RCC -> BDCR		 &= ~(0xFFFFFFFF);
	RCC -> CFGR 	 &= ~(0xFFFFFFFF);
	RCC -> CIR		 &= ~(0xFFFFFFFF);
	RCC -> CSR		 &= ~(0xFFFFFFFF);
	RCC -> DCKCFGR 	 &= ~(0xFFFFFFFF);
	RCC -> PLLCFGR	 &= ~(0xFFFFFFFF);
	RCC -> PLLI2SCFGR&= ~(0xFFFFFFFF);
	RCC -> PLLSAICFGR&= ~(0xFFFFFFFF);
	RCC -> SSCGR	 &= ~(0xFFFFFFFF);


	RCC -> CR 		 = 0x00000083;
	RCC -> PLLCFGR	 = 0x24003010;
	RCC -> AHB1ENR	 = 0x00100000;
	RCC -> AHB1LPENR = 0x7EEF97FF;
	RCC -> AHB2LPENR = 0x000000F1;
	RCC -> AHB3LPENR = 0x00000001;
	RCC -> APB1LPENR = 0xF6FEC9FF;
	RCC -> APB2LPENR = 0x04777F33;
	RCC -> CSR		 = 0x0E000000;
	RCC -> PLLI2SCFGR= 0x24003000;
	RCC -> PLLSAICFGR= 0x24003000;


	/* Enable HSI */
	RCC->CR |= (1 << 0);

	while((RCC->CR & RCC_CR_HSIRDY) != RCC_CR_HSIRDY);

	RCC->CFGR = 0x00;

	while((RCC->CFGR & RCC_CFGR_SWS) != 0);

	RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_HSEBYP | RCC_CR_CSSON);

	while((RCC->CR & RCC_CR_HSERDY) != 0);

	RCC->CR &= ~RCC_CR_PLLON;

	while((RCC->CR & RCC_CR_PLLRDY) != 0);




}

void vidRCC_EnableClock(u8 u8Peripheral)
{
	if ((u8Peripheral >= 0) && (u8Peripheral < 32))
	{
		//AHB1 Bus
		SET_BIT(RCC -> AHB1ENR, u8Peripheral);
	}

	else if ((u8Peripheral >= 32) && (u8Peripheral < 64))
	{
		//AHB2 Bus
		u8Peripheral -=32;
		SET_BIT(RCC -> AHB2ENR, u8Peripheral);
	}

	else if ((u8Peripheral >= 64) && (u8Peripheral < 128))
	{
		//AHB3 Bus
		u8Peripheral -=64;
		SET_BIT(RCC -> AHB3ENR, u8Peripheral);

	}

	else if((u8Peripheral >=128) && (u8Peripheral < 160))
	{
		//APB1 Bus
		u8Peripheral -=128;
		SET_BIT(RCC -> APB1ENR, u8Peripheral);
	}

	else if((u8Peripheral >=160) && (u8Peripheral <192))
	{
		//APB2 Bus
		u8Peripheral -=160;
		SET_BIT(RCC -> APB2ENR, u8Peripheral);
	}

	else
	{
		//Guard Else
	}
}

void vidRCC_DisableClock(u8 u8Peripheral)
{
	switch(u8Peripheral)
	{
	case 0 ... 31:
	//AHB1 Bus
	SET_BIT(RCC -> AHB1RSTR, u8Peripheral);
	break;

	case 32 ... 63:
	//AHB2 Bus
	u8Peripheral -=32;
	SET_BIT(RCC -> AHB2RSTR, u8Peripheral);
	break;

	case 64 ... 127:
	//AHB3 Bus
	u8Peripheral -=64;
	SET_BIT(RCC -> AHB3RSTR, u8Peripheral);
	break;

	case 128 ... 159:
	//APB1 Bus
	u8Peripheral -=128;
	SET_BIT(RCC -> APB1RSTR, u8Peripheral);
	break;

	case 160 ... 186:
	//APB2 Bus
	u8Peripheral -=160;
	SET_BIT(RCC -> APB2RSTR, u8Peripheral);
	break;

	default:
	break;
	}
}

