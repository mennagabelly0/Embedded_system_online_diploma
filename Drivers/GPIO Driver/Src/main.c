/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Menna_Gabely
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
#include "GPIO_DRIVER_STM32F103C6.h"
#include "STM32F103X6.h"

void clock_init(){
	// Enable clock GPIOA
	//RCC_APB2ENR |= RCC_IOPAEN ;
	RCC_GPIOA_CLK_EN() ;

	// Enable clock GPIOB
	//RCC_APB2ENR |= (1<<3) ;
	RCC_GPIOB_CLK_EN() ;
}

void GPIO_init(){

	GPIO_PinConfig_t PinCfg ;
// PA1 Input HighZ Floating input (reset state)
	PinCfg.GPIO_PinNumber = GPIO_PIN_1 ;
	PinCfg.GPIO_MODE = GPIO_MODE_Input_Floating ;
	MCAL_GPIO_Init(GPIOA, &PinCfg) ;

	//PORTB1 is an output as a PUSH/PULL Mode
	// CNFy[1:0] : 00: General purpose output push-pull
	//MODEy[1:0]: 01: Output mode, max speed 10 MHz.
	PinCfg.GPIO_PinNumber = GPIO_PIN_1 ;
	PinCfg.GPIO_MODE = GPIO_MODE_Output_push_pull ;
	PinCfg.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
	MCAL_GPIO_Init(GPIOB, &PinCfg) ;

	/////////////////////////////////////////////////

	// PA13 Input HighZ Floating input (reset state)
	PinCfg.GPIO_PinNumber = GPIO_PIN_13 ;
	PinCfg.GPIO_MODE = GPIO_MODE_Input_Floating ;
	MCAL_GPIO_Init(GPIOA, &PinCfg) ;

	//PORTB13 is an output as a PUSH/PULL Mode
	PinCfg.GPIO_PinNumber = GPIO_PIN_13 ;
	PinCfg.GPIO_MODE = GPIO_MODE_Output_push_pull ;
	PinCfg.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
	MCAL_GPIO_Init(GPIOB, &PinCfg) ;

	}

void WAITING(uint32_t time){
	uint32_t i ,j ;
	for(i= 0 ; i<time ; i++)
		for(j= 0 ; j<255 ; j++) ;
}
int main(void)
{
	clock_init() ;
	GPIO_init() ;

	while(1){

		if(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0){
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1) ;
			while (MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0) ; // single pressing
		}
 // EXTERNAL PULL DOWN
		if(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) == 1){
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13) ;// multiple pressing
		}
		WAITING(1);
	}

}
