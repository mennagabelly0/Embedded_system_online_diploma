/*
 * I2C_DRIVER_STM32F103C6.h
 *
 *  Created on: Feb 22, 2024
 *      Author: HFCS
 */

#ifndef INC_I2C_DRIVER_STM32F103C6_H_
#define INC_I2C_DRIVER_STM32F103C6_H_

//-----------------------------
//Includes
//-----------------------------

#include "STM32F103X6.h"
#include "GPIO_DRIVER_STM32F103C6.h"
#include "EXTI_DRIVER_STM32F103C6.h"
#include "RCC_DRIVER_STM32F103C6.h"
#include "USART_DRIVER_STM32F103C6.h"
#include "SPI_DRIVER_STM32F103C6.h"


//-----------------------------


//-----------------------------
// Configuration Structure
//-----------------------------

struct S_I2C_Slave_Device_Address{
	uint16_t													Enable_Dual_Address ;			// 1- Enable  , 0-Disable.
	uint16_t													Primary_Slave_Address ;
	uint16_t													Secondary_Slave_Address ;
	uint32_t													I2C_Addressing_Slave_Mode ;		// @Ref_I2C_Addressing_Slave.
};

typedef enum{
	I2C_EV_Stop ,
	I2C_Error_AF ,
	I2C_EV_ADDR_Matched ,
	I2C_EV_Data_REQ ,			// The APP layer should Send Data (I2C_Slave_Send_Data) in this State.
	I2C_EV_Data_RCV				// The APP layer should Reed Data (I2C_Slave_Receive_Data) in this State.
}Slave_State;

typedef struct{
	uint32_t													I2C_ClockSpeed ; 				// Specifies the two clock Frequency ,
												 	 	 	 									// The parameter must be set in @Ref_I2C_ClockSpeed.

	uint32_t													I2C_STRETCH_Mode ;    			// @Ref_I2C_STRETCH_Mode.

	uint32_t													I2C_Mode ;						// Specifies the I2C Mode.
	 																							// The parameter must be set in @Ref_I2C_Mode.

	struct S_I2C_Slave_Device_Address		        			I2C_Slave_Address ;

	uint32_t													I2C_ACK_Control ;				// Enable / Disable The Acknowledgment,
																								// The parameter must be set in @Ref_I2C_ACK_Control.

	uint32_t													I2C_Call_Address_Detection ;	// @Ref_I2C_Call_Address_Detection.

	void(*P_Slave_Event_CallBack)(Slave_State State) ;											//Set the C Function() which will be called once the IRQ happen.

}I2C_PinConfig_t;


//-----------------------------


//-*-*-*-*-*-*-*-*-*-*-*-
//Reference Macros:
//-*-*-*-*-*-*-*-*-*-*-*

// @Ref_I2C_ClockSpeed
/*
 * Standard Speed (up to 100 KHZ)
 * Fast Speed (up to 400 KHZ)
 * To configure Clock before enable the peripherals..
 * -- I2C_CR2 Bits 5:0 FREQ[5:0]: Peripheral clock frequency
 * Configure Clock control register
 * --- Bits 11:0 CCR[11:0]: Clock control register
 * 		--- in FM/SM mode (Master mode) --
 */
#define I2C_SCLK_SM_50K											(50000U)
#define I2C_SCLK_SM_100K										(100000U)
#define I2C_SCLK_FM_200K										(200000U) // Fast mode is not supported yet
#define I2C_SCLK_FM_400K										(400000U) // Fast mode is not supported yet

// @Ref_I2C_STRETCH_Mode
/*
    IN I2C_CR1 Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
    This bit is used to disable clock stretching in slave mode,
 	when ADDR or BTF flag is set, until it is reset by software.
 	 0: Clock stretching enabled
 	 1: Clock stretching disabled
 */
#define I2C_STRETCH_Mode_Enable 								(0x00000000U)
#define I2C_STRETCH_Mode_Disable								I2C_CR1_NOSTRETCH

// @Ref_I2C_Mode
/*
   Bit 1 SMBUS: SMBus mode
 	   0: I2C mode
 	   1: SMBus mode
 */
#define I2C_Mode_I2C											0
#define I2C_Mode_SMBus											I2C_CR1_SMBUS

// @Ref_I2C_Addressing_Slave
/*
 (I2C_OAR1) Bit 15 ADDMODE Addressing mode (slave mode)
 	  	  	     0: 7-bit slave address (10-bit address not acknowledged)
 	  	  	  	 1: 10-bit slave address (7-bit address not acknowledged)
 */
#define I2C_Addressing_Slave_Mode_7Bit							(0x00000000U)
#define I2C_Addressing_Slave_Mode_10Bit							(uint16_t)(1<<15)

