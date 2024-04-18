/*
 * Servo_Motor.h
 *
 *  Created on: Mar 28, 2024
 *      Author: HFCS
 */

#ifndef INCLUDES_SERVO_MOTOR_H_
#define INCLUDES_SERVO_MOTOR_H_

//-----------------------------
//Includes
//-----------------------------

#include "STM32F103X6.h"
#include "GPIO_DRIVER_STM32F103C6.h"
#include "EXTI_DRIVER_STM32F103C6.h"
#include "RCC_DRIVER_STM32F103C6.h"
#include "USART_DRIVER_STM32F103C6.h"
#include "SPI_DRIVER_STM32F103C6.h"
#include "I2C_DRIVER_STM32F103C6.h"
#include "I2C_Slave_EEPROM.h"
#include "Timer.h"


#define UP   1
#define Down 2


void Servo1_Entry_Gate_Init(void);
void Servo1_Entry_Gate(uint8_t Direction);


void Servo2_Exit_Gate_Init(void);
void Servo2_Exit_Gate(uint8_t Direction);
#endif /* INCLUDES_SERVO_MOTOR_H_ */
