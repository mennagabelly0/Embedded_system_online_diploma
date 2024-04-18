/*
 *  @author         : 			ENG Menna_Gabely
 *
 */
#include "STM32F103X6.h"
#include "GPIO_DRIVER_STM32F103C6.h"
/*
 * ===============================================
 * APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */
uint8_t Get_CRLH_Position (uint16_t PinNumber) {
	switch (PinNumber)
	{
	case GPIO_PIN_0 :
		return 0 ;
		break ;
	case GPIO_PIN_1 :
		return 4 ;
		break ;
	case GPIO_PIN_2 :
		return 8 ;
		break ;
	case GPIO_PIN_3 :
		return 12 ;
		break ;
	case GPIO_PIN_4 :
		return 16 ;
		break ;
	case GPIO_PIN_5 :
		return 20 ;
		break ;
	case GPIO_PIN_6 :
		return 24 ;
		break ;
	case GPIO_PIN_7 :
		return 28 ;
		break ;

	case GPIO_PIN_8 :
		return 0 ;
		break ;
	case GPIO_PIN_9 :
		return 4 ;
		break ;
	case GPIO_PIN_10 :
		return 8 ;
		break ;
	case GPIO_PIN_11 :
		return 12 ;
		break ;
	case GPIO_PIN_12 :
		return 16 ;
		break ;
	case GPIO_PIN_13:
		return 20 ;
		break ;
	case GPIO_PIN_14 :
		return 24 ;
		break ;
	case GPIO_PIN_15 :
		return 28 ;
		break ;

	}
	return 0 ;


}
/**================================================================
 * @Fn					- MCAL_GPIO_Init
 * @brief 				- Initialize the GPIOx PINy according to the specified parameter in the PinConfig
 * @param[in] 			- GPIOx
 * @param[in] 			- PinConfig
 * @retval				- none
 * Note					- In STM32F103C6 A , B fully included in LQFP48 Package ,
 * 									     C , D Partial included in LQFP48 Package ,
 * 						      			 E NOT included in LQFP48 Package.
 */

void MCAL_GPIO_Init(GPIO_Typedef *GPIOx ,GPIO_PinConfig_t* PinConfig ) {
	// Port Configuration register low (GPIOx_CRL) Configure PINs from 0 >>> 7
	// Port Configuration register High (GPIOx_CRH) Configure PINs from 8 >>> 15
	volatile uint32_t* configregister = NULL ;
	uint8_t PIN_Config = 0 ;
	configregister = (PinConfig ->GPIO_PinNumber < GPIO_PIN_8) ? &GPIOx->CRL : &GPIOx->CRH ; // TO check pin is low(0>>>7) or high(8>>>15)

	//clear CNF , MODE
	(*configregister) &= ~(0xf << Get_CRLH_Position(PinConfig->GPIO_PinNumber)) ;

	// if pin is output
	if((PinConfig->GPIO_MODE == GPIO_MODE_Output_push_pull ) || (PinConfig->GPIO_MODE == GPIO_MODE_Output_Open_drain ) || (PinConfig->GPIO_MODE == GPIO_MODE_Output_AF_Push_pull ) || (PinConfig->GPIO_MODE == GPIO_MODE_Output_AF_Open_drain  ))
	{
		//Set CNF , MODE
		PIN_Config = ((((PinConfig->GPIO_MODE - 4) << 2 ) | (PinConfig -> GPIO_Output_Speed)) & 0x0f ) ;
//		(*configregister) |= ((PIN_Config) << Get_CRLH_Position(PinConfig->GPIO_PinNumber)) ;

	}
	// if pin is output
	else { // MODE  = 00 INPUT RESET STATE
		if((PinConfig->GPIO_MODE == GPIO_MODE_Analog ) ||(PinConfig->GPIO_MODE == GPIO_MODE_Input_Floating ) ){
			//Set CNF , MODE
			PIN_Config = ((((PinConfig->GPIO_MODE ) << 2 ) | 0x0 ) & 0x0f ) ;
//			(*configregister) |= ((PIN_Config) << Get_CRLH_Position(PinConfig->GPIO_PinNumber)) ;

		}else if(PinConfig->GPIO_MODE == GPIO_MODE_Input_AF ){
			//Set CNF , MODE
			PIN_Config = (((GPIO_MODE_Input_AF << 2 ) | 0x0 ) & 0x0f ) ;
//			(*configregister) |= ((PIN_Config) << Get_CRLH_Position(PinConfig->GPIO_PinNumber)) ;

		}
		else{
			PIN_Config = (((GPIO_MODE_Input_pull_up << 2 ) | 0x0 ) & 0x0f)  ;
//			(*configregister) |= ((PIN_Config) << Get_CRLH_Position(PinConfig->GPIO_PinNumber)) ;

			if(PinConfig->GPIO_MODE == GPIO_MODE_Input_pull_up){
		// in case Pull_down table 20 port bit configuration table PXODR 1
				GPIOx->ODR |= PinConfig->GPIO_PinNumber ;
			}
			else{
		//  in case Pull_down  table 20 port bit configuration table PXODR 0
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber) ;

			}

		}
	}
	(*configregister) |= ((PIN_Config) << Get_CRLH_Position(PinConfig->GPIO_PinNumber)) ;
}


