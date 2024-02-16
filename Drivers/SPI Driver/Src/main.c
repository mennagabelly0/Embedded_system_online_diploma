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
#include "RCC_DRIVER_STM32F103C6.h"
#include "SPI_DRIVER_STM32F103C6.h"


//#define MCU_Act_As_Master
#define MCU_Act_As_Slave

unsigned char ch ;

void Clock_init()
{
	// Enable Clock
	RCC_GPIOA_CLK_EN() ;
	RCC_GPIOB_CLK_EN() ;
	RCC_AFIO_CLK_EN() ;


}

// related to Interrupt Mechanism
void Menna_SPI1_IRQ_CallBack(struct S_IRQ_SRC irq_src){
#ifdef MCU_Act_As_Slave
	if(irq_src.RXEN){
		ch = 0xF ;
		MCAL_SPI_Send_Receive_Data(SPI1, &ch, Polling_Disable) ;
		MCAL_UART_Send_Data(USART1, &ch, Enable) ;
	}
#endif


}


// related to Interrupt Mechanism
void Menna_UART1_CallBack(void){
#ifdef MCU_Act_As_Master
	MCAL_UART_Receive_Data(USART1 , &ch , Disable) ;
	MCAL_UART_Send_Data(USART1 , &ch , Enable) ;
	// Send Data to SPI
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0) ;
	MCAL_SPI_Send_Receive_Data(SPI1, &ch, Polling_Enable) ;
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1) ;
#endif


}

int main(void)
{
	UART_Config uartCFG ;
	SPI_Congig spi1CFG ;
	GPIO_PinConfig_t gpioCFG ;

	Clock_init() ;

	// ===================	UART1	===================
	// PA9 => TX
	// PA10 => RX
	// PA11 => CTS
	// PA12 => RTS

	uartCFG.BaudRate = UART_BaudRate_115200 ;
	uartCFG.HW_Flow_Conterl = UART_HW_Flow_Conterl_NONE ;

	// related to Interrupt Mechanism
	uartCFG.IRQ_Enable = UART_IRQ_Enable_RXNEIE ;
	uartCFG.P_IRQ_CallBack = Menna_UART1_CallBack ;

	//Related to Polling_Michanism
	//uartCFG.IRQ_Enable = UART_IRQ_Enable_NONE ;
	//uartCFG.P_IRQ_CallBack = NULL ;


	uartCFG.Parity = UART_Parity_NONE ;
	uartCFG.Payload_length = UART_Payload_length_8B ;
	uartCFG.Stop_Bits = UART_Stop_Bits_1 ;
	uartCFG.UART_Mode = UART_Mode_TX_RX ;

	MCAL_UART_Init(USART1,&uartCFG) ;

	MCAL_UART_GPIO_Set_Pins(USART1) ;

	// ===================	SPI1	===================
	//SPI1_NSS  : PA4
	//SPI1_SCK  : PA5
	//SPI1_MISO : PA6
	//SPI1_MOSI : PA7

	// Comma Configuration Master / Slave
	spi1CFG.CLKPhese = SPI_CLKPhese_First_Edge_Clock_Transition ;
	spi1CFG.CLKPolarity = SPI_CLKPolarity_High_Idle ;
	spi1CFG.DataSize_Frame_Format = SPI_DataSize_Frame_Format_8Bit ;
	spi1CFG.Frame_Format = SPI_Frame_Format_MSB_transmitted_first ;
	// Assume by Default PCK = 8MHZ.
	spi1CFG.SPI_BaudRate_PreScaler = SPI_BaudRate_PreScaler_8 ;
	spi1CFG.Communication_Mode = SPI_Communication_Mode_Directinal_2Lines ;

#ifdef MCU_Act_As_Master
	spi1CFG.Device_Mode = SPI_Device_Mode_MASTER ;
	spi1CFG.IRQ_Enable = SPI_IRQ_Enable_NONE ;
	spi1CFG.NSS = SPI_NSS_Software_Internal_Set ;
	spi1CFG.P_IRQ_CallBack = NULL ;

	// Configuration SS PORTA PIN 4 By GPIO
	gpioCFG.GPIO_PinNumber = GPIO_PIN_4 ;
	gpioCFG.GPIO_MODE = GPIO_MODE_Output_push_pull ;
	gpioCFG.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
	MCAL_GPIO_Init(GPIOA, &gpioCFG) ;

	// Focus the Slave select (High) Idle Mode
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1) ;
#endif

#ifdef MCU_Act_As_Slave
	spi1CFG.Device_Mode = SPI_Device_Mode_SLAVE ;
	spi1CFG.IRQ_Enable = SPI_IRQ_Enable_RXNEIE ;
	spi1CFG.NSS = SPI_NSS_Hardware_Slave ;
	spi1CFG.P_IRQ_CallBack = Menna_SPI1_IRQ_CallBack ;
#endif

	MCAL_SPI_Init(SPI1, &spi1CFG) ;
	MCAL_SPI_GPIO_Set_Pins(SPI1) ;

// LOOP FOREEVER
	while(1)
	{
		//Related to Polling_Michanism
		//MCAL_UART_Receive_Data(USART1 , &ch , Enable) ;
		//MCAL_UART_Send_Data(USART1 , &ch , Enable) ;


	}
}
