/*
 * EXTI_DRIVER_STM32F103C6.C
 *
 *  Created on: Dec 31, 2023
 *      Author: ENG Menna_Gabely
 */

#include "EXTI_DRIVER_STM32F103C6.h"
#include "GPIO_DRIVER_STM32F103C6.h"

/*
 * ===============================================
				"Generic Variables"
 * ===============================================
 */
	void (* GP_IRQ_CallBack[15])(void) ;

/*
 * ===============================================
				"Generic Macros"
 * ===============================================
 */
#define AFIO_GPIO_EXTI_Mapping(x)	(	(x==GPIOA)?0:\
										(x==GPIOB)?1:\
										(x==GPIOC)?2:\
										(x==GPIOD)?3:0	)

/*
 * ===============================================
				"Generic Function"
 * ===============================================
 */
void Enable_NVIC(uint16_t IRQ){

	switch (IRQ){
	case 0:
		NVIC_IRQ6_EXTI0_Enable ;
		break ;
	case 1:
		NVIC_IRQ7_EXTI1_Enable ;
			break ;
	case 2:
		NVIC_IRQ8_EXTI2_Enable ;
			break ;
	case 3:
		NVIC_IRQ9_EXTI3_Enable ;
			break ;
	case 4:
		NVIC_IRQ10_EXTI4_Enable ;
			break ;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Enable ;
		break ;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Enable ;
		break ;
	}

}

void Diasble_NVIC(uint16_t IRQ){

	switch (IRQ){
	case 0:
		NVIC_IRQ6_EXTI0_Disable ;
		break ;
	case 1:
		NVIC_IRQ7_EXTI1_Disable ;
			break ;
	case 2:
		NVIC_IRQ8_EXTI2_Disable ;
			break ;
	case 3:
		NVIC_IRQ9_EXTI3_Disable ;
			break ;
	case 4:
		NVIC_IRQ10_EXTI4_Disable ;
			break ;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Disable ;
		break ;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Disable ;
		break ;
	}

}



void Update_EXTI(EXTI_PinConfig_t* EXTI_Config)
{
	// 1- configuration GPIO TO be AF => Floating Input
	GPIO_PinConfig_t PinCFG ;
	// Update GPIO Pin to be Floating Input
	PinCFG.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_PIN ;
	PinCFG.GPIO_MODE = GPIO_MODE_Input_Floating ;
	MCAL_GPIO_Init(EXTI_Config->EXTI_PIN.GPIO_Port , &PinCFG) ;

	//=================================================================

	// 2- Update AFIO to Route between EXTI line with PORT A,B,C,D
	uint8_t AFIO_EXTICR_index = EXTI_Config->EXTI_PIN.EXTI_Interrupt_lineNumber / 4 ;
	uint8_t AFIO_EXTICR_Position  = (EXTI_Config->EXTI_PIN.EXTI_Interrupt_lineNumber % 4 ) *4 ; // like bit field

	// clean the four bit
	AFIO->EXTICR[AFIO_EXTICR_index] &= ~(0xF << AFIO_EXTICR_Position ) ;
	AFIO->EXTICR[AFIO_EXTICR_index] |= ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_Port) &0xF) << AFIO_EXTICR_Position) ;

	//=================================================================

	// 3- Update Rising and Falling Edge
	// CLAER RTSR & FTSR Register
	EXTI->RTSR &= ~(1<<EXTI_Config->EXTI_PIN.EXTI_Interrupt_lineNumber) ;
	EXTI->FTSR &= ~(1<<EXTI_Config->EXTI_PIN.EXTI_Interrupt_lineNumber) ;

	if(EXTI_Config->Tregger_case == EXTI_Trigger_Rising){
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_PIN.EXTI_Interrupt_lineNumber) ;

	}
	else if(EXTI_Config->Tregger_case == EXTI_Trigger_Falling){
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_PIN.EXTI_Interrupt_lineNumber) ;

	}
	else if(EXTI_Config->Tregger_case == EXTI_Trigger_RisingAndFalling){
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_PIN.EXTI_Interrupt_lineNumber) ;
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_PIN.EXTI_Interrupt_lineNumber) ;

	}

	//=================================================================

	// 4 - Update IRQ handling CallBack
	GP_IRQ_CallBack[EXTI_Config->EXTI_PIN.EXTI_Interrupt_lineNumber] = EXTI_Config->P_IRQ_CallBack ;

	//=================================================================

	// 5- Enable/Disable IRQ EXTI & NVIC
			//Enable IRQ EXTI
	if(EXTI_Config->IRQ_Enable == EXTI_IRQ_Enable){
		EXTI->IMR |= (1<<EXTI_Config->EXTI_PIN.EXTI_Interrupt_lineNumber) ;
			//Enable NVIC
		Enable_NVIC (EXTI_Config->EXTI_PIN.EXTI_Interrupt_lineNumber) ;

	}else{
			//Disable IRQ EXTI
		EXTI->IMR &= ~(1<<EXTI_Config->EXTI_PIN.EXTI_Interrupt_lineNumber) ;
			//Disable NVIC
		Diasble_NVIC (EXTI_Config->EXTI_PIN.EXTI_Interrupt_lineNumber) ;
	}

}

/*
 * ===============================================
 * APIs Supported by "MCAL External Interrupt DRIVER"
 * ===============================================
 */