/**================================================================
 * @Fn					- MCAL_GPIO_DeInit
 * @brief 				- Reset all the GPIO Registers
 * @param[in] 			- GPIOx
 * @param[out] 			- none
 * @retval				- none
 * Note					- none
 */
void MCAL_GPIO_DeInit(GPIO_Typedef *GPIOx ){
// if  Microcontroller is Not consists of Reset mode
//	GPIOx->BRR = 0x00000000 ;
//	GPIOx->BSRR = 0x00000000 ;
//	GPIOx->CRH = 0x44444444 ;
//	GPIOx->CRL = 0x44444444 ;
////	GPIOx->IDR = ; read only
//	GPIOx->LCKR = 0x00000000 ;
//	GPIOx->ODR = 0x00000000 ;

	// use reset mode in RCC
	// Reset to peripheral
	// set and clear by SW according to TRM
	if(GPIOx == GPIOA){
		RCC->APB2RSTR |= (1<<2) ; // BIT 2 IOPARST : IO port A RESET
		RCC->APB2RSTR &= ~(1<<2) ;
	}
	else if(GPIOx == GPIOB){
		RCC->APB2RSTR |= (1<<3) ; // BIT 3 IOPARST : IO port B RESET
		RCC->APB2RSTR &= ~(1<<3) ;
	}
	else if(GPIOx == GPIOC){
			RCC->APB2RSTR |= (1<<4) ; // BIT 4 IOPARST : IO port C RESET
			RCC->APB2RSTR &= ~(1<<4) ;
		}
	else if(GPIOx == GPIOD){
			RCC->APB2RSTR |= (1<<5) ; // BIT 5 IOPARST : IO port D RESET
			RCC->APB2RSTR &= ~(1<<5) ;
		}
	else if(GPIOx == GPIOE){
				RCC->APB2RSTR |= (1<<6) ; // BIT 6 IOPARST : IO port E RESET
				RCC->APB2RSTR &= ~(1<<6) ;
			}

}

///////////////////////////////////////// READ API's

/**================================================================
 * @Fn					- MCAL_GPIO_ReadPin
 * @brief 				- Read specific Pin
 * @param[in] 			- GPIOx
 * @param[in]		 	- PinNumber ==> set pin based on @REF GPIO_PIN_Define
 * @retval				- the input pin value (two value based on @REF GPIO_PINS_State)
 * Note					- none
 */

uint8_t MCAL_GPIO_ReadPin(GPIO_Typedef *GPIOx , uint16_t PinNumber ) {
	uint8_t bitstatus ;
	if(((GPIOx->IDR)& PinNumber) != (uint32_t)GPIO_PIN_Reset ){
		bitstatus = GPIO_PIN_Set ; // 1
	}
	else {
		bitstatus = GPIO_PIN_Reset ; // 0
	}
	return bitstatus ;

}


/**================================================================
 * @Fn					- MCAL_GPIO_ReadPort
 * @brief 				- Read the input port value
 * @param[in] 			- GPIOx
 * @param[out] 			- none
 * @retval				- the input port value
 * Note					- none
 */
uint16_t MCAL_GPIO_ReadPort (GPIO_Typedef *GPIOx ) {

	uint16_t port_value ;
	port_value = (uint16_t)(GPIOx->IDR) ;
	return port_value ;

}


