################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../src/startup_stm32f429x.s 

C_SRCS += \
../src/main.c \
../src/stm32f4xx_it.c \
../src/system_stm32f4xx.c \
../src/tiny_printf.c 

OBJS += \
./src/main.o \
./src/startup_stm32f429x.o \
./src/stm32f4xx_it.o \
./src/system_stm32f4xx.o \
./src/tiny_printf.o 

C_DEPS += \
./src/main.d \
./src/stm32f4xx_it.d \
./src/system_stm32f4xx.d \
./src/tiny_printf.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	arm-atollic-eabi-gcc -c "$<" -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=gnu11 -DSTM32F42_43xxx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DUSE_STM32F429I_DISCO -I../src -I../Drivers/CRC -I../Drivers/DEBUG -I../Drivers/DMA -I../Drivers/EXTI -I../Drivers/FLASH -I../Drivers/GPIO -I../Drivers/NVIC -I../Drivers/RCC -I../Drivers/STD_and_MATH -I../Drivers/SYSTICK -I../Drivers/USART -I../Libraries/CMSIS/Include -I../Libraries/Device/ST/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Utilities/Common -I../Utilities/STM32F429I-Discovery -O0 -ffunction-sections -fdata-sections -g -fstack-usage -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -specs=nano.specs -o "$@"
src/%.o: ../src/%.s
	arm-atollic-eabi-gcc -c -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F42_43xxx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DUSE_STM32F429I_DISCO -I../src -I../Libraries/CMSIS/Include -I../Libraries/Device/ST/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Utilities/Common -I../Utilities/STM32F429I-Discovery -g -Wa,--warn -x assembler-with-cpp -specs=nano.specs -o "$@" "$<"

