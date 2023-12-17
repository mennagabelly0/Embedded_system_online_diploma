################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
PULL-UP-DOWN_AND_HighZ_GPIO.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
PULL-UP-DOWN_AND_HighZ_GPIO.list \

OBJCOPY_HEX += \
PULL-UP-DOWN_AND_HighZ_GPIO.hex \

OBJCOPY_BIN += \
PULL-UP-DOWN_AND_HighZ_GPIO.bin \


# All Target
all: PULL-UP-DOWN_AND_HighZ_GPIO.elf secondary-outputs

# Tool invocations
PULL-UP-DOWN_AND_HighZ_GPIO.elf: $(OBJS) $(USER_OBJS) D:\learn\ in\ depth\ Assignment\Unit-7\lesson\ 1\PULL-UP-DOWN_AND_HighZ_GPIO\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "PULL-UP-DOWN_AND_HighZ_GPIO.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\learn in depth Assignment\Unit-7\lesson 1\PULL-UP-DOWN_AND_HighZ_GPIO\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="PULL-UP-DOWN_AND_HighZ_GPIO.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

PULL-UP-DOWN_AND_HighZ_GPIO.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "PULL-UP-DOWN_AND_HighZ_GPIO.list"
	@echo 'Finished building: $@'
	@echo ' '

PULL-UP-DOWN_AND_HighZ_GPIO.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "PULL-UP-DOWN_AND_HighZ_GPIO.hex"
	@echo 'Finished building: $@'
	@echo ' '

PULL-UP-DOWN_AND_HighZ_GPIO.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "PULL-UP-DOWN_AND_HighZ_GPIO.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