////////////////////////////////////// Write API's

/**================================================================
 * @Fn					- MCAL_GPIO_WritePin
 * @brief 				- Write in specific Pin
 * @param[in] 			- GPIOx
 * @param[in] 			- PinNumber ======> @REF GPIO_PIN_Define
 * @param[in]			- Value
 * @retval				- none
 * Note					- none
 */
void MCAL_GPIO_WritePin(GPIO_Typedef *GPIOx , uint16_t PinNumber , uint16_t Value  ){
	if( Value != GPIO_PIN_Reset ){
//		GPIOx->ODR |= PinNumber ;
		// or use Register according to TRM
		GPIOx->BSRR = (uint32_t)PinNumber ;

		}
		else {
			//use Register according to TRM
			GPIOx->BRR = (uint32_t)PinNumber ;
		}
}

/**================================================================
 * @Fn					- MCAL_GPIO_WritePort
 * @brief 				- Write the input port value
 * @param[in] 			- GPIOx
 * @param[in] 			- none
 * @retval				- none
 * Note					- none
 */
void MCAL_GPIO_WritePort (GPIO_Typedef *GPIOx , uint16_t Value ){

	GPIOx->ODR = (uint32_t)Value ;

}

///////////////////////////////////// Toggle LED

/**================================================================
 * @Fn					- MCAL_GPIO_TogglePin
 * @brief 				- Toggle specified GPIO Pin
 * @param[in] 			- GPIOx
 * @param[in] 			- PinNumber ======> @REF GPIO_PIN_Define
 * @retval				- none
 * Note					- none
 */
void MCAL_GPIO_TogglePin(GPIO_Typedef *GPIOx , uint16_t PinNumber ) {
	GPIOx->ODR ^= (PinNumber) ;

}

////////////////////////////////// Lock Pin
/**================================================================
 * @Fn					- MCAL_GPIO_LockPin
 * @brief 				- lock bit freezes the corresponding 4 bits of the control register (CRL, CRH).
 * @param[in] 			- GPIOx
 * @param[in] 			- PinNumber ======> @REF GPIO_PIN_Define
 * @retval				- freeze pin =====> @REF GPIO_RETERN_LOCK
 * Note					- none
 */
uint8_t MCAL_GPIO_LockPin(GPIO_Typedef *GPIOx , uint16_t PinNumber ){ // @REF GPIO_RETERN_LOCK

//	Bit 16 LCKK[16]: Lock key
//	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
//	0: Port configuration lock key not active
//	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
//	LOCK key writing sequence:
//	Write 1
//	Write 0
//	Write 1
//	Read 0
//	Read 1 (this read is optional but confirms that the lock is active)
//	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
//	Any error in the lock sequence will abort the lock.
//	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
//	These bits are read write but can only be written when the LCKK bit is 0.
//	0: Port configuration not locked
//	1: Port configuration locked.

	volatile uint32_t temp = 1<<16 ; //	Bit 16 LCKK[16]: Lock key
	temp |= PinNumber ; // set the LCKy

	//	LOCK key writing sequence:
	//	Write 1
	GPIOx->LCKR = temp ;
	//	Write 0
	GPIOx->LCKR = PinNumber ;
	//	Write 1
	GPIOx->LCKR = temp ;
	//	Read 0
	temp = 	GPIOx->LCKR ;
	//	Read 1 (this read is optional but confirms that the lock is active)
	if((uint32_t)(GPIOx->LCKR & 1<<16 )){
		return GPIO_RETERN_LOCK_Enable ;
	}
	else{
		return GPIO_RETERN_LOCK_Error ;
	}
}


/**=================================================================
 * @Fn -                    - MCAL_GPIO_WriteGroup
 * @brief -                 -Write on specific portion of the port
 * @param [in] -            -GPIOx : where x can be (A..E depending on device used)
 * @param [in] -            -Vlaue to write on this port
 * @param [in] -            -Mask : bit with 1 will be affected , bits with 0 won't be affected
 * @retval -                -none
 * note -                   -none
 */
/**================================================================= */
void MCAL_GPIO_WriteGroup(GPIO_Typedef * GPIOx ,uint16_t Value , uint16_t Mask)
{
	GPIOx->ODR &= ~(Mask);				// clear the group
	GPIOx->ODR |= (Value & Mask);		// put the new value
}
