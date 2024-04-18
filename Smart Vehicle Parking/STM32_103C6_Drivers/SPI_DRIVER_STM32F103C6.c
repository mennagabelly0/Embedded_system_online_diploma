/*
 * SPI_DRIVER_STM32F103C6.c
 *
 *  Created on: Feb 13, 2024
 *      Author: HFCS
 */

//-----------------------------
//Includes
//-----------------------------

#include "SPI_DRIVER_STM32F103C6.h"

/*
 * ===============================================
				"Generic Variables"
 * ===============================================
 */

// To can use more than 1 SPI in the same time without any over write .
SPI_Congig* Global_SPI_Congig[2] = {NULL , NULL} ;
SPI_Congig Global_SPI_Congig1 ;
SPI_Congig Global_SPI_Congig2 ;

/*
 * ===============================================
				"Generic Function"
 * ===============================================
 */
// Related Generic Variables to can use more than 1 SPI in the same time without any over write .
#define 		SPI1_INDEX			0
#define 		SPI2_INDEX			1

// Check Transmit & Receive to Buffer
#define 		SPI_SR_TXE			((uint8_t)0x02)			// Transmit Buffer is Empty
#define 		SPI_SR_RXNE			((uint8_t)0x01)			// Receive Buffer is NOT Empty


/*
 * ===============================================
 * APIs Supported by "MCAL SPI DRIVER"
 * ===============================================
 */

/**================================================================
 * @Fn					- MCAL_SPI_Init
 * @brief 				- Initialization The SPI according to RTM
 * @param[in] 			- SPIx
 * @param[in] 			- SPI_Congig
 * @retval				- NONE
 * Note					- Support for SPI Full Duplex Master/Slave only & NSS HW/SW
 *						- in case of Master You have to configure Pin and device it.
 */

void MCAL_SPI_Init(SPI_Typedef* SPIx , SPI_Congig* SPI_Congig)
{
	// Safety for Registers
	uint16_t TempReg_CR1 = 0 ;
	uint16_t TempReg_CR2 = 0 ;

	if(SPIx == SPI1){
		Global_SPI_Congig1 = *SPI_Congig ;
		Global_SPI_Congig[SPI1_INDEX] = &Global_SPI_Congig1 ;
		RCC_SPI1_CLK_EN() ;
	}
	else if(SPIx == SPI2){
		Global_SPI_Congig2 = *SPI_Congig ;
		Global_SPI_Congig[SPI2_INDEX] = &Global_SPI_Congig2 ;
		RCC_SPI2_CLK_EN() ;
	}

	// Enable SPI CR1: BIT 6 SPE : SPI Enable
	TempReg_CR1 = (0x1U<<6) ;

	// Master/ Slave
	TempReg_CR1 |= SPI_Congig->Device_Mode ;

	// SPI Communication Mode
	TempReg_CR1 |= SPI_Congig->Communication_Mode ;

	// SPI Frame Format
	TempReg_CR1 |= SPI_Congig->Frame_Format ;

	// SPI DataSize Frame Format
	TempReg_CR1 |= SPI_Congig->DataSize_Frame_Format ;

	// SPI CLKPolarity
	TempReg_CR1 |= SPI_Congig->CLKPolarity ;

	// SPI CLKPhese
	TempReg_CR1 |= SPI_Congig->CLKPhese ;

	// SPI NSS
	if(SPI_Congig->NSS == SPI_NSS_Hardware_Master_SS_Output_Enable){
		TempReg_CR2 |= SPI_Congig->NSS ;									// ========================Hardware============================
	}
	else if(SPI_Congig->NSS == SPI_NSS_Hardware_Master_SS_Output_Disable){	// ========================Hardware============================
		TempReg_CR2 &= SPI_Congig->NSS ;
	}
	else{
		TempReg_CR1 |= SPI_Congig->NSS ;									// ==================Software(Master | Slave)==================

	}

	// SPI BaudRate PreScaler
	TempReg_CR1 |= SPI_Congig->SPI_BaudRate_PreScaler ;

	// SPI IRQ Enable
	if(SPI_Congig->IRQ_Enable != SPI_IRQ_Enable_NONE){
		// SPI Interrupt Enable
		TempReg_CR2 |= SPI_Congig->IRQ_Enable ;

		if(SPIx == SPI1){
			NVIC_IRQ35_SPI1_Enable ;
		}
		else if(SPIx == SPI2){
			NVIC_IRQ36_SPI2_Enable ;
		}
	}

	SPIx->SPI_CR1 = TempReg_CR1 ;
	SPIx->SPI_CR2 = TempReg_CR2 ;

}

