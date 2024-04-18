/*
 * Keypad_ME.c
 *
 *  Created on: Mar 30, 2024
 *      Author:  ENG Menna_Gabely
 */

//-----------------------------
//Includes
//----------------------------
#include "Keypad_ME.h"


void keypad_Init()
{
	GPIO_PinConfig_t PinCinfg ;

	PinCinfg.GPIO_PinNumber = GPIO_PIN_0 ;
	PinCinfg.GPIO_MODE = GPIO_MODE_Input_pull_up ;
	MCAL_GPIO_Init(GPIOB, &PinCinfg) ;

	PinCinfg.GPIO_PinNumber= GPIO_PIN_1 ;
	PinCinfg.GPIO_MODE = GPIO_MODE_Input_pull_up ;
	MCAL_GPIO_Init(GPIOB, &PinCinfg);

	PinCinfg.GPIO_PinNumber = GPIO_PIN_3 ;
	PinCinfg.GPIO_MODE = GPIO_MODE_Input_pull_up ;
	MCAL_GPIO_Init(GPIOB, &PinCinfg) ;

	PinCinfg.GPIO_PinNumber = GPIO_PIN_4 ;
	PinCinfg.GPIO_MODE = GPIO_MODE_Input_pull_up ;
	MCAL_GPIO_Init(GPIOB, &PinCinfg) ;

	PinCinfg.GPIO_PinNumber = GPIO_PIN_5 ;
	PinCinfg.GPIO_MODE = GPIO_MODE_Output_push_pull ;
	PinCinfg.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
	MCAL_GPIO_Init(GPIOB, &PinCinfg) ;

	PinCinfg.GPIO_PinNumber = GPIO_PIN_6 ;
	PinCinfg.GPIO_MODE = GPIO_MODE_Output_push_pull ;
	PinCinfg.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
	MCAL_GPIO_Init(GPIOB, &PinCinfg) ;

	PinCinfg.GPIO_PinNumber = GPIO_PIN_7 ;
	PinCinfg.GPIO_MODE = GPIO_MODE_Output_push_pull ;
	PinCinfg.GPIO_Output_Speed = GPIO_Output_Speed_10M ;
	MCAL_GPIO_Init(GPIOB, &PinCinfg) ;
}
char keypad_Read(void)
{
	MCAL_GPIO_WritePort(GPIOB, 0x0020) ;// Make Pin B5 High
	if(  (MCAL_GPIO_ReadPort(GPIOB)) &(uint16_t)(1<<0) ) return '*' ;
	if(  (MCAL_GPIO_ReadPort(GPIOB)) &(uint16_t)(1<<1) ) return '7' ;
	if(  (MCAL_GPIO_ReadPort(GPIOB)) &(uint16_t)(1<<3) ) return '4' ;
	if(  (MCAL_GPIO_ReadPort(GPIOB)) &(uint16_t)(1<<4) ) return '1' ;


	MCAL_GPIO_WritePort(GPIOB, 0x0040) ; // Make Pin B6 High
	if(  (MCAL_GPIO_ReadPort(GPIOB)) &(uint16_t)(1<<0) ) return '0' ;
	if(  (MCAL_GPIO_ReadPort(GPIOB)) &(uint16_t)(1<<1) ) return '8' ;
	if(  (MCAL_GPIO_ReadPort(GPIOB)) &(uint16_t)(1<<3) ) return '5' ;
	if(  (MCAL_GPIO_ReadPort(GPIOB)) &(uint16_t)(1<<4) ) return '2' ;

	MCAL_GPIO_WritePort(GPIOB, 0x0080) ; // Make Pin B7 High
	if(  (MCAL_GPIO_ReadPort(GPIOB)) &(uint16_t)(1<<0) ) return '#' ;
	if(  (MCAL_GPIO_ReadPort(GPIOB)) &(uint16_t)(1<<1) ) return '9' ;
	if(  (MCAL_GPIO_ReadPort(GPIOB)) &(uint16_t)(1<<3) ) return '6' ;
	if(  (MCAL_GPIO_ReadPort(GPIOB)) &(uint16_t)(1<<4) ) return '3' ;


	return 'N' ;

}
