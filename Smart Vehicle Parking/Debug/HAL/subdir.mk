################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/I2C_Slave_EEPROM.c \
../HAL/Keypad_ME.c \
../HAL/LCD_ME.c \
../HAL/Servo_Motor.c \
../HAL/keypad.c \
../HAL/lcd.c 

OBJS += \
./HAL/I2C_Slave_EEPROM.o \
./HAL/Keypad_ME.o \
./HAL/LCD_ME.o \
./HAL/Servo_Motor.o \
./HAL/keypad.o \
./HAL/lcd.o 

C_DEPS += \
./HAL/I2C_Slave_EEPROM.d \
./HAL/Keypad_ME.d \
./HAL/LCD_ME.d \
./HAL/Servo_Motor.d \
./HAL/keypad.d \
./HAL/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/I2C_Slave_EEPROM.o: ../HAL/I2C_Slave_EEPROM.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/learn in depth Assignment/DRIVERS/Drivers/HAL/Includes" -I"D:/learn in depth Assignment/DRIVERS/Drivers/STM32_103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/I2C_Slave_EEPROM.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/Keypad_ME.o: ../HAL/Keypad_ME.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/learn in depth Assignment/DRIVERS/Drivers/HAL/Includes" -I"D:/learn in depth Assignment/DRIVERS/Drivers/STM32_103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/Keypad_ME.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/LCD_ME.o: ../HAL/LCD_ME.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/learn in depth Assignment/DRIVERS/Drivers/HAL/Includes" -I"D:/learn in depth Assignment/DRIVERS/Drivers/STM32_103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/LCD_ME.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/Servo_Motor.o: ../HAL/Servo_Motor.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/learn in depth Assignment/DRIVERS/Drivers/HAL/Includes" -I"D:/learn in depth Assignment/DRIVERS/Drivers/STM32_103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/Servo_Motor.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/keypad.o: ../HAL/keypad.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/learn in depth Assignment/DRIVERS/Drivers/HAL/Includes" -I"D:/learn in depth Assignment/DRIVERS/Drivers/STM32_103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/keypad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/lcd.o: ../HAL/lcd.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/learn in depth Assignment/DRIVERS/Drivers/HAL/Includes" -I"D:/learn in depth Assignment/DRIVERS/Drivers/STM32_103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/lcd.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

