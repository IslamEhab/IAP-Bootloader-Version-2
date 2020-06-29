################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include Utilities/STM32F429I-Discovery/subdir.mk
-include Utilities/Common/subdir.mk
-include Libraries/STM32F4xx_StdPeriph_Driver/src/subdir.mk
-include Drivers/USART/subdir.mk
-include Drivers/SYSTICK/subdir.mk
-include Drivers/RCC/subdir.mk
-include Drivers/NVIC/subdir.mk
-include Drivers/GPIO/subdir.mk
-include Drivers/FLASH/subdir.mk
-include Drivers/EXTI/subdir.mk
-include Drivers/DMA/subdir.mk
-include Drivers/DEBUG/subdir.mk
-include Drivers/CRC/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECOUTPUTBUILDVAR += \
EXECUTABLES \


# All Target
all: IAP_BootLoader.elf secondary-outputs

# Tool invocations
IAP_BootLoader.elf: $(OBJS) $(USER_OBJS)
	arm-atollic-eabi-gcc -o "IAP_BootLoader.elf" $(OBJS) $(USER_OBJS) $(LIBS) -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -T"../stm32f4_flash.ld" -specs=nosys.specs -static -Wl,-cref,-u,Reset_Handler "-Wl,-Map=IAP_BootLoader.map" -Wl,--gc-sections -Wl,--defsym=malloc_getpagesize_P=0x80 -Wl,--start-group -lc -lm -Wl,--end-group -specs=nano.specs

EXECUTABLES: IAP_BootLoader.elf $(EXECUTABLES)
	"C:\Program Files (x86)\Atollic\TrueSTUDIO for STM32 9.3.0\ide\jre\bin\java" -jar "C:\Program Files (x86)\Atollic\TrueSTUDIO for STM32 9.3.0\Tools\arm-atollic-reports.jar" convert-hex sizeinfo list IAP_BootLoader.elf

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(SECOUTPUTBUILDVAR)$(OBJS)$(C_DEPS) IAP_BootLoader.elf
	-@echo ' '

secondary-outputs: $(SECOUTPUTBUILDVAR)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
