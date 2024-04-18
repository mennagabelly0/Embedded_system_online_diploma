/*
 * debugUart.c
 *
 *  Created on: Apr 3, 2024
 *      Author: MENNA GABELY
 */

#include "USART_DRIVER_STM32F103C6.h"


/*
 * ===============================================
				"Generic Variables"
 * ===============================================
 */

// UART_Config* Global_UART_Config = NULL ;

UART_Config* Global_UART_Config[3] = {NULL,NULL,NULL} ;



/*
 * ===============================================
 * APIs Supported by "MCAL USART DRIVER"
 * ===============================================
 */


/**================================================================
 * @Fn					- MCAL_UART_Init
 * @brief 				- INIT UART
 * @param[in] 			- USARTx
 * @param[in] 			- UART_Config : All UART Configuration EXTI_PinConfig_t .
 * @retval				- NONE
 * Note					- Support for new Asynchronous mode & Clock 8MHZ
 *
 *
 */

void MCAL_UART_Init(USART_Typedef* USARTx , UART_Config* UART_Config)
{
	uint32_t Pclk , BRR ;

	//Global_UART_Config = UART_Config ;

	// Enable The Clock for  given USART Peripheral
	if(USARTx == USART1){
		RCC_USART1_CLK_EN() ;
	    Global_UART_Config[0] = UART_Config ;
	}
	else if(USARTx == USART2){
		RCC_USART2_CLK_EN() ;
	    Global_UART_Config[1] = UART_Config ;
	}

	else if(USARTx == USART3){
		RCC_USART3_CLK_EN() ;
	    Global_UART_Config[2] = UART_Config ;
	}
	// Enable UART Module
	//Bit 13 UE: USART enable
	USARTx->USART_CR1 |= 1<<13 ;

	// Enable USART TX and RX Engines according to the USART_MODE Configuration item
	// USART_CR1 Bit 3 TE: Transmitter enable , Bit 2 RE: Receiver enable
	USARTx->USART_CR1 |= UART_Config->UART_Mode ;

	// PAYLOAD Width
	// USARTx->USART_CR1 Bit 12 M: Word length
	USARTx->USART_CR1 |= UART_Config->Payload_length ;

	// Configuration of Parity Control bit fields
	// USARTx->USART_CR1 Bit 10 PCE: Parity control enable , Bit 9 PS: Parity selection
	USARTx->USART_CR1 |= UART_Config->Parity ;

	// Configuration of the number of stop bits
	// USARTx->USART_CR2 Bits 13:12 STOP: STOP bits
	USARTx->USART_CR2 |= UART_Config->Stop_Bits ;

	// Configuration of USART Hardware Flow Control
	// USARTx->USART_CR3 Bit 9 CTSE: CTS enable , Bit 8 RTSE: RTS enable
	USARTx->USART_CR3 |= UART_Config->HW_Flow_Conterl ;


	// Configuration of BRR (Baudrate register)
	// PCLK1 for USART 2 , 3
	// PCLK2 for USART 1

	if( USARTx == USART1 ){
		Pclk = MCAL_RCC_Get_PCLK2_Frequency() ;
	}
	else {
		Pclk = MCAL_RCC_Get_PCLK1_Frequency() ;
	}

	BRR = UART_BRR_Register(Pclk , UART_Config->BaudRate ) ;
	USARTx->USART_BRR = BRR ;

	// Enable / Disable Interrupt
	// USART_CR1
	if(UART_Config->IRQ_Enable != UART_IRQ_Enable_NONE  ){
		USARTx->USART_CR1 |= (UART_Config->IRQ_Enable) ;

		//  Enable For NVIC UARTx IRQ
		if(USARTx == USART1)
			NVIC_IRQ37_USART1_Enable() ;
		else if(USARTx == USART2)
			NVIC_IRQ38_USART2_Enable() ;
		else if(USARTx == USART3)
			NVIC_IRQ39_USART3_Enable() ;

	}


}



/**================================================================
 * @Fn					- MCAL_UART_DeInit
 * @brief 				- DEINIT UART
 * @param[in] 			- USARTx
 * @param[in] 			- NONE
 * @retval				- NONE
 * Note					- Support for new Asynchronous mode & Clock 8MHZ
 *
 *
 */

void MCAL_UART_DeInit(USART_Typedef* USARTx )
{
	if( USARTx == USART1){
		RCC_USART1_Reset() ;
		NVIC_IRQ37_USART1_Disable() ;
	}
	else if( USARTx == USART2){
		RCC_USART2_Reset() ;
		NVIC_IRQ38_USART2_Disable() ;
	}
	else if( USARTx == USART3){
		RCC_USART3_Reset() ;
		NVIC_IRQ39_USART3_Disable() ;
	}

}

/*
 * This functions is used by UART driver to get the index of the global array for the used instance
 * */
static uint8_t Which_UART(USART_Typedef* USARTx){
	if(USARTx == USART1)
	{
		return 0;
	}
	else if(USARTx == USART2)
	{
		return 1;
	}
	else if(USARTx == USART3)
	{
		return 3;
	}
	return 4;		//will cause error for user when he uses wrong address for USARTx
}


