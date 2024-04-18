/*
 * Keypad_ME.h
 *
 *  Created on: Mar 30, 2024
 *      Author:  ENG Menna_Gabely
 */

#ifndef INCLUDES_KEYPAD_ME_H_
#define INCLUDES_KEYPAD_ME_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103X6.h"
#include "GPIO_DRIVER_STM32F103C6.h"

void keypad_Init();
char keypad_Read(void);

#endif /* INCLUDES_KEYPAD_ME_H_ */
