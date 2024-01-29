/*
 * USART_DRIVER_STM32F103C6.h
 *
 *  Created on: Jan 25, 2024
 *      Author: HFCS
 */

#ifndef INC_USART_DRIVER_STM32F103C6_H_
#define INC_USART_DRIVER_STM32F103C6_H_

//-----------------------------
//Includes
//-----------------------------

#include "STM32F103X6.h"
#include "GPIO_DRIVER_STM32F103C6.h"
#include "EXTI_DRIVER_STM32F103C6.h"
#include "RCC_DRIVER_STM32F103C6.h"

//-----------------------------
// Configuration Structure
//-----------------------------
typedef struct{
	uint8_t 							UART_Mode ; 		 			 //specifies TX/RX Enable/Disable .
														 	 	 	 	 //This parameter must be set based on @Raf_UART_Mode_Define .
	uint32_t 							BaudRate ; 						//This member Configure the UART communication Baud Rate .
																		//This parameter must be set based on @Raf_UART_BaudRate_Define .
	uint8_t								Payload_length ;   				//specifies the number of data bits transmitted or received in frame.
																		//This parameter must be set based on @Raf_UART_Payload_length_Define .
	uint8_t								Parity ;						//specifies the Parity mode .
																		//@Raf_UART_Parity_Define .
	uint8_t								Stop_Bits ;						//specifies the number of stop bits transmitted .
																		//@Raf_UART_Stop_Bits_Define .
	uint8_t								HW_Flow_Conterl ;				//specifies whether the Hardware flow control mode is enable or disable .
																		//@Raf_UART_HW_Flow_Conterl_Define .
	uint8_t								IRQ_Enable ;					//Enable or Disable UART IRQ TX/RX .
																		//@Raf_UART_IRQ_Enable_Define , you can select 2 or 3 parameters .
	void(* P_IRQ_CallBack)(void) ;										//Set the C Function() which will be called once the IRQ happen.

}UART_Config;

//-----------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//Reference Macros:
//-*-*-*-*-*-*-*-*-*-*-*

// @Raf_UART_Mode_Define
#define UART_Mode_RX					(uint32_t)(1<<2) ; 				// Bit 2 RE: Receiver enable
#define UART_Mode_TX					(uint32_t)(1<<3) ;  			// Bit 3 TE: Transmitter enable
#define UART_Mode_TX_RX				    ((uint32_t)(1<<2 | 1<<3)) 		// Bit 2 RE: Receiver enable & Bit 3 TE: Transmitter enable .

// @Raf_UART_BaudRate_Define
#define UART_BaudRate_2400				2400
#define UART_BaudRate_9600				9600
#define UART_BaudRate_19200				19200
#define UART_BaudRate_57600				57600
#define UART_BaudRate_115200			115200
#define UART_BaudRate_230400			230400
#define UART_BaudRate_460800			460800
#define UART_BaudRate_921600			921600
#define UART_BaudRate_2250000			2250000
#define UART_BaudRate_4500000			4500000


// @Raf_UART_Payload_length_Define
     //Bit 12 M: Word length
#define UART_Payload_length_8B			(uint32_t)(0)       		  //0: 1 Start bit, 8 Data bits, n Stop bit
#define UART_Payload_length_9B			(uint32_t)(1<<12)             //1: 1 Start bit, 9 Data bits, n Stop bit


// @Raf_UART_Parity_Define
#define UART_Parity_NONE				(uint32_t)(0)
#define UART_Parity_EVEN				(uint32_t)(1<<10)
#define UART_Parity_ODD					((uint32_t)(1<<10 | 1<<9))


// @Raf_UART_Stop_Bits_Define
    //Bits 13:12 STOP: STOP bits
#define UART_Stop_Bits_half				(uint32_t)(1<<12) 			 //01: 0.5 Stop bit
#define UART_Stop_Bits_1				(uint32_t)(0)				 //00: 1 Stop bit
#define UART_Stop_Bits_1_half			(uint32_t)(3<<12)			 //11: 1.5 Stop bit
#define UART_Stop_Bits_2				(uint32_t)(2<<12)			 //10: 2 Stop bits


