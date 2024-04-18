/*/
 * GPIO_DRIVER_STM32F103C6.h
 *
 *  Created on: Dec 23, 2023
 *  @author         : 			ENG Menna_Gabely
 */

#ifndef INC_GPIO_DRIVER_STM32F103C6_H_
#define INC_GPIO_DRIVER_STM32F103C6_H_
//-----------------------------
//Includes
//-----------------------------
#include "STM32F103X6.h"
//-----------------------------

//Configuration Structure
typedef struct{
	uint16_t GPIO_PinNumber ;           // specifies the GPIO pin to be configured , this parameter must be set based on  @REF GPIO_PIN_Define
	uint8_t GPIO_MODE ;                // specifies the Operation mode for selected pins , this parameter can be a value of  @REF GPIO_MODE_Define
	uint8_t GPIO_Output_Speed ;       // specifies the speed for selected pins , this parameter can be a value of  @REF GPIO_Output_Speed_Define

}GPIO_PinConfig_t;

// @REF GPIO_PINS_State
#define GPIO_PIN_Set  					    1
#define GPIO_PIN_Reset  					0

// @REF GPIO_RETERN_LOCK
#define GPIO_RETERN_LOCK_Enable             1
#define GPIO_RETERN_LOCK_Error              0



//-*-*-*-*-*-*-*-*-*-*-*-
// Macros Configuration Reference :
//-*-*-*-*-*-*-*-*-*-*-*
//@REF GPIO_PIN_Define
#define GPIO_PIN_0 							((uint16_t)0x0001) //PIN 0 Selected
#define GPIO_PIN_1 							((uint16_t)0x0002) //PIN 1 Selected
#define GPIO_PIN_2 							((uint16_t)0x0004) //PIN 2 Selected
#define GPIO_PIN_3 							((uint16_t)0x0008) //PIN 3 Selected
#define GPIO_PIN_4							((uint16_t)0x0010) //PIN 4 Selected
#define GPIO_PIN_5						    ((uint16_t)0x0020) //PIN 5 Selected
#define GPIO_PIN_6 							((uint16_t)0x0040) //PIN 6 Selected
#define GPIO_PIN_7 							((uint16_t)0x0080) //PIN 7 Selected
#define GPIO_PIN_8 							((uint16_t)0x0100) //PIN 8 Selected
#define GPIO_PIN_9        					((uint16_t)0x0200) //PIN 9 Selected
#define GPIO_PIN_10 						((uint16_t)0x0400) //PIN 10 Selected
#define GPIO_PIN_11		 					((uint16_t)0x0800) //PIN 11 Selected
#define GPIO_PIN_12 						((uint16_t)0x1000) //PIN 12 Selected
#define GPIO_PIN_13 						((uint16_t)0x2000) //PIN 13 Selected
#define GPIO_PIN_14 						((uint16_t)0x4000) //PIN 14 Selected
#define GPIO_PIN_15 						((uint16_t)0x8000) //PIN 15 Selected
#define GPIO_PIN_ALL 						((uint16_t)0xFFFF) //ALL PINS  Selected

#define GPIO_PIN_MASK                 		0x0000FFFFUL //PIN MASK FOR ASSERT TEST

// @REF GPIO_MODE_Define
/*
0: Analog mode
1: Floating input (reset state)
2: Input with pull-up
3: pull-down
4: General purpose output push-pull
5: General purpose output Open-drain
6: Alternate function output Push-pull
7: Alternate function output Open-drain
8: Alternate function input
*/

#define GPIO_MODE_Analog           		  	   0x00000000U // 0: Analog mode
#define GPIO_MODE_Input_Floating           	   0x00000001U // 1: Floating input (reset state)
#define GPIO_MODE_Input_pull_up           	   0x00000002U // 2: Input with pull-up
#define GPIO_MODE_Input_Pull_down         	   0x00000003U // 3: pull-down
#define GPIO_MODE_Output_push_pull             0x00000004U // 4: General purpose output push-pull
#define GPIO_MODE_Output_Open_drain            0x00000005U // 5: General purpose output Open-drain
#define GPIO_MODE_Output_AF_Push_pull          0x00000006U // 6: Alternate function output Push-pull
#define GPIO_MODE_Output_AF_Open_drain         0x00000007U // 7: Alternate function output Open-drain
#define GPIO_MODE_Input_AF          		   0x00000008U // 8: Alternate function input

// @REF GPIO_Output_Speed_Define
/*
01: Output mode, max speed 10 MHz.
10: Output mode, max speed 2 MHz.
11: Output mode, max speed 50 MHz.
*/
#define GPIO_Output_Speed_10M                  0x00000001U // 1: Output mode, max speed 10 MHz.
#define GPIO_Output_Speed_2M                   0x00000002U // 2: Output mode, max speed 2 MHz.
#define GPIO_Output_Speed_50M                  0x00000003U // 3: Output mode, max speed 50 MHz.

/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/
void MCAL_GPIO_Init(GPIO_Typedef *GPIOx , GPIO_PinConfig_t* PinConfig ) ;
void MCAL_GPIO_DeInit(GPIO_Typedef *GPIOx ) ;

// READ API's
uint8_t MCAL_GPIO_ReadPin(GPIO_Typedef *GPIOx , uint16_t PinNumber ) ;
uint16_t MCAL_GPIO_ReadPort(GPIO_Typedef *GPIOx ) ;

// Write API's
void MCAL_GPIO_WritePin(GPIO_Typedef *GPIOx , uint16_t PinNumber , uint16_t Value  ) ;
void MCAL_GPIO_WritePort(GPIO_Typedef *GPIOx , uint16_t Value ) ;

//Toggle LED
void MCAL_GPIO_TogglePin(GPIO_Typedef *GPIOx , uint16_t PinNumber ) ;

//Lock Pin
uint8_t MCAL_GPIO_LockPin(GPIO_Typedef *GPIOx , uint16_t PinNumber ) ;

void MCAL_GPIO_WriteGroup(GPIO_Typedef * GPIOx,uint16_t Vlaue,uint16_t mask);


#endif /* INC_GPIO_DRIVER_STM32F103C6_H_ */
