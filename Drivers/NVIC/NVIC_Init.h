/*
 * NVIC_Init.h
 *
 *  Created on: Feb 17, 2020
 *      Author: Islam Ehab
 */

#ifndef NVIC_INIT_H_
#define NVIC_INIT_H_


enum{
	NonMaskableInt_IRQn  = -14,
	MemManagment_IRQn	 = -12,
	//	RESET = -3,					//Reset
	//	NMI,						//Non Maskable INT, Clock Security System
	//	HardFault,					//All Class Of Fault
	//	MemManage,					//Memomry Managment
	//	BusFault,					//Pre-Fetch Fault, Memory Access Fault
	//	UsageFault,					//Undefined Instruction or Illegal State
	//	SVCall = 3,					//System Service Call via SWI Instruction
	//	DebugMonitor,				//Debug Monitor
	//	PendSV = 5,					//Pendable Request For System Service
	//	Systick,					//System Tick Timer
	Systick_IRQn = -1,
	WWD_G,						//Window WatchDog Interrupt
	PVD,						//PVD Through EXTI Line Detection Interrupt
	TAMP_STAMP,					//Tamper & TimeStamp Interrupt Through the EXTI Line
	RTC_WKUP,					//RTC Wakeup Interrupt Through the EXTI Line
	FLASH,						//Flash Global Interrupt
	RCC_,						//RCC Global Interruot
	EXTI0,						//EXTI Line0 Interrupt
	EXTI1,						//EXTI Line1 Interrupt
	EXTI2,						//EXTI Line2 Interrupt
	EXTI3,						//EXTI Line3 Interrupt
	EXTI4,						//EXTI Line4 Interrupt
	DMA1__STREAM0,				//DMA1 Streem0 Global Interrupt
	DMA1__STREAM1,				//DMA1 Streem1 Global Interrupt
	DMA1__STREAM2,				//DMA1 Streem2 Global Interrupt
	DMA1__STREAM3,				//DMA1 Streem3 Global Interrupt
	DMA1__STREAM4,				//DMA1 Streem4 Global Interrupt
	DMA1__STREAM5,				//DMA1 Streem5 Global Interrupt
	DMA1__STREAM6,				//DMA1 Streem6 Global Interrupt
	ADC,						//ADC1, ADC2 and ADC3 Global Interrupt
	CAN1_TX,					//CAN1 TX Interrupt
	CAN1_RX0,					//CAN1 RX0 Interrupt
	CAN1_RX1,					//CAN1 RX1 Interrupt
	CAN1_SCE,					//CAN1 SCE Interrupt
	EXTI9_5,					//EXTI Line[9:5] Interrupts
	TIM1_BRK_TIM9,				//TIM1 Break Interrupt & TIM9 Global Interrupt
	TIM1_UP_TIM10,				//TIM1 Update Interrupt & TIM10 Global Interrupt
	TIM1_TRG_COM_TIM11,			//TIM1 Trigger and Commutation Interrupts and TIM11 Global Interrupt
	TIM1_CC,					//TIM1 Capture Compare Interrupt
	TIM2,						//TIM2 Global Interrupt
	TIM3,						//TIM3 Global Interrupt
	TIM4,						//TIM4 Global Interrupt
	I2C1_EV,					//I2C1 Event Interrupt
	I2C1_ER,					//I2C1 Error Interrupt
	I2C2_EV,					//I2C1 Event Interrupt
	I2C2_ER,					//I2C1 Error Interrupt
	SPI1,						//SPI1 Global Interrupt
	SPI2,						//SPI2 Global Interrupt
	USART1INT,					//USART1 Global Interrupt
	USART2INT,					//USART2 Global Interrupt
	USART3INT,					//USART3 Global Interrupt
	EXTI15_10,					//EXTI Line[15:10] Interrupts
	RTC_ALARM,					//RTC Alarms(A and B) Through EXTI Line Interrupt
	OTG_FS_WKUP,				//USB On-The-Go FS WakeUp Through EXTI Line Interrupt
	TIM8_BRK_TIM12,				//TIM8 Break Interrupt and TIM12 Global Interrupt
	TIM8_UP_TIM13,				//TIM8 Update Interrupt and TIM13 Global Interrupt
	TIM8_TRG_COM_TIM14,			//TIM8 Trigger and Communcation Interrupts and TIM14 Global Interrupt
	TIM8_CC,					//TIM8 Capture Compare Interrupt
	DMA1__STREAM7,				//DMA1 Stream7 Global Interrupt
	FSMC,						//FSMC Global Interrupt
	SDIO,						//SDIO Global Interrupt
	TIM5,						//TIM5 Global Interrupt
	SPI3,						//SPI3 Global Interrupt
	UART4,						//UART4 Global Interrupt
	UART5,						//UART5 Global Interrupt
	TIM6_DAC,					//TIM6 Global Interrupt / DAC1 and DAC2 underrun Error Interrupt
	TIM7,						//TIM7 Global Interrupt
	DMA2__STREAM0,				//DMA2 Stream 0 Global Interrupt
	DMA2__STREAM1,				//DMA2 Stream 1 Global Interrupt
	DMA2__STREAM2,				//DMA2 Stream 2 Global Interrupt
	DMA2__STREAM3,				//DMA2 Stream 3 Global Interrupt
	DMA2__STREAM4,				//DMA2 Stream 4 Global Interrupt
	ETH,						//Ethernet Global Interrupt
	ETH_WKUP,					//Ethernet Wakeup Through EXTI Line Interrupt
	CAN2_TX,					//CAN2 TX  Interrupt
	CAN2_RX0,					//CAN2 RX0 Interrupt
	CAN2_RX1,					//CAN2 RX1 Interrupt
	CAN2_SCE,					//CAN2 SCE Interrupt
	OTG_FS,						//USB On The Go FS Global Interrupt
	DMA2__STREAM5,				//DMA2 Stream 5 Global Interrupt
	DMA2__STREAM6,				//DMA2 Stream 6 Global Interrupt
	DMA2__STREAM7,				//DMA2 Stream 7 Global Interrupt
	USART6,						//USART6 Global Interrupt
	I2C3_EV,					//I2C3 Event Interrupt
	I2C3_ER,					//I2C3 Error Interrup
	OTG_HS_EP1_OUT,				//USB On The GO HS End Point 1 Out Global Interrupt
	OTG_HS_EP1_IN,				//USB On The GO HS End Point 1 In Global Interrupt
	OTG_HS_WKUP,				//USB On The GO HS Wakup Through EXTI Interrupt
	OTG_HS,						//USB On The GO HS Global Interrupt
	DCMI,						//DCMI Global Interrupt
	CRYP,						//CRYP Crypto  Global Interrupt
	HASH_RNG,					//Hash and Rng Global Interrupt
	FPU,						//FPU Global Interrupt
	UART7,						//UART7 Global Interrupt
	UART8,						//UART8 Global Interrupt
	SPI4,						//SPI4  Global Interrupt
	SPI5,						//SPI5  Global Interrupt
	SPI6,						//SPI6  Global Interrupt
	SAI1,						//SAI1  Global Interrupt
	LCD_TFT,					//LTDC  Global Interrupt
	LCD_TFT_Error,				//LTDC  Global Error Interrupt
	DMA2D						//DMA2D Global Interrupt
};

void vidNVIC_Init(void);
void vidNVIC_SetPriority(u8 u8u8Idx, u8 u8Priority);
void vidNVIC_Enable(u8 u8u8Idx);
void vidNVIC_Disable(u8 u8u8Idx);
void vidNVIC_SetPending(u8 u8u8Idx);
void vidNVIC_ClearPending(u8 u8u8Idx);
u8 u8NVIC_GetActiveFlag(u8 u8u8Idx);


#endif /* NVIC_INIT_H_ */
