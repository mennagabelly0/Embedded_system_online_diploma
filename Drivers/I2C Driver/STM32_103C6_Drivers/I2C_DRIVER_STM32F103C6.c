/*
 * I2C_DRIVER_STM32F103C6.c
 *
 *  Created on: Feb 22, 2024
 *      Author: HFCS
 */

//-----------------------------
//Includes
//-----------------------------

#include "I2C_DRIVER_STM32F103C6.h"


/*
 * ===============================================
				"Generic Variables"
 * ===============================================
 */

I2C_PinConfig_t Global_I2C_Config[2] = {0} ;


/*
 * ===============================================
				"Generic Function"
 * ===============================================
 */

#define				I2C1_Index				0
#define				I2C2_Index				1




/*
 * ===============================================
 * APIs Supported by "MCAL I2C DRIVER"
 * ===============================================
 */

/**================================================================
 * @Fn					-	MCAL_I2C_Init
 * @brief 				-	Initialization I2C
 * @param[in] 			-	I2Cx
 * @param[in] 			-	I2C_Config
 * @retval				-	NONE
 * Note					-	NONE
 *						-
 */
void MCAL_I2C_Init(I2C_Typedef* I2Cx , I2C_PinConfig_t* I2C_Config)
{
	/*
 The following is the required sequence in MASTER MODE.
 • Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
 • Configure the clock control registers
 • Configure the rise time register
 • Program the I2C_CR1 register to enable the peripheral
 • Set the START bit in the I2C_CR1 register to generate a Start condition
 The peripheral input clock frequency must be at least:
 • 2 MHz in SM mode
 • 4 MHz in FM mode
	 */
	uint16_t TmepReg = 0 , FreqRange = 0 ;
	uint32_t PCLK1 = 8000000 ;
	uint16_t Result = 0 ;

	// Enable RCC Clock
	if(I2Cx == I2C1){
		Global_I2C_Config[I2C1_Index] = *I2C_Config ;
		RCC_I2C1_CLK_EN() ;
	}
	else{
		Global_I2C_Config[I2C2_Index] = *I2C_Config ;
		RCC_I2C2_CLK_EN() ;
	}

	// Check MODE
	if(I2C_Config->I2C_Mode == I2C_Mode_I2C ){ // I2C Standard mode

		// ========================== INIT Timing ==========================
		// -- I2C_CR2 Bits 5:0 FREQ[5:0]: Peripheral clock frequency
		TmepReg = I2Cx->I2C_CR2 ;
		// Clear Frequency RREQ[5:0] Bit
		TmepReg &= ~(I2C_CR2_FREQ_Msk) ;
		// Get PCLK1 Frequency Value
		PCLK1 = MCAL_RCC_Get_PCLK1_Frequency() ;
		// Set Frequency bit depending on PCLK1 value
		FreqRange = (uint16_t)(PCLK1 / 1000000) ;

		TmepReg |= FreqRange ;
		// Write on I2C CR2
		I2Cx->I2C_CR2 = TmepReg ;

		// Configure Clock control register
		// Disable the selected I2C Peripheral to configure time
		I2Cx->I2C_CR1 &= ~(I2C_CR1_PE) ;
		TmepReg = 0 ;

		// Configure Speed in Standard mode
		if((I2C_Config->I2C_ClockSpeed == I2C_SCLK_SM_50K) || (I2C_Config->I2C_ClockSpeed == I2C_SCLK_SM_100K)){
			// Standard mode Speed Calculation
			// TCLK / 2 = CCR * TPCLK1
			// CCR = TCLK / (2 * TPCLK1)
			// CCR = FREQPCLK1 / (2 * I2C_ClockFrequency)
			Result = (uint16_t)(PCLK1 / (I2C_Config->I2C_ClockSpeed << 1 )) ; // I2C_Config->I2C_ClockSpeed << 1  == I2C_Config->I2C_ClockSpeed * 2
			TmepReg |= Result ;
			// Write on I2C CCR
			I2Cx->I2C_CCR = TmepReg ;

		// ========================== Configure Rise Time ==========================
		/*
		Bits 5:0 TRISE[5:0]: Maximum rise time in FM/SM mode (Master mode)
		For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
 	 	If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
 	 	therefore the TRISE[5:0] bits must be programmed with 09h.
 	 	(1000 ns / 125 ns = 8 + 1)
		*/
		I2Cx->I2C_TRISE = FreqRange + 1 ;

		}
		else{
			// Fast MODE Not Supported Yet ..
		}

		// ========================== I2Cx CR1 Configuration ==========================

		// Get the I2Cx CR1 value
		TmepReg = I2Cx->I2C_CR1 ;
		TmepReg |= (uint16_t)(I2C_Config->I2C_ACK_Control | I2C_Config->I2C_Call_Address_Detection | I2C_Config->I2C_Mode | I2C_Config->I2C_STRETCH_Mode) ;

		// Write on I2C CR1
		I2Cx->I2C_CR1 = TmepReg ;

		// ========================== I2Cx OAR1 & OAR2 Configuration ==========================
		TmepReg = 0 ;
		if(I2C_Config->I2C_Slave_Address.Enable_Dual_Address == 1){
			TmepReg = I2C_OAR2_ENDUAL ;
			TmepReg |= I2C_Config->I2C_Slave_Address.Secondary_Slave_Address << I2C_OAR2_ADD2_Pos ; // I2C_Slave_Address.Secondary_Slave_Address << I2C_OAR2_ADD2_Pos     ==    I2C_Slave_Address.Secondary_Slave_Address << 1

			// Write on I2C OAR2
			I2Cx->I2C_OAR2 = TmepReg ;

		}

		TmepReg = 0 ;
		TmepReg |= I2C_Config->I2C_Slave_Address.Primary_Slave_Address << 1 ;
		/*
		 Bit 15 ADDMODE Addressing mode (slave mode)
 	 	 	 0: 7-bit slave address (10-bit address not acknowledged)
 	 	 	 1: 10-bit slave address (7-bit address not acknowledged)
		 */
		TmepReg |= I2C_Config->I2C_Slave_Address.I2C_Addressing_Slave_Mode ;
		// Write on I2C OAR1
		I2Cx->I2C_OAR1 = TmepReg ;

	}
	else{
		// SMBus Not Supported yet.
	}

	// Interrupt Mode in Slave ... Check Call Back Pointer != NULL
	if(I2C_Config->P_Slave_Event_CallBack != NULL){ // TAHT ENABLE SLAVE IRQ States MODE
		// Enable IRQ
		/*
		 (I2C_CR2) Bit 8 ITERREN: Error interrupt enable
 	 	 0: Error interrupt disabled
 	 	 1: Error interrupt enabled
		 */
		I2Cx->I2C_CR2 = (I2C_CR2_ITERREN) ;
		/*
		 (I2C_CR2) Bit 9 ITEVTEN: Event interrupt enable
 	 	 0: Event interrupt disabled
 	 	 1: Event interrupt enabled
		 */
		I2Cx->I2C_CR2 = (I2C_CR2_ITEVTEN) ;
		/*
		    (I2C_CR2) Bit 10 ITBUFEN: Buffer interrupt enable
 	 	 	0: TxE = 1 or RxNE = 1 does not generate any interrupt.
 	 	 	1: TxE = 1 or RxNE = 1 generates Event Interrupt (whatever the state of DMAEN)
		 */
		I2Cx->I2C_CR2 = (I2C_CR2_ITBUFEN) ;

		if(I2Cx == I2C1){
			NVIC_IRQ31_I2C1_EV_Enable ;
			NVIC_IRQ32_I2C1_ER_Enable ;

		}
		else if (I2Cx == I2C2){
			NVIC_IRQ33_I2C2_EV_Enable ;
			NVIC_IRQ34_I2C2_ER_Enable ;
		}
		I2Cx->I2C_SR1 = 0 ;
		I2Cx->I2C_SR2 = 0 ;

	}

	// Enable I2C peripheral
	I2Cx->I2C_CR1 |= I2C_CR1_PE ;

}

