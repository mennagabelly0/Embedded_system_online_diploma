/*
 * RCC_DRIVER_STM32F103C6.h
 *
 *  Created on: Jan 25, 2024
 *      Author: HFCS
 */

#ifndef INC_RCC_DRIVER_STM32F103C6_H_
#define INC_RCC_DRIVER_STM32F103C6_H_

//-----------------------------
//Includes
//-----------------------------

#include "STM32F103X6.h"
#include "GPIO_DRIVER_STM32F103C6.h"
#include "EXTI_DRIVER_STM32F103C6.h"

#define HSE_Clock		(uint32_t)16000000
#define HSI_RC_CLK		(uint32_t)8000000

uint32_t MCAL_RCC_Get_System_CLK_Frequency(void) ;
uint32_t MCAL_RCC_Get_HCLK_Frequency(void) ;
uint32_t MCAL_RCC_Get_PCLK1_Frequency(void) ;
uint32_t MCAL_RCC_Get_PCLK2_Frequency(void) ;


#endif /* INC_RCC_DRIVER_STM32F103C6_H_ */
