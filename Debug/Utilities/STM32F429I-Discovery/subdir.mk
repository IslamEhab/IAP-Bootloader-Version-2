################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/STM32F429I-Discovery/stm32f429i_discovery.c \
../Utilities/STM32F429I-Discovery/stm32f429i_discovery_i2c_ee.c \
../Utilities/STM32F429I-Discovery/stm32f429i_discovery_ioe.c \
../Utilities/STM32F429I-Discovery/stm32f429i_discovery_l3gd20.c \
../Utilities/STM32F429I-Discovery/stm32f429i_discovery_lcd.c \
../Utilities/STM32F429I-Discovery/stm32f429i_discovery_sdram.c 

OBJS += \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery.o \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_i2c_ee.o \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_ioe.o \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_l3gd20.o \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_lcd.o \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_sdram.o 

C_DEPS += \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery.d \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_i2c_ee.d \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_ioe.d \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_l3gd20.d \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_lcd.d \
./Utilities/STM32F429I-Discovery/stm32f429i_discovery_sdram.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/STM32F429I-Discovery/%.o: ../Utilities/STM32F429I-Discovery/%.c
	arm-atollic-eabi-gcc -c "$<" -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=gnu11 -DSTM32F42_43xxx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DUSE_STM32F429I_DISCO -I../src -I../Drivers/CRC -I../Drivers/DEBUG -I../Drivers/DMA -I../Drivers/EXTI -I../Drivers/FLASH -I../Drivers/GPIO -I../Drivers/NVIC -I../Drivers/RCC -I../Drivers/STD_and_MATH -I../Drivers/SYSTICK -I../Drivers/USART -I../Libraries/CMSIS/Include -I../Libraries/Device/ST/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Utilities/Common -I../Utilities/STM32F429I-Discovery -O0 -ffunction-sections -fdata-sections -g -fstack-usage -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -specs=nano.specs -o "$@"

