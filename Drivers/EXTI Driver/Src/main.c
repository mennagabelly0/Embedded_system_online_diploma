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
#include "STM32F103X6.h"
#include "GPIO_DRIVER_STM32F103C6.h"
#include "EXTI_DRIVER_STM32F103C6.h"
#include "lcd.h"
#include "keypad.h"

unsigned int IRQ_Flag = 0 ;

void WAITING(uint32_t time){
	uint32_t i ,j ;
	for(i= 0 ; i<time ; i++)
		for(j= 0 ; j<255 ; j++) ;
}
void EXTI9_CallBack(void ){
	IRQ_Flag = 1 ;
	LCD_WRITE_STRING("IRQ EXTI9 IS HAPPEND _|-..") ;
	WAITING(1000) ;

}
int main(void)
{
	// Enable Clock
	RCC_GPIOA_CLK_EN() ;
	RCC_GPIOB_CLK_EN() ;
	RCC_AFIO_CLK_EN() ;

	LCD_INIT() ;
	LCD_clear_screen() ;


	EXTI_PinConfig_t EXTI_CFG ;
	EXTI_CFG.EXTI_PIN = EXTI9PB9 ;
	EXTI_CFG.Tregger_case = EXTI_Trigger_Rising ;
	EXTI_CFG.P_IRQ_CallBack = EXTI9_CallBack ;
	EXTI_CFG.IRQ_Enable = EXTI_IRQ_Enable ;

	MCAL_EXTI_GPIO_Init(&EXTI_CFG) ;

	IRQ_Flag = 1 ;

	while(1){
		if (IRQ_Flag ){
			LCD_clear_screen() ;
			IRQ_Flag = 0 ;
		}
	}
}