/**================================================================
 * @Fn					-	MCAL_I2C_DeInit
 * @brief 				-	DeInitialization I2C
 * @param[in] 			-	I2Cx
 * @param[in] 			-	NONE
 * @retval				-	NONE
 * Note					-	NONE
 *						-
 */

void MCAL_I2C_DeInit(I2C_Typedef* I2Cx )
{
	if(I2Cx == I2C1){
		NVIC_IRQ31_I2C1_EV_Disable ;
		NVIC_IRQ32_I2C1_ER_Disable ;
		RCC_I2C1_CLK_Reset() ;

	}
	else if (I2Cx == I2C2){
		NVIC_IRQ33_I2C2_EV_Disable ;
		NVIC_IRQ34_I2C2_ER_Disable ;
		RCC_I2C2_CLK_Reset() ;

	}
}


/**================================================================
 * @Fn					-	MCAL_I2C_GPIO_Set_Pins
 * @brief 				- 	I2C GPIO Set Pins
 * @param[in] 			-	I2Cx
 * @param[in] 			-	NONE
 * @retval				-	NONE
 * Note					-	NONE
 *						-
 */

void MCAL_I2C_GPIO_Set_Pins(I2C_Typedef* I2Cx)
{
	GPIO_PinConfig_t PINCF ;

	// I2C1
//	IN AFIO I2C1_SCL 	 IN 	 PB6
//	IN AFIO I2C1_SDA  	 IN 	 PB7
//  IN AFIO I2C1_SMBAl 	 IN		 PB5 		NOT Supported Yet

	// I2C2
//	IN AFIO I2C2_SCL  	 IN		 PB10
//	IN AFIO I2C2_SDA  	 IN 	 PB11
//  IN AFIO I2C2_SMBAl	 IN		 PB12		NOT Supported Yet

	// IN General
//	I2Cx_SCL	I2C clock		Alternate function open drain
//	I2Cx_SDA	I2C Data I/O	Alternate function open drain

	if(I2Cx == I2C1){
		// I2C1
		//	IN AFIO I2C1_SCL 	 IN 	 PB6
		//	IN AFIO I2C1_SDA  	 IN 	 PB7

		PINCF.GPIO_PinNumber = 	GPIO_PIN_6 ;
		PINCF.GPIO_MODE = GPIO_MODE_Output_AF_Open_drain ;
		PINCF.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
		MCAL_GPIO_Init(GPIOB, &PINCF) ;

		PINCF.GPIO_PinNumber = 	GPIO_PIN_7 ;
		PINCF.GPIO_MODE = GPIO_MODE_Output_AF_Open_drain ;
		PINCF.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
		MCAL_GPIO_Init(GPIOB, &PINCF) ;
	}
	else if(I2Cx == I2C2){
		// I2C2
		//	IN AFIO I2C2_SCL  	 IN		 PB10
		//	IN AFIO I2C2_SDA  	 IN 	 PB11

		PINCF.GPIO_PinNumber = 	GPIO_PIN_10 ;
		PINCF.GPIO_MODE = GPIO_MODE_Output_AF_Open_drain ;
		PINCF.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
		MCAL_GPIO_Init(GPIOB, &PINCF) ;

		PINCF.GPIO_PinNumber = 	GPIO_PIN_11 ;
		PINCF.GPIO_MODE = GPIO_MODE_Output_AF_Open_drain ;
		PINCF.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
		MCAL_GPIO_Init(GPIOB, &PINCF) ;


	}
}


