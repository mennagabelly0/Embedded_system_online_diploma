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
toggle\ led\ as\ an\ Interrupt.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
toggle\ led\ as\ an\ Interrupt.list \

OBJCOPY_BIN += \
toggle\ led\ as\ an\ Interrupt.bin \


# All Target
all: toggle\ led\ as\ an\ Interrupt.elf secondary-outputs

# Tool invocations
toggle\ led\ as\ an\ Interrupt.elf: $(OBJS) $(USER_OBJS) D:\learn\ in\ depth\ Assignment\Unit-6\lesson\ 3\toggle\ led\ as\ an\ Interrupt\STM32F103C6UX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "toggle led as an Interrupt.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\learn in depth Assignment\Unit-6\lesson 3\toggle led as an Interrupt\STM32F103C6UX_FLASH.ld" --specs=nosys.specs -Wl,-Map="toggle led as an Interrupt.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

toggle\ led\ as\ an\ Interrupt.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "toggle led as an Interrupt.list"
	@echo 'Finished building: $@'
	@echo ' '

toggle\ led\ as\ an\ Interrupt.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "toggle led as an Interrupt.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
