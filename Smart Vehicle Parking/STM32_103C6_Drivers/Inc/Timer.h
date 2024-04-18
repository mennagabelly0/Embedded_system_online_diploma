/*
 * Timer.h
 *
 *  Created on: Mar 28, 2024
 *      Author: ENG.Menna Gabely.
 */


#ifndef INC_TIMER_H_
#define INC_TIMER_H_

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


#define RCC_APB1ENR                           *( volatile uint32_t *)(RCC_Base + 0x1C)
#define RCC_APB2ENR                           *( volatile uint32_t *)(RCC_Base + 0x18)





//TIMER2
#define TIM2_timer_Base                        0x40000000
#define TIM2_CNT                              *( volatile uint32_t *)(TIM2_timer_Base+0x24)
#define TIM2_CR1                              *( volatile uint32_t *)(TIM2_timer_Base+0x00)
#define TIM2_PSC                              *( volatile uint32_t *)(TIM2_timer_Base+0x28)
#define TIM2_SR                               *( volatile uint32_t *)(TIM2_timer_Base+0x10)
#define TIM2_DIER                             *( volatile uint32_t *)(TIM2_timer_Base+0x0c)
#define TIM2_ARR                              *( volatile uint32_t *)(TIM2_timer_Base+0x2c)



/*=================Timer2======================*/
void Timer2_init(void);
void dus(int us);
void dms(int ms);

#endif /* INC_TIMER_H_ */