/**================================================================
 * @Fn					-	MCAL_I2C_Master_Receive_Data_RX
 * @brief 				-	I2C Master Receive Data RX
 * @param[in] 			-	I2Cx
 * @param[in] 			-	DevAddress
 * @param[in] 			-	DataOut
 * @param[in] 			-	DataLen
 * @param[in] 			-	Stop
 * @param[in] 			-	Start
 * @retval				-	NONE
 * Note					-	NONE
 *						-
 */

void MCAL_I2C_Master_Receive_Data_RX(I2C_Typedef* I2Cx , uint16_t DevAddress , uint8_t* DataOut , uint32_t DataLen , Stop_Condation Stop , Repeated_Start Start)
{
	int i = 0 ; // length
	uint8_t indix = I2Cx == I2C1 ? I2C1_Index : I2C2_Index ;

	// 1- Set the Start Bit in The I2C_CR1 Register to Generate a Start Condition .
	I2C_Generate_Start(I2Cx , enable , Start) ;

	//	Notes: 1- The EV5, EV6, EV9, EV8_1 and EV8_2 events stretch SCL low until the end of the corresponding software sequence.
	//         2- The EV8 software sequence must complete before the end of the current byte transfer. In case EV8 software
	// 			  sequence can not be managed before the current byte end of transfer, it is recommended to use BTF instead
	//			  of TXE with the drawback of slowing the communication.

	// 2- Wait for EV5
	// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(!I2C_Get_Flag_Status(I2Cx, EV5)) ;

	// 2.1- Send Address
	I2C_Send_Address(I2Cx , DevAddress , I2C_Direction_Receiver ) ; // Address

	// 3- Wait for EV6
	// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!I2C_Get_Flag_Status(I2Cx, EV6)) ;

	if(DataLen){
		// Read Data until Length Become Zero
		for(i = DataLen ; i > 1 ; i-- ){
			// wait until RXNE Become 1
			while(!I2C_Get_Flag_Status(I2Cx, EV7)) ;
			// Read Data from data register into buffer
			*DataOut = I2Cx->I2C_DR ;
			// Increment the Buffer address
			DataOut ++ ;
		}

		I2C_AcknowledgeConfig(I2Cx , disable) ;
	}

	if(Stop == With_Stop){
		// 7. Send Stop Configuration
		I2C_Generate_Stop(I2Cx, enable) ;
	}

	// Re-Enable ACKing
	if(Global_I2C_Config[indix].I2C_ACK_Control == I2C_ACK_Control_Enable){
		I2C_AcknowledgeConfig(I2Cx , enable) ;

	}
}