/**================================================================
 * @Fn					- MCAL_SPI_DeInit
 * @brief 				- DeInitialization The SPI according to RTM
 * @param[in] 			- SPIx
 * @param[in] 			- NONE
 * @retval				- NONE
 * Note					- Support for SPI Full Duplex Master/Slave only & NSS HW/SW
 *						- in case of Master You have to configure Pin and device it.
 */

void MCAL_SPI_DeInit(SPI_Typedef* SPIx )
{
	if(SPIx == SPI1){
		NVIC_IRQ35_SPI1_Disable ;
		RCC_SPI1_Reset() ;
	}
	else if(SPIx == SPI2){
		NVIC_IRQ36_SPI2_Disable ;
		RCC_SPI2_Reset() ;
	}

}

/**================================================================
 * @Fn					- MCAL_SPI_GPIO_Set_Pins
 * @brief 				- SPI GPIO SET PIN
 * @param[in] 			- SPIx
 * @param[in] 			- NONE
 * @retval				- NONE
 * Note					- NONE
 */

void MCAL_SPI_GPIO_Set_Pins(SPI_Typedef* SPIx)
{
	GPIO_PinConfig_t pincfg ;
	if(SPIx == SPI1){
		//SPI1_NSS  : PA4
		//SPI1_SCK  : PA5
		//SPI1_MISO : PA6
		//SPI1_MOSI : PA7

		if(Global_SPI_Congig[SPI1_INDEX]->Device_Mode == SPI_Device_Mode_MASTER){
			//SPI1_NSS  : PA4
			switch(Global_SPI_Congig[SPI1_INDEX]->NSS){

			case SPI_NSS_Hardware_Master_SS_Output_Disable :
				// SPIx_NSS Hardware master /slave Input floating
				pincfg.GPIO_PinNumber = GPIO_PIN_4 ;
				pincfg.GPIO_MODE = GPIO_MODE_Input_Floating ;
				MCAL_GPIO_Init(GPIOA, &pincfg) ;
				break ;

			case SPI_NSS_Hardware_Master_SS_Output_Enable :
				//SPIx_NSS Hardware master/ NSS output enabled Alternate function push-pull
				pincfg.GPIO_PinNumber = GPIO_PIN_4 ;
				pincfg.GPIO_MODE = GPIO_MODE_Output_AF_Push_pull ;
				pincfg.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
				MCAL_GPIO_Init(GPIOA, &pincfg) ;
				break ;
			}

			// SPI1_SCK  : PA5
			// SPIx_SCK Master Alternate function push-pull
			pincfg.GPIO_PinNumber = GPIO_PIN_5 ;
			pincfg.GPIO_MODE = GPIO_MODE_Output_AF_Push_pull ;
			pincfg.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
			MCAL_GPIO_Init(GPIOA, &pincfg) ;

			// SPI1_MISO : PA6
			// SPIx_MISO Full duplex / master Input floating / Input pull-up
			pincfg.GPIO_PinNumber = GPIO_PIN_6 ;
			pincfg.GPIO_MODE = GPIO_MODE_Input_Floating ;
			MCAL_GPIO_Init(GPIOA, &pincfg) ;

			// SPI1_MOSI : PA7
			// SPIx_MOSI Full duplex / master Alternate function push-pull
			pincfg.GPIO_PinNumber = GPIO_PIN_7 ;
			pincfg.GPIO_MODE = GPIO_MODE_Output_AF_Push_pull ;
			pincfg.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
			MCAL_GPIO_Init(GPIOA, &pincfg) ;

		}
		else{ // SLAVE
			//SPI1_NSS  : PA4
			//SPI1_SCK  : PA5
			//SPI1_MISO : PA6
			//SPI1_MOSI : PA7

			//SPI1_NSS  : PA4
			if(Global_SPI_Congig[SPI1_INDEX]->NSS == SPI_NSS_Hardware_Slave){
				//  SPIx_NSS Hardware master /slave Input floating
				pincfg.GPIO_PinNumber = GPIO_PIN_4 ;
				pincfg.GPIO_MODE = GPIO_MODE_Input_Floating ;
				MCAL_GPIO_Init(GPIOA, &pincfg) ;

			}
			// SPI1_SCK  : PA5
			// SPIx_SCK Slave Input floating
			pincfg.GPIO_PinNumber = GPIO_PIN_5 ;
			pincfg.GPIO_MODE = GPIO_MODE_Input_Floating ;
			MCAL_GPIO_Init(GPIOA, &pincfg) ;

			// SPI1_MISO : PA6
			// SPIx_MISO Full duplex /  slave (point to point) Alternate function push-pull
			pincfg.GPIO_PinNumber = GPIO_PIN_6 ;
			pincfg.GPIO_MODE = GPIO_MODE_Output_AF_Push_pull;
			pincfg.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
			MCAL_GPIO_Init(GPIOA, &pincfg) ;

			// SPI1_MOSI : PA7
			// SPIx_MOSI Full duplex /  slave Input floating / Input pull-up
			pincfg.GPIO_PinNumber = GPIO_PIN_7 ;
			pincfg.GPIO_MODE = GPIO_MODE_Input_AF;
			MCAL_GPIO_Init(GPIOA, &pincfg) ;

		}

	}

	else if(SPIx == SPI2){
		//SPI2_NSS  : PB12
		//SPI2_SCK  : PB13
		//SPI2_MISO : PB14
		//SPI2_MOSI : PB15

		if(Global_SPI_Congig[SPI2_INDEX]->Device_Mode == SPI_Device_Mode_MASTER){
			//SPI2_NSS  : PB12
			switch(Global_SPI_Congig[SPI2_INDEX]->NSS){
			case SPI_NSS_Hardware_Master_SS_Output_Disable :
				// SPIx_NSS Hardware master /slave Input floating
				pincfg.GPIO_PinNumber = GPIO_PIN_12 ;
				pincfg.GPIO_MODE = GPIO_MODE_Input_Floating ;
				MCAL_GPIO_Init(GPIOB, &pincfg) ;
				break ;

			case SPI_NSS_Hardware_Master_SS_Output_Enable :
				//SPIx_NSS Hardware master/ NSS output enabled Alternate function push-pull
				pincfg.GPIO_PinNumber = GPIO_PIN_12 ;
				pincfg.GPIO_MODE = GPIO_MODE_Output_AF_Push_pull ;
				pincfg.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
				MCAL_GPIO_Init(GPIOB, &pincfg) ;
				break ;
			}
			//SPI2_SCK  : PB13
			// SPIx_SCK Master Alternate function push-pull
			pincfg.GPIO_PinNumber = GPIO_PIN_13 ;
			pincfg.GPIO_MODE = GPIO_MODE_Output_AF_Push_pull ;
			pincfg.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
			MCAL_GPIO_Init(GPIOB, &pincfg) ;

			//SPI2_MISO : PB14
			// SPIx_MISO Full duplex / master Input floating / Input pull-up
			pincfg.GPIO_PinNumber = GPIO_PIN_14 ;
			pincfg.GPIO_MODE = GPIO_MODE_Input_Floating ;
			MCAL_GPIO_Init(GPIOB, &pincfg) ;

			//SPI2_MOSI : PB15
			// SPIx_MOSI Full duplex / master Alternate function push-pull
			pincfg.GPIO_PinNumber = GPIO_PIN_15 ;
			pincfg.GPIO_MODE = GPIO_MODE_Output_AF_Push_pull ;
			pincfg.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
			MCAL_GPIO_Init(GPIOB, &pincfg) ;

		}
		else{ // SLAVE
			//SPI2_NSS  : PB12
			//SPI2_SCK  : PB13
			//SPI2_MISO : PB14
			//SPI2_MOSI : PB15

			//SPI2_NSS  : PB12
			if(Global_SPI_Congig[SPI2_INDEX]->NSS == SPI_NSS_Hardware_Slave){
				//  SPIx_NSS Hardware master /slave Input floating
				pincfg.GPIO_PinNumber = GPIO_PIN_12 ;
				pincfg.GPIO_MODE = GPIO_MODE_Input_Floating ;
				MCAL_GPIO_Init(GPIOB, &pincfg) ;

			}
			//SPI2_SCK  : PB13
			// SPIx_SCK Slave Input floating
			pincfg.GPIO_PinNumber = GPIO_PIN_13 ;
			pincfg.GPIO_MODE = GPIO_MODE_Input_Floating ;
			MCAL_GPIO_Init(GPIOB, &pincfg) ;

			//SPI2_MISO : PB14
			// SPIx_MISO Full duplex /  slave (point to point) Alternate function push-pull
			pincfg.GPIO_PinNumber = GPIO_PIN_14 ;
			pincfg.GPIO_MODE = GPIO_MODE_Output_AF_Push_pull;
			pincfg.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
			MCAL_GPIO_Init(GPIOB, &pincfg) ;

			//SPI2_MOSI : PB15
			// SPIx_MOSI Full duplex /  slave Input floating / Input pull-up
			pincfg.GPIO_PinNumber = GPIO_PIN_15 ;
			pincfg.GPIO_MODE = GPIO_MODE_Input_AF;
			MCAL_GPIO_Init(GPIOB, &pincfg) ;

		}

	}

}

