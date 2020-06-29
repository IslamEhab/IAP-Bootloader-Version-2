#include "main.h"


extern volatile u32 DELAY_X;


static void Hardware_Init(void);
static void GPIO_Peripheral_Configuration(void);

void LED_Play(void)
{
	u8 i = 0;
	for(i=7 ; i<14 ; i++)
	{
		GPIOG ->ODR = (0x1<<i);
		_delay_ms(500);
	}
}

int main(void)
{
	Hardware_Init();
	GPIO_Peripheral_Configuration();

	while(1)
	{
		LED_Play();
	}
}

/**
  * @brief Hardware Initialization Function
  * @param None
  * @retval None
  */
static void Hardware_Init(void)
{
	/* Enable IRQ because it was disabled in the bootloader before Jump here */
	asm("MOV R0,#0");
	asm("MSR PRIMASK,R0");

	/* Set Vector table to the first adddress of the sector 2 (SP) */
	SCB_VTOR = (SECTOR2_BASE_ADDRESS);

	vidRCC_Init();
	vidNVIC_Init();

	vidSYSTICK_Init(89999);

	vidRCC_EnableClock(RCC_GPIOG);

	vidGPIO_Init_Reg();



}

/**
  * @brief 	GPIO Peripherals Initialization Function
  * @param 	None
  * @retval None
  */
static void GPIO_Peripheral_Configuration(void)
{
	GPIO_PIN_INIT hgpio = {0};

	/* Configuration for PushButton PA0 */
	hgpio.GPIO_PIN		= PIN0;
	hgpio.GPIO_MODE		= GPIO_MODE_IN;
	hgpio.GPIO_PULL		= GPIO_PULL_DOWN;
	hgpio.GPIO_OUT		= 0;
	hgpio.GPIO_SPEED	= GPIO_SPEED_LOW;

	vidGPIO_Init(GPIOA, &hgpio);

	 /* Configuration for LEDs PG13, PG14 */
	hgpio.GPIO_PIN		= PIN13;
	hgpio.GPIO_MODE		= GPIO_MODE_GPO;
	hgpio.GPIO_OUT		= GPIO_OUT_PP;
	hgpio.GPIO_PULL		= GPIO_PULL_NO;
	hgpio.GPIO_SPEED	= GPIO_SPEED_HIGH;
	vidGPIO_Init(GPIOG,&hgpio);

	hgpio.GPIO_PIN		= PIN12;
	vidGPIO_Init(GPIOG,&hgpio);

	hgpio.GPIO_PIN		= PIN11;
	vidGPIO_Init(GPIOG,&hgpio);

	hgpio.GPIO_PIN		= PIN10;
	vidGPIO_Init(GPIOG,&hgpio);

	hgpio.GPIO_PIN		= PIN9;
	vidGPIO_Init(GPIOG,&hgpio);

	hgpio.GPIO_PIN		= PIN8;
	vidGPIO_Init(GPIOG,&hgpio);

	hgpio.GPIO_PIN		= PIN7;
	vidGPIO_Init(GPIOG,&hgpio);


}


