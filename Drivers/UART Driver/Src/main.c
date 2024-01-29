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
#include "USART_DRIVER_STM32F103C6.h"

void Clock_init()
{
	// Enable Clock
	RCC_GPIOA_CLK_EN() ;
	RCC_GPIOB_CLK_EN() ;
	RCC_AFIO_CLK_EN() ;


}

unsigned char ch ;

//// related to Interrupt Mechanism
//void Menna_CallBack(void){
//
//	MCAL_UART_Receive_Data(USART1 , &ch , Disable) ;
//	MCAL_UART_Send_Data(USART1 , &ch , Disable) ;
//}



int main(void)
{
	UART_Config uartCFG ;

	Clock_init() ;

	uartCFG.BaudRate = UART_BaudRate_115200 ;
	uartCFG.HW_Flow_Conterl = UART_HW_Flow_Conterl_NONE ;

//	// related to Interrupt Mechanism
//	uartCFG.IRQ_Enable = UART_IRQ_Enable_RXNEIE ;
//	uartCFG.P_IRQ_CallBack = Menna_CallBack ;


		//Related to Polling_Michanism
	uartCFG.IRQ_Enable = UART_IRQ_Enable_NONE ;
	uartCFG.P_IRQ_CallBack = NULL ;


	uartCFG.Parity = UART_Parity_NONE ;
	uartCFG.Payload_length = UART_Payload_length_8B ;
	uartCFG.Stop_Bits = UART_Stop_Bits_1 ;
	uartCFG.UART_Mode = UART_Mode_TX_RX ;

	MCAL_UART_Init(USART1,&uartCFG) ;

	MCAL_UART_GPIO_Set_Pins(USART1) ;

	while(1)
	{
		//Related to Polling_Michanism
		MCAL_UART_Receive_Data(USART1 , &ch , Enable) ;
		MCAL_UART_Send_Data(USART1 , &ch , Enable) ;


	}
}