/**================================================================
 * @Fn					- MCAL_SPI_Send_Data
 * @brief 				- SPI SEND DATA
 * @param[in] 			- SPIx
 * @param[in] 			- pTXBuffer
 * @param[in] 			- PollingEnable
 * @retval				- NONE
 * Note					- NONE
 *
 *
 */

void MCAL_SPI_Send_Data(SPI_Typedef* SPIx , uint16_t* pTXBuffer , enum PollingMichanism PollingEnable)
{
	// Transmit & Receive to Buffer
	if(PollingEnable == Polling_Enable)
		while (!((SPIx->SPI_SR) & SPI_SR_TXE)) ;
	SPIx->SPI_DR = *pTXBuffer ;

}

/**================================================================
 * @Fn					- MCAL_SPI_Receive_Data
 * @brief 				- SPI Receive Data
 * @param[in] 			- SPIx
 * @param[in] 			- pTXBuffer
 * @param[in] 			- PollingEnable
 * @retval				- NONE
 * Note					- NONE
 *
 *
 */

void MCAL_SPI_Receive_Data(SPI_Typedef* SPIx , uint16_t* pTXBuffer , enum PollingMichanism PollingEnable)
{
	if(PollingEnable == Polling_Enable)
		while (!((SPIx->SPI_SR) & SPI_SR_RXNE)) ;
	*pTXBuffer = SPIx->SPI_DR ;

}