/**================================================================
 * @Fn					- MCAL_UART_GPIO_Set_Pins
 * @brief 				- UART GPIO SET PIN
 * @param[in] 			- USARTx
 * @param[in] 			- NONE
 * @retval				- NONE
 * Note					- NONE
 *
 *
 */

void MCAL_UART_GPIO_Set_Pins(USART_Typedef* USARTx)
{
	GPIO_PinConfig_t PINCFG ;
	if(USARTx == USART1)
	{
		// PA9 => TX
		// PA10 => RX
		// PA11 => CTS
		// PA12 => RTS

		// PA9 => TX
		PINCFG.GPIO_PinNumber = GPIO_PIN_9 ;
		PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_Push_pull ;
		PINCFG.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
		MCAL_GPIO_Init(GPIOA, &PINCFG) ;

		// PA10 => RX
		PINCFG.GPIO_PinNumber = GPIO_PIN_10 ;
		PINCFG.GPIO_MODE = GPIO_MODE_Input_Floating ;
		MCAL_GPIO_Init(GPIOA, &PINCFG) ;

		// PA11 => CTS
		// PA12 => RTS
		if(Global_UART_Config[0]->HW_Flow_Conterl== UART_HW_Flow_Conterl_CTS || Global_UART_Config[0]->HW_Flow_Conterl == UART_HW_Flow_Conterl_RTS_CTS)
		{
			// PA11 => CTS
			PINCFG.GPIO_PinNumber = GPIO_PIN_11 ;
			PINCFG.GPIO_MODE = GPIO_MODE_Input_Floating ;
			MCAL_GPIO_Init(GPIOA, &PINCFG) ;

		}
		else if(Global_UART_Config[0]->HW_Flow_Conterl == UART_HW_Flow_Conterl_RTS || Global_UART_Config[0]->HW_Flow_Conterl == UART_HW_Flow_Conterl_RTS_CTS)
		{
			// PA12 => RTS
			PINCFG.GPIO_PinNumber = GPIO_PIN_12 ;
			PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_Push_pull ;
			PINCFG.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
			MCAL_GPIO_Init(GPIOA, &PINCFG) ;

		}


	}
	else if(USARTx == USART2)
	{
		// PA2 => TX
		// PA3 => RX
		// PA0 => CTS
		// PA1 => RTS

		// PA2 => TX
		PINCFG.GPIO_PinNumber = GPIO_PIN_2 ;
		PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_Push_pull ;
		PINCFG.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
		MCAL_GPIO_Init(GPIOA, &PINCFG) ;

		// PA3 => RX
		PINCFG.GPIO_PinNumber = GPIO_PIN_3 ;
		PINCFG.GPIO_MODE = GPIO_MODE_Input_Floating ;
		MCAL_GPIO_Init(GPIOA, &PINCFG) ;

		// PA0 => CTS
		// PA1 => RTS
		if(Global_UART_Config[1]->HW_Flow_Conterl == UART_HW_Flow_Conterl_CTS || Global_UART_Config[1]->HW_Flow_Conterl == UART_HW_Flow_Conterl_RTS_CTS)
		{
			// PA0 => CTS
			PINCFG.GPIO_PinNumber = GPIO_PIN_0 ;
			PINCFG.GPIO_MODE = GPIO_MODE_Input_Floating ;
			MCAL_GPIO_Init(GPIOA, &PINCFG) ;

		}
		else if(Global_UART_Config[1]->HW_Flow_Conterl == UART_HW_Flow_Conterl_RTS || Global_UART_Config[1]->HW_Flow_Conterl == UART_HW_Flow_Conterl_RTS_CTS)
		{
			// PA1 => RTS
			PINCFG.GPIO_PinNumber = GPIO_PIN_1 ;
			PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_Push_pull ;
			PINCFG.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
			MCAL_GPIO_Init(GPIOA, &PINCFG) ;

		}


	}
	else if(USARTx == USART3)
	{
		// PB10 => TX
		// PB11 => RX
		// PB13 => CTS
		// PB14 => RTS

		// PB10 => TX
		PINCFG.GPIO_PinNumber = GPIO_PIN_10 ;
		PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_Push_pull ;
		PINCFG.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
		MCAL_GPIO_Init(GPIOB, &PINCFG) ;

		// PB11 => RX
		PINCFG.GPIO_PinNumber = GPIO_PIN_11 ;
		PINCFG.GPIO_MODE = GPIO_MODE_Input_Floating ;
		MCAL_GPIO_Init(GPIOB, &PINCFG) ;

		// PB13 => CTS
		// PA14 => RTS
		if(Global_UART_Config[2]->HW_Flow_Conterl == UART_HW_Flow_Conterl_CTS || Global_UART_Config[2]->HW_Flow_Conterl == UART_HW_Flow_Conterl_RTS_CTS)
		{
			// PB13 => CTS
			PINCFG.GPIO_PinNumber = GPIO_PIN_13 ;
			PINCFG.GPIO_MODE = GPIO_MODE_Input_Floating ;
			MCAL_GPIO_Init(GPIOB, &PINCFG) ;

		}
		else if(Global_UART_Config[2]->HW_Flow_Conterl == UART_HW_Flow_Conterl_RTS || Global_UART_Config[2]->HW_Flow_Conterl == UART_HW_Flow_Conterl_RTS_CTS)
		{
			// PB14 => RTS
			PINCFG.GPIO_PinNumber = GPIO_PIN_14 ;
			PINCFG.GPIO_MODE = GPIO_MODE_Output_AF_Push_pull ;
			PINCFG.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
			MCAL_GPIO_Init(GPIOB, &PINCFG) ;

		}
	}
}



