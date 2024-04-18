/*
 * Servo_Motor.c
 *
 *  Created on: Mar 28, 2024
 *      Author: ENG.Menna Gabely.
 */

#include "Servo_Motor.h"

//Direction of motion
#define UP   1
#define Down 2


//B8 SERVO1
void Servo1_Entry_Gate_Init(void)
{
	/*SERVO MOTOR 1*/
	GPIO_PinConfig_t PinCinfg;
	PinCinfg.GPIO_PinNumber=GPIO_PIN_8;
	PinCinfg.GPIO_MODE = GPIO_MODE_Output_push_pull;
	PinCinfg.GPIO_Output_Speed =GPIO_Output_Speed_10M;
	MCAL_GPIO_Init(GPIOB, &PinCinfg);
}

//Direction Up or Down
void Servo1_Entry_Gate(uint8_t Direction)
{
	if(Direction == UP)
	{
		//servo1 Enter gate up +90
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 1);
		dus(500);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
	}
	if(Direction==Down)
	{
		//servo1 Enter gate down -90
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 1);
		dus(1488);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
	}


}

//B9 SERVO2
void Servo2_Exit_Gate_Init(void)
{
	/*SERVO MOTOR 2*/
	GPIO_PinConfig_t PinCinfg;
	PinCinfg.GPIO_PinNumber=GPIO_PIN_9;
	PinCinfg.GPIO_MODE = GPIO_MODE_Output_push_pull;
	PinCinfg.GPIO_Output_Speed=GPIO_Output_Speed_10M;
	MCAL_GPIO_Init(GPIOB, &PinCinfg);
}

//Direction Up or Down
void Servo2_Exit_Gate(uint8_t Direction)
{
	if(Direction == UP)
	{
		//servo2 Exit gate up +90
		GPIO_PinConfig_t PinCinfg;
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 1);
		dus(500);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);
	}

	if(Direction == Down)
	{
		//servo2 Exit gate down -90
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 1);
		dus(1488);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);
	}

}