/**================================================================
 * @Fn					- MCAL_SPI_Send_Receive_Data
 * @brief 				- SPI Send AND Receive Data
  * @param[in] 			- SPIx
 * @param[in] 			- pTXBuffer
 * @param[in] 			- PollingEnable
 * @retval				- NONE
 * Note					- NONE
 */

void MCAL_SPI_Send_Receive_Data(SPI_Typedef* SPIx , uint16_t* pTXBuffer , enum PollingMichanism PollingEnable)
{
	// SEND DATA
	if(PollingEnable == Polling_Enable)
		while (!((SPIx->SPI_SR) & SPI_SR_TXE)) ;
	SPIx->SPI_DR = *pTXBuffer ;

	// Receive Data
	if(PollingEnable == Polling_Enable)
		while (!((SPIx->SPI_SR) & SPI_SR_RXNE)) ;
	*pTXBuffer = SPIx->SPI_DR ;

}


//========================================== IRQ ==========================================

void SPI1_IRQHandler(void){

	struct S_IRQ_SRC irq_src ;

	irq_src.TXE =  ( ((SPI1->SPI_SR) & (1<<1)) >> 1) ;
	irq_src.RXEN = ( ((SPI1->SPI_SR) & (1<<0)) >> 0) ;
	irq_src.ERRI = ( ((SPI1->SPI_SR) & (1<<4)) >> 4) ;

	Global_SPI_Congig[SPI1_INDEX]->P_IRQ_CallBack(irq_src) ;
}

void SPI2_IRQHandler(void){

	struct S_IRQ_SRC irq_src ;

	irq_src.TXE =  ( ((SPI2->SPI_SR) & (1<<1)) >> 1) ;
	irq_src.RXEN = ( ((SPI2->SPI_SR) & (1<<0)) >> 0) ;
	irq_src.ERRI = ( ((SPI2->SPI_SR) & (1<<4)) >> 4) ;

	Global_SPI_Congig[SPI2_INDEX]->P_IRQ_CallBack(irq_src) ;

}