/**================================================================
 * @Fn					- MCAL_UART_Send_Data
 * @brief 				- UART SEND DATA
 * @param[in] 			- USARTx
 * @param[in] 			- PTXBuffer
 * @param[in] 			- Polling_Enable
 * @retval				- NONE
 * Note					- NONE
 *
 *
 */

void MCAL_UART_Send_Data(USART_Typedef* USARTx , uint16_t* PTXBuffer , enum Polling_Michanism Polling_Enable)
{
	// Wait until TXE flag is set in the SR
	if(Polling_Enable == Enable)
	{
		while(!(USARTx->USART_SR  & (1<<7))) ;
	}

	uint8_t Gindex = Which_UART(USARTx) ;

	// Check The UART Length 8B OR 9B Frame
	/*
	    When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
		the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
		because it is replaced by the parity.
		When receiving with the parity enabled, the value read in the MSB bit is the received parity
		bit.
	 */
	if(Global_UART_Config[Gindex]->Payload_length == UART_Payload_length_9B){
		USARTx->USART_DR = (*PTXBuffer & (uint16_t)0x01FF ) ;
	}
	else {
		USARTx->USART_DR = (*PTXBuffer & (uint8_t)0xFF ) ;
	}

}


/**================================================================
 * @Fn					- MCAL_UART_Receive_Data
 * @brief 				- UART Receive Data
 * @param[in] 			- USARTx
 * @param[in] 			- PTXBuffer
 * @param[in] 			- Polling_Enable
 * @retval				- NONE
 * Note					- NONE
 *
 *
 */

void MCAL_UART_Receive_Data(USART_Typedef* USARTx , uint16_t* PTXBuffer , enum Polling_Michanism Polling_Enable)
{
	// Wait until RXNE flag is Set in SR
	if( Polling_Enable == Enable )
	{
		while (!(USARTx->USART_SR & (1<<5))) ;
	}

	uint8_t Gindex = Which_UART(USARTx) ;

	// Check The UART Length 8B OR 9B Frame
	/*
		    When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
			the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
			because it is replaced by the parity.
			When receiving with the parity enabled, the value read in the MSB bit is the received parity
			bit.
	 */
	// This 9 Bit
	if(Global_UART_Config[Gindex]->Payload_length == UART_Payload_length_9B)
	{
		if(Global_UART_Config[Gindex]->Parity == UART_Parity_NONE)
		{
			// NO Parity So All 9 Bit are conceder Data
			*((uint16_t*) PTXBuffer ) = USARTx->USART_DR ;

		}
		else
		{
			// Parity is used So 8 Bit will be used of data and 1 bit is Parity
			*((uint16_t*)PTXBuffer ) = (USARTx->USART_DR & (uint8_t)0xFF) ;

		}

	}
	else
	{
		// This 8 Bit
		if(Global_UART_Config[Gindex]->Parity == UART_Parity_NONE)
		{
			// NO Parity So All 8 Bit are conceder Data
			*((uint16_t*) PTXBuffer ) = (USARTx->USART_DR & (uint8_t)0xFF) ;

		}
		else
		{
			// Parity is used So 7 Bit will be used of data and 1 bit is Parity
			*((uint16_t*) PTXBuffer ) = (USARTx->USART_DR & (uint8_t)0x7F) ;
		}
	}
}



/**================================================================
 * @Fn					- MCAL_UART_Wait_Transmit_Complite
 * @brief 				- UART Wait Transmit Complete
 * @param[in] 			- USARTx
 * @param[in] 			- NONE
 * @retval				- NONE
 * Note					- NONE
 *
 *
 */

void MCAL_UART_Wait_Transmit_Complete(USART_Typedef* USARTx )
{
	// Wait TC flag is still Set in the RS
	while(!(USARTx->USART_SR & 1<<6)) ;

}



// ISR
void USART1_IRQHandler(void)
{
	Global_UART_Config[0]->P_IRQ_CallBack() ;

}

void USART2_IRQHandler(void)
{
	Global_UART_Config[1]->P_IRQ_CallBack() ;


}

void USART3_IRQHandler(void)
{
	Global_UART_Config[2]->P_IRQ_CallBack() ;


}