void I2C_AcknowledgeConfig(I2C_Typedef* I2Cx  , Functional_State NewState)
{
	/*Bit 10 ACK: Acknowledge enable
	This bit is set and cleared by software and cleared by hardware when PE=0.
	0: No acknowledge returned
	1: Acknowledge returned after a byte is received (matched address or data)*/

	if(NewState == enable)
	{
		I2Cx->I2C_CR1 |=(I2C_CR1_ACK);
	}
	else
	{
		I2Cx->I2C_CR1 &=~(I2C_CR1_ACK);
	}

}


/**================================================================
 * @Fn					-	MCAL_I2C_Master_Send_Data_TX
 * @brief 				-	I2C Master Send Data TX
 * @param[in] 			-	I2Cx
 * @param[in] 			-	DevAddress
 * @param[in] 			-	DataOut
 * @param[in] 			-	DataLen
 * @param[in] 			-	Stop
 * @param[in] 			-	Start
 * @retval				-	NONE
 * Note					-	NONE
 *						-
 */

void MCAL_I2C_Master_Send_Data_TX(I2C_Typedef* I2Cx , uint16_t DevAddress , uint8_t* DataOut , uint32_t DataLen , Stop_Condation Stop , Repeated_Start Start)
{
	int i = 0 ; // length
	// TODO...
	// Support Timeout (Configure Timer working for specific duration Rise Interrupt
	// Timer_interrupt(){Flag = 1 }
	// So any Exist in while(check flag || any Polling Condition)

	// 1- Set the Start Bit in The I2C_CR1 Register to Generate a Start Condition .
	I2C_Generate_Start(I2Cx , enable , Start) ;

	//	Notes: 1- The EV5, EV6, EV9, EV8_1 and EV8_2 events stretch SCL low until the end of the corresponding software sequence.
	//         2- The EV8 software sequence must complete before the end of the current byte transfer. In case EV8 software
	// 			  sequence can not be managed before the current byte end of transfer, it is recommended to use BTF instead
	//			  of TXE with the drawback of slowing the communication.

	// 2- Wait for EV5
	// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(!I2C_Get_Flag_Status(I2Cx, EV5)) ;

	// 2.1- Send Address
	I2C_Send_Address(I2Cx , DevAddress , I2C_Direction_Transmitter ) ; // Address

	// 3- Wait for EV6
	// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!I2C_Get_Flag_Status(I2Cx, EV6)) ;

	// 4- TRA , Busy , MSL , TX Flags
	while(!I2C_Get_Flag_Status(I2Cx, MASTER_BITE_Transmitter)) ;

	for (i = 0 ; i < DataLen ; i++)
	{
		// write in DR register the data to be send
		I2Cx->I2C_DR = DataOut[i] ;
		// Wait for EV8
		// EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
		while(!I2C_Get_Flag_Status(I2Cx, EV8)) ;

	}
	// Wait for EV8_2
	// TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	// while(!I2C_Get_Flag_Status(I2Cx, EV8_2)) ;

	if(Stop == With_Stop ){
		I2C_Generate_Stop(I2Cx , enable) ;
	}

}