/**================================================================
 * @Fn					- MCAL_EXTI_GPIO_Init
 * @brief 				- Initialize External Interrupt from specific pin and specify the mask/trigger/ TRQ
 * @param[in] 			- EXTI_Config Set by @Ref_EXTI_Define , @Ref_EXTI_Trigger_Define , @Ref_EXTI_IRQ_Define
 * @param[in] 			- none
 * @retval				- none
 * Note					- In STM32F103C6 A , B fully included in LQFP48 Package ,
 * 									     C , D Partial included in LQFP48 Package ,
 * 						      			 E NOT included in LQFP48 Package.
 * 						      			 -Also mandatory to enable RCC , AFIO and the corresponding GPIO
 */

void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config) ;



}

/**================================================================
 * @Fn					- MCAL_EXTI_GPIO_DeInit
 * @brief 				- Reset EXTI Register & NVIC Corresponding IRQ mask
 * @param[in] 			- none
 * @param[in] 			- none
 * @retval				- none
 * Note					- none
 *
 */
void MCAL_EXTI_GPIO_DeInit(void)
{
	EXTI->EMR = 0x00000000 ;
	EXTI->FTSR = 0x00000000 ;
	EXTI->IMR = 0x00000000 ;
	EXTI->PR = 0x00000000 ;
	EXTI->RTSR = 0xFFFFFFFF ; // Write 1 to clear bit according to TRM
	EXTI->SWIER = 0x00000000 ;

	// Disable EXTI IRQ from NVIC

	NVIC_IRQ6_EXTI0_Disable	;
	NVIC_IRQ7_EXTI1_Disable	;
	NVIC_IRQ8_EXTI2_Disable	;
	NVIC_IRQ9_EXTI3_Disable	;
	NVIC_IRQ10_EXTI4_Disable ;
	NVIC_IRQ23_EXTI5_9_Disable ;
	NVIC_IRQ40_EXTI10_15_Disable ;



}

/**================================================================
 * @Fn					- MCAL_EXTI_GPIO_Update
 * @brief 				- Update External Interrupt from specific pin and specify the mask/trigger/ TRQ
 * @param[in] 			- EXTI_Config Set by @Ref_EXTI_Define , @Ref_EXTI_Trigger_Define , @Ref_EXTI_IRQ_Define
 * @param[in] 			- none
 * @retval				- none
 * Note					- In STM32F103C6 A , B fully included in LQFP48 Package ,
 * 									     C , D Partial included in LQFP48 Package ,
 * 						      			 E NOT included in LQFP48 Package.
 * 						      			 -Also mandatory to enable RCC , AFIO and the corresponding GPIO
 */
void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config) ;

}


/*
 * ===============================================
				"ISR Function"
 * ===============================================
 */

void EXTI0_IRQHandler (void){
	//Disable Pending register
	EXTI->PR |= 1<<0 ;
	// CALLBACK IRQ
	GP_IRQ_CallBack[0] ();

	}
void EXTI1_IRQHandler (void){
	//Disable Pending register
		EXTI->PR |= (1<<1) ;
		// CALLBACK IRQ
		GP_IRQ_CallBack[1]();

	}
void EXTI2_IRQHandler (void){
	//Disable Pending register
		EXTI->PR |= (1<<2) ;
		// CALLBACK IRQ
		GP_IRQ_CallBack[2]();

	}
void EXTI3_IRQHandler (void){
	//Disable Pending register
		EXTI->PR |= (1<<3) ;
		// CALLBACK IRQ
		GP_IRQ_CallBack[3]();

	}
void EXTI4_IRQHandler (void){
	//Disable Pending register
		EXTI->PR |= (1<<4) ;
		// CALLBACK IRQ
		GP_IRQ_CallBack[4]();

	}
void EXTI9_5_IRQHandler (void){
	if(EXTI->PR & 1<<5){ EXTI->PR |= (1<<5) ; GP_IRQ_CallBack[5](); }
	if(EXTI->PR & 1<<6){ EXTI->PR |= (1<<6) ; GP_IRQ_CallBack[6](); }
	if(EXTI->PR & 1<<7){ EXTI->PR |= (1<<7) ; GP_IRQ_CallBack[7](); }
	if(EXTI->PR & 1<<8){ EXTI->PR |= (1<<8) ; GP_IRQ_CallBack[8](); }
	if(EXTI->PR & 1<<9){ EXTI->PR |= (1<<9) ; GP_IRQ_CallBack[9](); }

	}
void EXTI15_10_IRQHandler (void){
	if(EXTI->PR & 1<<10){ EXTI->PR |= (1<<10) ; GP_IRQ_CallBack[10](); }
	if(EXTI->PR & 1<<11){ EXTI->PR |= (1<<11) ; GP_IRQ_CallBack[11](); }
	if(EXTI->PR & 1<<12){ EXTI->PR |= (1<<12) ; GP_IRQ_CallBack[12](); }
	if(EXTI->PR & 1<<13){ EXTI->PR |= (1<<13) ; GP_IRQ_CallBack[13](); }
	if(EXTI->PR & 1<<14){ EXTI->PR |= (1<<14) ; GP_IRQ_CallBack[14](); }
	if(EXTI->PR & 1<<15){ EXTI->PR |= (1<<15) ; GP_IRQ_CallBack[15](); }

	}


