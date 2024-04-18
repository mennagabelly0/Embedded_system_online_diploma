/*
 * SPI_DRIVER_STM32F103C6.h
 *
 *  Created on: Feb 13, 2024
 *      Author: MENNA
 */

#ifndef INC_SPI_DRIVER_STM32F103C6_H_
#define INC_SPI_DRIVER_STM32F103C6_H_

//-----------------------------
//Includes
//-----------------------------

#include "STM32F103X6.h"
#include "GPIO_DRIVER_STM32F103C6.h"
#include "EXTI_DRIVER_STM32F103C6.h"
#include "RCC_DRIVER_STM32F103C6.h"
#include "USART_DRIVER_STM32F103C6.h"

//-----------------------------

// Structure Related to IRQ Function CallBack using in Application (main)

struct S_IRQ_SRC {
	uint8_t		TXE:1  ;									// TX Buffer Empty interrupt .
	uint8_t 	RXEN:1 ;									// RX Buffer NOT Empty interrupt .
	uint8_t		ERRI:1 ;									// Error Interrupt .
	uint8_t		Reserved:5 ;

};

//-----------------------------
// Configuration Structure
//-----------------------------

typedef struct{

	uint16_t	Device_Mode ;								// Specifies The SPI operating Mode @Ref_SPI_Device_Mode .

	uint16_t	Communication_Mode ;						// Specifies The SPI by directional mode state @Ref_SPI_Communication_Mode .

	uint16_t	Frame_Format ;								// Specifies LSB | MSB @Ref_SPI_Frame_Format .

	uint16_t	DataSize_Frame_Format ;						// Specifies 8 | 16 Bit @Ref_SPI_DataSize_Frame_Format .

	uint16_t	CLKPolarity ;								// @Ref_SPI_CLKPolarity .

	uint16_t	CLKPhese ;									// @Ref_SPI_CLKPhese .

	uint16_t	NSS ;										// Specifies whether the NSS signal is managed by HW | SW
															// HW (NSS Pin) | SW using the (SSI Bit enable)
															// @Ref_SPI_NSS .

	uint16_t	SPI_BaudRate_PreScaler ;					// Specifies The SPI Baud Rate PreScaler value which will be used to configure the transmit and reserve SCK ,
															// This parameter can be value of @Ref_SPI_BaudRate_PreScaler ,
															// @Note The communication Clock is derived by Master Clock ,
															// The Slave Clock dose not need to be Set .
															// Take care you have to configure RCC to enter the correct Clock From  APB2 >>>>> TO SPI1 .

	uint16_t	IRQ_Enable ;								// @Ref_SPI_IRQ_Enable .

	void (* P_IRQ_CallBack)(struct S_IRQ_SRC irq_src) ;		// Set the C function which will be Called once IRQ Happened .



}SPI_Congig;


//-----------------------------


//-*-*-*-*-*-*-*-*-*-*-*-
//Reference Macros:
//-*-*-*-*-*-*-*-*-*-*-*

// @Ref_SPI_Device_Mode
/*
  Bit 2 MSTR: Master selection
		0: Slave configuration
 	 	1: Master configuration
 */
#define SPI_Device_Mode_SLAVE								(0x00000000U)
#define SPI_Device_Mode_MASTER								(0x1U<<2)



// @Ref_SPI_Communication_Mode
/*
 Bit 15 BIDIMODE: Bidirectional data mode enable
 	 	 0: 2-line unidirectional data mode selected
 	 	 1: 1-line bidirectional data mode selected

 Bit 14 BIDIOE: Output enable in bidirectional mode
 This bit combined with the BIDImode bit selects the direction of transfer in bidirectional mode
 	 	 0: Output disabled (receive-only mode)
 	 	 1: Output enabled (transmit-only mode)

 Bit 10 RXONLY: Receive only
 This bit combined with the BIDImode bit selects the direction of transfer in 2-line
 unidirectional mode. This bit is also useful in a multislave system in which this particular
 slave is not accessed, the output from the accessed slave is not corrupted.
 	 	 0: Full duplex (Transmit and receive)
 	 	 1: Output disabled (Receive-only mode)
 */
#define SPI_Communication_Mode_Directinal_2Lines			(0x00000000U)						// 0: 2-line unidirectional data mode selected
#define SPI_Communication_Mode_Directinal_2Lines_RXOnly		(0x1U<<10)							// 1: Output disabled (Receive-only mode)
#define SPI_Communication_Mode_Directinal_1Lines_RXOnly		(0x1U<<15)							// 1: 1-line bidirectional data mode selected
#define SPI_Communication_Mode_Directinal_1Lines_TXOnly		((0x1U<<15) | (0x1U>>14))			// 1: 1-line bidirectional data mode selected | 1: Output enabled (transmit-only mode)



// @Ref_SPI_Frame_Format
/*
 Bit 7 LSBFIRST: Frame format
 	 0: MSB transmitted first
 	 1: LSB transmitted first
 */
#define SPI_Frame_Format_MSB_transmitted_first				(0x00000000U)						// 0: MSB transmitted first
#define SPI_Frame_Format_LSB_transmitted_first				(0x1U<<7)							// 1: LSB transmitted first



// @Ref_SPI_DataSize_Frame_Format
/*
 Bit 11 DFF: Data frame format
 	 0: 8-bit data frame format is selected for transmission/reception
 	 1: 16-bit data frame format is selected for transmission/reception
 */