//@Raf_UART_HW_Flow_Conterl_Define
#define UART_HW_Flow_Conterl_NONE		(uint32_t)(0)
#define UART_HW_Flow_Conterl_RTS		(uint32_t)(1<<8)
#define UART_HW_Flow_Conterl_CTS		(uint32_t)(1<<9)
#define UART_HW_Flow_Conterl_TTS_CTS	((uint32_t)(1<<8 | 1<<9))


//@Raf_UART_IRQ_Enable_Define
#define UART_IRQ_Enable_NONE 			(uint32_t)(0)
#define UART_IRQ_Enable_TXEIE			(uint32_t)(1<<7) 			//Bit 7 TXEIE: TXE interrupt enable
#define UART_IRQ_Enable_TCIE			(uint32_t)(1<<6)			//Bit 6 TCIE: Transmission complete interrupt enable
#define UART_IRQ_Enable_RXNEIE			(uint32_t)(1<<5)			//Bit 5 RXNEIE: RXNE interrupt enable
#define UART_IRQ_Enable_PEIE			(uint32_t)(1<<8)			//Bit 8 PEIE: PE interrupt enable

enum Polling_Michanism{
	Enable ,
	Disable
};


// ========================== Baud Rate Calculation ==========================

// USARTDIV = FrqCLK / (16 *  BaudRate)
// USARTDIV_MUL100 = uint32_t( 100 * FrqCLK ) / (16 *  BaudRate) == ( 25 * FrqCLK ) / ( 4 *  BaudRate )
// DIV_Mantissa_MUL100 = Integer Part (USARTDIV) * 100
// DIV_Mantissa = Integer Part (USARTDIV)
// DIV_Fraction = ((USARTDIV_MUL100 - DIV_Mantissa_MUL100 ) * 16 ) / 100

#define USARTDIV(_PCLK_ , _BAUD_ )					(uint32_t) ( _PCLK_ / (16 *_BAUD_ ))
#define USARTDIV_MUL100(_PCLK_ , _BAUD_ )			(uint32_t) ( (25 * _PCLK_) / (4 *_BAUD_ ))
#define DIV_Mantissa_MUL100(_PCLK_ , _BAUD_ )		(uint32_t) ( USARTDIV(_PCLK_ , _BAUD_ ) * 100 )
#define DIV_Mantissa(_PCLK_ , _BAUD_ )				(uint32_t) ( USARTDIV(_PCLK_ , _BAUD_ ))
#define DIV_Fraction(_PCLK_ , _BAUD_ )				(uint32_t) ( ( ( USARTDIV_MUL100(_PCLK_ , _BAUD_ ) - DIV_Mantissa_MUL100(_PCLK_ , _BAUD_ ) ) * 16 ) / 100 )
#define UART_BRR_Register(_PCLK_ , _BAUD_ )			(uint32_t) ( (DIV_Mantissa(_PCLK_ , _BAUD_ )) << 4)  | ( (DIV_Fraction(_PCLK_ , _BAUD_ )) & 0xf  )


//-----------------------------


/*
 * ===============================================
 * APIs Supported by "MCAL USART DRIVER"
 * ===============================================
 */

void MCAL_UART_Init(USART_Typedef* USARTx , UART_Config* UART_Config) ;
void MCAL_UART_DeInit(USART_Typedef* USARTx ) ;

void MCAL_UART_GPIO_Set_Pins(USART_Typedef* USARTx) ;

void MCAL_UART_Send_Data(USART_Typedef* USARTx , uint16_t* PTXBuffer , enum Polling_Michanism Polling_Enable) ;
void MCAL_UART_Receive_Data(USART_Typedef* USARTx , uint16_t* PTXBuffer , enum Polling_Michanism Polling_Enable) ;

void MCAL_UART_Wait_Transmit_Complete(USART_Typedef* USARTx ) ;

// TODO
/*
 * MCAL_UART_LIN_Init() ;    //LIN
 * MCAL_UART_USART_Init() ;  //USART
 * MCAL_UART_DMA_Init() ;	 //DMA
 */




#endif /* INC_USART_DRIVER_STM32F103C6_H_ */