/**================================================================
 * @Fn					-	I2C_Generate_Start
 * @brief 				-	I2C Generate Start
 * @param[in] 			-	I2Cx
 * @param[in] 			-	NewState
 * @param[in] 			-	Start
 * @retval				-	NONE
 * Note					-	NONE
 *						-
 */

void I2C_Generate_Start(I2C_Typedef* I2Cx , Functional_State NewState , Repeated_Start Start )
{
	if(Start != RepeatedStart){
		// check if Bus is Idle
		while(I2C_Get_Flag_Status(I2Cx, I2C_Flag_Busy)) ;
	}
//	 (I2C_CR1) Bit 8 START: Start generation
//	 This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
//	 In Master Mode:
//	 0: No Start generation
//	 1: Repeated start generation
//	 In Slave mode:
//	 0: No Start generation
//	 1: Start generation when the bus is free
	if(NewState != disable)
	{
		// Generate The start Condition
		I2Cx->I2C_CR1 |= I2C_CR1_START ;
	}
	else
	{
		// Disable The start Condition Generation
		I2Cx->I2C_CR1 &= ~(I2C_CR1_START) ;
	}



}

void I2C_Send_Address( I2C_Typedef* I2Cx , uint16_t Address , I2C_Direction Direction)
{
//  IN Case cover 10B and switch between 7 BIT or 10 BIT
//  uint8_t index = I2Cx == I2C1 ? I2C1_Index : I2C2_Index ;
//	if(Global_I2C_Config[index].I2C_Slave_Address.I2C_Addressing_Slave_Mode == I2C_Addressing_Slave_Mode_7Bit)
//	{
//
//	}
//	else{
////		Not Supporter I2C_Addressing_Slave_Mode_10Bit yet
//	}

	// In This Case just Supported 7 Bit so Work in Function without any Conditions.
	Address = (Address << 1) ;
	if(Direction != I2C_Direction_Transmitter)
	{
		// Set Address bit 0  for Read
		Address |= 1<<0 ;
	}
	else
	{
		// Reset Address bit 0 for write
		Address &= ~(1<<0) ;
	}

	// Send the Address
	I2Cx->I2C_DR = Address ;

}

void I2C_Generate_Stop(I2C_Typedef* I2Cx , Functional_State NewState )
{
	if(NewState != disable)
	{
		//Enable Stop
		I2Cx->I2C_CR1 |= I2C_CR1_STOP ;
	}
	else
	{
		//Disable Stop
		I2Cx->I2C_CR1 &= ~(I2C_CR1_STOP) ;
	}

}