// @Ref_I2C_ACK_Control
/*
 I2C Control register 1 (I2C_CR1) Bit 10 ACK: Acknowledge enable
 This bit is set and cleared by software and cleared by hardware when PE=0.
 	 0: No acknowledge returned
 	 1: Acknowledge returned after a byte is received (matched address or data)
 */
#define I2C_ACK_Control_Enable									(I2C_CR1_ACK)
#define I2C_ACK_Control_Disable									((uint16_t)0x0000)

// @Ref_I2C_Call_Address_Detection
/*
 I2C Control register 1 (I2C_CR1) Bit 6 ENGC: General call enable
 	 0: General call disabled. Address 00h is NACKed.
 	 1: General call enabled. Address 00h is ACKed.
 */
#define I2C_Call_Address_Detection_ENGC_Enable					(I2C_CR1_ENGC)
#define I2C_Call_Address_Detection_ENGC_Disable					((uint16_t)0x0000)

//------------------------------------------------------------------------------------------

// ====================================== Master Polling Mechanism ==========================

typedef enum{
	With_Stop ,
	Without_Stop

}Stop_Condation ;

typedef enum{
	Start ,
	RepeatedStart

}Repeated_Start ;

typedef enum{
	disable = 0 ,
	enable = 1

}Functional_State ;

typedef enum{
	Reset = 0 ,
	Set = 1

}FlagStatus;

#define I2C_EVENT_MASTER_BITE_Transmitter					((uint32_t)0x00070080U)			// TRA , Busy , MSL , TX Flags

typedef enum{
	I2C_Flag_Busy = 0 ,
	EV5,     												//  EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	EV6, 													//  EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	EV7 ,													//  EV7: RXNE = 1 Cleared by reading DR register
//	EV7_1 ,													//  EV7_1: RXNE = 1 Cleared by reading DR register , program ACK = 0 and Stop Request
	EV8_1 ,													//	TxE=1, shift register empty, data register empty, write Data1 in DR.
	EV8 , 													//  TxE=1, shift register not empty, data register empty, cleared by writing DR register
//	EV8_2 ,													//	TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
//	EV9 ,													//	ADD10=1, cleared by reading SR1 register followed by writing DR register.
	MASTER_BITE_Transmitter	 = ((uint32_t)0x00070080U) 	    //  TRA , Busy , MSL , TX Flags

}Status ;

typedef enum {
	I2C_Direction_Transmitter = 0 ,
	I2C_Direction_Receiver = 1

}I2C_Direction ;


/*
 * ===============================================
 * APIs Supported by "MCAL I2C DRIVER"
 * ===============================================
 */

void MCAL_I2C_Init(I2C_Typedef* I2Cx , I2C_PinConfig_t* I2C_Config) ;
void MCAL_I2C_DeInit(I2C_Typedef* I2Cx ) ;

void MCAL_I2C_GPIO_Set_Pins(I2C_Typedef* I2Cx) ;

// ====================================== Master Polling Mechanism ==========================

void MCAL_I2C_Master_Send_Data_TX(I2C_Typedef* I2Cx , uint16_t DevAddress , uint8_t* DataOut , uint32_t DataLen , Stop_Condation Stop , Repeated_Start Start) ;
void MCAL_I2C_Master_Receive_Data_RX(I2C_Typedef* I2Cx , uint16_t DevAddress , uint8_t* DataOut , uint32_t DataLen , Stop_Condation Stop , Repeated_Start Start) ;
//void MCAL_I2C_Master_Wait_Transmit_Complete_TR_TX(I2C_Typedef* I2Cx ) ;

// ====================================== Slave Interrupt ===================================

void MCAL_I2C_Slave_Send_Data_TX( I2C_Typedef* I2Cx  , uint8_t data) ;
uint8_t MCAL_I2C_Slave_Receive_Data_RX( I2C_Typedef* I2Cx ) ;

//====================================== Generic API'S ======================================

void I2C_Generate_Start(I2C_Typedef* I2Cx , Functional_State NewState , Repeated_Start Start ) ;
void I2C_Generate_Stop(I2C_Typedef* I2Cx , Functional_State NewState ) ;

FlagStatus I2C_Get_Flag_Status( I2C_Typedef* I2Cx , Status flag ) ;

void I2C_Send_Address( I2C_Typedef* I2Cx , uint16_t Address , I2C_Direction Direction) ;
void I2C_AcknowledgeConfig(I2C_Typedef* I2Cx  , Functional_State NewState) ;

#endif /* INC_I2C_DRIVER_STM32F103C6_H_ */
