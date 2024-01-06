################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32_103C6_Drivers/EXTI_DRIVER_STM32F103C6.c \
../STM32_103C6_Drivers/GPIO_DRIVER_STM32F103C6.c 

OBJS += \
./STM32_103C6_Drivers/EXTI_DRIVER_STM32F103C6.o \
./STM32_103C6_Drivers/GPIO_DRIVER_STM32F103C6.o 

C_DEPS += \
./STM32_103C6_Drivers/EXTI_DRIVER_STM32F103C6.d \
./STM32_103C6_Drivers/GPIO_DRIVER_STM32F103C6.d 


# Each subdirectory must supply rules for building sources it contributes
STM32_103C6_Drivers/EXTI_DRIVER_STM32F103C6.o: ../STM32_103C6_Drivers/EXTI_DRIVER_STM32F103C6.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/learn in depth Assignment/DRIVERS/Drivers/HAL/Includes" -I"D:/learn in depth Assignment/DRIVERS/Drivers/STM32_103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32_103C6_Drivers/EXTI_DRIVER_STM32F103C6.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
STM32_103C6_Drivers/GPIO_DRIVER_STM32F103C6.o: ../STM32_103C6_Drivers/GPIO_DRIVER_STM32F103C6.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/learn in depth Assignment/DRIVERS/Drivers/HAL/Includes" -I"D:/learn in depth Assignment/DRIVERS/Drivers/STM32_103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32_103C6_Drivers/GPIO_DRIVER_STM32F103C6.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