FlagStatus I2C_Get_Flag_Status( I2C_Typedef* I2Cx , Status flag )
{
	volatile uint32_t  dummyRead ;
	FlagStatus Bitstatus = Reset ;
	uint32_t  Flag1 = 0 , Flag2 = 0 ;
	uint32_t lastEvent = 0 ;

	switch(flag)
	{
	case I2C_Flag_Busy :
	{
//		I2C_SR2 Bit 1 BUSY: Bus busy
// 	 	0: No communication on the bus
// 	 	1: Communication ongoing on the bus
// 	 	– Set by hardware on detection of SDA or SCL low
//      – cleared by hardware on detection of a Stop condition.
//		It indicates a communication in progress on the bus. This information is still updated when
//		the interface is disabled (PE=0).
		if((I2Cx->I2C_SR2) & (I2C_SR2_BUSY))
			Bitstatus = Set ;
		else
			Bitstatus = Reset ;
		break ;
	}
	case EV5:
	{
//  	EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
//		(I2C_SR1) Bit 0 SB: Start bit (Master mode)
//		0: No Start condition
//		1: Start condition generated.– Set when a Start condition generated.
//		– Cleared by software by reading the SR1 register followed by writing the DR register, or by
//		hardware when PE=0
		if((I2Cx->I2C_SR1) & (I2C_SR1_SB))
			Bitstatus = Set ;
		else
			Bitstatus = Reset ;
		break ;
	}
	case EV6 :
	{
//		EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
//		(I2C_SR1) Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
//		This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
//		when PE=0.
//		Address matched (Slave)
//		0: Address mismatched or not received.
//		1: Received address matched.
		if((I2Cx->I2C_SR1) & (I2C_SR1_ADDR))
			Bitstatus = Set ;
		else
			Bitstatus = Reset ;

////		Note: Reading I2C_SR2 after reading I2C_SR1 clears the ADDR flag, even if the ADDR flag was
////		set after reading I2C_SR1. Consequently, I2C_SR2 must be read only when ADDR is found
////		set in I2C_SR1 or when the STOPF bit is cleared.
//		dummyRead = I2Cx->I2C_SR2 ;
		break ;
	}
	case MASTER_BITE_Transmitter :
	{
		// Read I2C state register
		Flag1 = I2Cx->I2C_SR1 ;
		Flag2 = I2Cx->I2C_SR2 ;
		Flag2 = Flag2 << 16 ;
		// Get the last event value from I2C state register
		lastEvent = (Flag1 | Flag2) & ((uint32_t)0x00FFFFFF) ;
		//check whether the last event contains the I2C_EVENT
		if((lastEvent & flag) == flag)
			Bitstatus = Set ;
		else
			Bitstatus = Reset ;
		break ;
	}
	case EV8 :		//  TxE=1, shift register not empty, data register empty, cleared by writing DR register
	case EV8_1 :	//	TxE=1, shift register empty, data register empty, write Data1 in DR.
	{
		//		(I2C_SR1)  Bit 7 TxE: Data register empty (transmitters)
		//		0: Data register not empty
		//		1: Data register empty
		if((I2Cx->I2C_SR1) &(I2C_SR1_TXE))
			Bitstatus = Set ;
		else
			Bitstatus = Reset ;
		break ;
	}
	case EV7 :
	{
		//		 Bit 6 RxNE: Data register not empty (receivers)
		//		 0: Data register empty
		//		 1: Data register not empty
		//		  – Set when data register is not empty in receiver mode. RxNE is not set during address phase.
		//		  – Cleared by software reading or writing the DR register or by hardware when PE=0.
		//		 RxNE is not set in case of ARLO event.
		//       Note: RxNE is not cleared by reading data when BTF is set, as the data register is still full.
		if((I2Cx->I2C_SR1) &(I2C_SR1_RXNE))
			Bitstatus = Set ;
		else
			Bitstatus = Reset ;
		break ;

	}

	}
	return Bitstatus ;
}


// ====================================== Slave Interrupt ===================================

/**================================================================
 * @Fn					-	MCAL_I2C_Slave_Send_Data_TX
 * @brief 				-	I2C Slave Send Data TX
 * @param[in] 			-	I2Cx
 * @param[in] 			-	data
 * @retval				-	NONE
 * Note					-	NONE
 *						-
 */
void MCAL_I2C_Slave_Send_Data_TX( I2C_Typedef* I2Cx  , uint8_t data)
{
	I2Cx->I2C_DR = data ;
}

/**================================================================
 * @Fn					-	MCAL_I2C_Slave_Receive_Data_RX
 * @brief 				-	I2C Slave Receive Data RX
 * @param[in] 			-	NONE
 * @param[out] 			-	I2Cx
 * @retval				-	NONE
 * Note					-	NONE
 *						-
 */
uint8_t MCAL_I2C_Slave_Receive_Data_RX( I2C_Typedef* I2Cx )
{
	return (uint8_t) I2Cx->I2C_DR ;
}

// ******************************* ISR *******************************

//				Note :	Working on to Compete but Not Now ...

void I2C1_EV_IRQHandler(void)
{
//	volatile uint32_t dumy_Read = 0 ;
//	I2C_Typedef* I2Cx = I2C1 ;
//	// Interrupt Handling for both Master and Salve Mode of Device
//	uint32_t temp1 , temp2 , temp3 ;
//	temp1 = I2Cx->I2C_CR2 & (I2C_CR2_ITEVTEN) ;
//	temp2 = I2Cx->I2C_CR2 & (I2C_CR2_ITBUFEN) ;
//	temp3 = I2Cx->I2C_SR1 & (I2C_SR1_STOPF) ;


	//	Working on to Compete but Not Now ...
}

void I2C1_ER_IRQHandler(void)
{

}

void I2C2_EV_IRQHandler(void)
{

}

void I2C2_ER_IRQHandler(void)
{

}
