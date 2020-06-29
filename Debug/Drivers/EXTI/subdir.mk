################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/EXTI/EXTI_Prog.c 

OBJS += \
./Drivers/EXTI/EXTI_Prog.o 

C_DEPS += \
./Drivers/EXTI/EXTI_Prog.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/EXTI/%.o: ../Drivers/EXTI/%.c
	arm-atollic-eabi-gcc -c "$<" -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=gnu11 -DSTM32F42_43xxx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DUSE_STM32F429I_DISCO -I../src -I../Drivers/CRC -I../Drivers/DEBUG -I../Drivers/DMA -I../Drivers/EXTI -I../Drivers/FLASH -I../Drivers/GPIO -I../Drivers/NVIC -I../Drivers/RCC -I../Drivers/STD_and_MATH -I../Drivers/SYSTICK -I../Drivers/USART -I../Libraries/CMSIS/Include -I../Libraries/Device/ST/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Utilities/Common -I../Utilities/STM32F429I-Discovery -O0 -ffunction-sections -fdata-sections -g -fstack-usage -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -specs=nano.specs -o "$@"