#define SPI_DataSize_Frame_Format_8Bit						(0x00000000U)						// 0: 8-bit data frame format is selected for transmission/reception
#define SPI_DataSize_Frame_Format_16Bit						(0x1U<<11)							// 1: 16-bit data frame format is selected for transmission/reception



// @Ref_SPI_CLKPolarity
/*
 Bit 1 CPOL: Clock polarity
	 0: CK to 0 when idle
     1: CK to 1 when idle
 */
#define SPI_CLKPolarity_Low_Idle							(0x00000000U)						// 0: CK to 0 when idle
#define SPI_CLKPolarity_High_Idle							(0x1U<<1)							// 1: CK to 1 when idle



// @Ref_SPI_CLKPhese .
/*
 Bit 0 CPHA: Clock phase
	 0: The first clock transition is the first data capture edge
 	 1: The second clock transition is the first data capture edge
 */
#define SPI_CLKPhese_First_Edge_Clock_Transition				(0x00000000U)						// 0: The first clock transition is the first data capture edge
#define SPI_CLKPhese_Second_Edge_Clock_Transition				(0x1U<<0)							// 1: The second clock transition is the first data capture edge



// @Ref_SPI_NSS
/*
 * ==================Hardware==================
 Bit 2 SSOE: SS output enable
 	 0: SS output is disabled in master mode and the cell can work in multimaster configuration
 	 1: SS output is enabled in master mode and when the cell is enabled. The cell cannot work
		in a multimaster environment.
 */
#define SPI_NSS_Hardware_Slave									(0x00000000U)
#define SPI_NSS_Hardware_Master_SS_Output_Enable				(0x1U<<2)
#define SPI_NSS_Hardware_Master_SS_Output_Disable				~(0x1U<<2)

/*
 *  ==================Software(Master | Slave)==================
 Bit 9 SSM: Software slave management
 When the SSM bit is set, the NSS pin input is replaced with the value from the SSI bit.
 	 0: Software slave management disabled
 	 1: Software slave management enabled

 Bit 8 SSI: Internal slave select
 This bit has an effect only when the SSM bit is set. The value of this bit is forced onto the
 NSS pin and the IO value of the NSS pin is ignored.
 */
#define SPI_NSS_Software_Internal_Reset							(0x1U<<9)
#define SPI_NSS_Software_Internal_Set							((0x1U<<9) | (0x1U<<8))



// @Ref_SPI_BaudRate_PreScaler
/*
 Bits 5:3 BR[2:0]: Baud rate control
 000: fPCLK/2
 001: fPCLK/4
 010: fPCLK/8
 011: fPCLK/16
 100: fPCLK/32
 101: fPCLK/64
 110: fPCLK/128
 111: fPCLK/256
 */
#define SPI_BaudRate_PreScaler_2								(0x00000000U)
#define SPI_BaudRate_PreScaler_4								(0b001U << 3)
#define SPI_BaudRate_PreScaler_8								(0b010U << 3)
#define SPI_BaudRate_PreScaler_16								(0b011U << 3)
#define SPI_BaudRate_PreScaler_32								(0b100U << 3)
#define SPI_BaudRate_PreScaler_64								(0b101U << 3)
#define SPI_BaudRate_PreScaler_128								(0b110U << 3)
#define SPI_BaudRate_PreScaler_256								(0b111U << 3)



// @Ref_SPI_IRQ_Enable
/*
  Bit 7 TXEIE: Tx buffer empty interrupt enable
 	  0: TXE interrupt masked
	  1: TXE interrupt not masked. Used to generate an interrupt request when the TXE flag is set.

  Bit 6 RXNEIE: RX buffer not empty interrupt enable
 	  0: RXNE interrupt masked
 	  1: RXNE interrupt not masked. Used to generate an interrupt request when the RXNE flag is set.

  Bit 5 ERRIE: Error interrupt enable This bit controls the generation of an interrupt when an error condition occurs (CRCERR, OVR, MODF in SPI mode and UDR, OVR in I2S mode).
 	  0: Error interrupt is masked
   	  1: Error interrupt is enabled
 */
#define SPI_IRQ_Enable_NONE										(0x00000000U)
#define SPI_IRQ_Enable_TXEIE									(0x1U << 7)
#define SPI_IRQ_Enable_RXNEIE									(0x1U << 6)
#define SPI_IRQ_Enable_ERRIE									(0x1U << 5)


enum PollingMichanism{
 	Polling_Enable ,
	Polling_Disable
};


//-----------------------------


/*
 * ===============================================
 * APIs Supported by "MCAL SPI DRIVER"
 * ===============================================
 */

void MCAL_SPI_Init(SPI_Typedef* SPIx , SPI_Congig* SPI_Congig) ;
void MCAL_SPI_DeInit(SPI_Typedef* SPIx ) ;

void MCAL_SPI_GPIO_Set_Pins(SPI_Typedef* SPIx) ;

void MCAL_SPI_Send_Data(SPI_Typedef* SPIx , uint16_t* pTXBuffer , enum PollingMichanism PollingEnable) ;
void MCAL_SPI_Receive_Data(SPI_Typedef* SPIx , uint16_t* pTXBuffer , enum PollingMichanism PollingEnable) ;
void MCAL_SPI_Send_Receive_Data(SPI_Typedef* SPIx , uint16_t* pTXBuffer , enum PollingMichanism PollingEnable) ;


#endif /* INC_SPI_DRIVER_STM32F103C6_H_ */
