/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Menna_Gabely
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "STM32F103X6.h"
#include "RCC_DRIVER_STM32F103C6.h"
#include "GPIO_DRIVER_STM32F103C6.h"
#include "EXTI_DRIVER_STM32F103C6.h"
#include "USART_DRIVER_STM32F103C6.h"
#include "SPI_DRIVER_STM32F103C6.h"
#include "I2C_DRIVER_STM32F103C6.h"
#include "I2C_Slave_EEPROM.h"
#include "Timer.h"
#include "Servo_Motor.h"
#include "LCD_ME.h"
#include "Keypad_ME.h"



// ===================	Global Variables	===================

uint16_t RFID_CARD_Enter ;
uint16_t RFID_CARD_EXIT  ;
uint8_t Pass[3] = {0} ;
unsigned char Available_Slots = '3' ;
uint8_t Search_Done = 0 ;


// ===================	Global Functions	===================

void UART1_RFID_CARD_Enter_CallBack(void) ;
void UART2_RFID_CARD_EXIT_CallBack(void) ;
void LCD_Welcome(void);
void LCD_Display_Empty_Slots(void);
void LEDs_Init(void);
void PIRs_Iint(void);
void Store_IDs_From_Admin(void);

void Clock_init()
{
	// Enable Clock
	RCC_GPIOA_CLK_EN() ;
	RCC_GPIOB_CLK_EN() ;
	RCC_AFIO_CLK_EN() ;
}

// ===================	LCDs Configurations	===================

LCD_Pins_Config_t LCD1 = {GPIOB,GPIOB,GPIOB,GPIOB,GPIO_PIN_11,GPIO_PIN_10} ;

LCD_Pins_Config_t LCD2 = {GPIOA,GPIOA,GPIOA,GPIOA,GPIO_PIN_5,GPIO_PIN_6} ;

// related to Interrupt Mechanism
// Entry Gate
void UART1_RFID_CARD_Enter_CallBack(void){
	MCAL_UART_Receive_Data(USART1, &RFID_CARD_Enter, Disable) ;
	MCAL_UART_Send_Data(USART1, &RFID_CARD_Enter, Enable) ;

}
// Exit Gate
void UART2_RFID_CARD_EXIT_CallBack(void){
	MCAL_UART_Receive_Data(USART2, &RFID_CARD_EXIT, Disable) ;
	MCAL_UART_Send_Data(USART2, &RFID_CARD_EXIT, Enable) ;
}


int main(void)
{
	// ===================	Initialization	===================
	Clock_init() ;
	keypad_Init() ;
	Timer2_init() ;
	Servo1_Entry_Gate_Init() ;
	Servo2_Exit_Gate_Init() ;

	// ===================	UART1	===================
	// PA9 => TX
	// PA10 => RX
	// PA11 => CTS
	// PA12 => RTS

	UART_Config uart1CFG ;
	uart1CFG.BaudRate = UART_BaudRate_115200 ;
	uart1CFG.HW_Flow_Conterl = UART_HW_Flow_Conterl_NONE ;
	// related to Interrupt Mechanism
	uart1CFG.IRQ_Enable = UART_IRQ_Enable_RXNEIE ;
	uart1CFG.P_IRQ_CallBack = UART1_RFID_CARD_Enter_CallBack ;
	uart1CFG.Parity = UART_Parity_NONE ;
	uart1CFG.Payload_length = UART_Payload_length_8B ;
	uart1CFG.Stop_Bits = UART_Stop_Bits_1 ;
	uart1CFG.UART_Mode = UART_Mode_TX_RX ;
	MCAL_UART_Init(USART1,&uart1CFG) ;
	MCAL_UART_GPIO_Set_Pins(USART1) ;

	// ===================	UART2	===================
	// PA2 => TX
	// PA3 => RX
	// PA0 => CTS
	// PA1 => RTS

	UART_Config uart2CFG ;
	uart2CFG.BaudRate = UART_BaudRate_115200 ;
	uart2CFG.HW_Flow_Conterl = UART_HW_Flow_Conterl_NONE ;
	// related to Interrupt Mechanism
	uart2CFG.IRQ_Enable = UART_IRQ_Enable_RXNEIE ;
	uart2CFG.P_IRQ_CallBack = UART2_RFID_CARD_EXIT_CallBack ;
	uart2CFG.Parity = UART_Parity_NONE ;
	uart2CFG.Payload_length = UART_Payload_length_8B ;
	uart2CFG.Stop_Bits = UART_Stop_Bits_1 ;
	uart2CFG.UART_Mode = UART_Mode_TX_RX ;
	MCAL_UART_Init(USART2,&uart2CFG) ;
	MCAL_UART_GPIO_Set_Pins(USART2) ;

	// ===================	Initialization	===================
	lcd_init(&LCD1) ;
	lcd_init(&LCD2) ;
	LEDs_Init() ;
	PIRs_Iint() ;
	//===================	Enter IDs To Store In Array Pass	===================
	Store_IDs_From_Admin() ;
	int i = 0 ;

	//	Dash Board LCD
	LCD_Welcome() ;
	dms(200) ;
	LCD_Display_Empty_Slots() ;

	// LOOP FOREEVER
	while(1)
	{
		if(Available_Slots>'0')
		{
			lcd_set_position(&LCD2, 2 , 0 ) ;
			lcd_send_string(&LCD2, " Enter ID : ") ;
			lcd_set_position(&LCD2, 3 , 0 ) ;
			lcd_send_string(&LCD2, "Card Reader ") ;
			while(RFID_CARD_Enter ==0 && RFID_CARD_EXIT==0) ; //Wait for Enter any id
		}
		// ====== Parking is full so can not allow any Car =======
		else
		{
			lcd_clear(&LCD2) ;
			lcd_set_position(&LCD2, 0, 0) ;
			lcd_send_string(&LCD2,"Parking Is Full") ;
			lcd_set_position(&LCD2, 2, 0) ;
			lcd_send_string(&LCD2,"Entry Not Allowed") ;
		}

		// Search for IDs in Array
		for(i = 0 ; i<3 ; i++)
		{
			if(RFID_CARD_Enter == Pass[i] || RFID_CARD_EXIT == Pass[i] )
			{
				Search_Done = 1 ;
			}
		}

		// =====================	Entry Gate	=====================

		if(Search_Done == 1 && RFID_CARD_Enter != 0 && Available_Slots >'0')
		{
			lcd_clear(&LCD2) ;
			lcd_set_position(&LCD2, 2, 3) ;
			lcd_send_string(&LCD2,"Right ID") ;
			lcd_set_position(&LCD2, 3, 0) ;
			lcd_send_string(&LCD2,"Entry gate Opens") ;

			MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0) ;
			Servo1_Entry_Gate(UP) ;
			Available_Slots-- ;

			RFID_CARD_Enter =0 ;
			Search_Done =0 ;

			dms(300) ;

			while(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)==1)
			{
				dms(200) ;
			}


			MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1) ;
			Servo1_Entry_Gate(Down) ;


			//	Dash Board LCD
			LCD_Welcome() ;
			dms(200) ;
			LCD_Display_Empty_Slots() ;
		}

		// =====================	Exit Gate	=====================

		if(Search_Done == 1 && RFID_CARD_EXIT != 0 && Available_Slots <'3')
		{
			lcd_clear(&LCD2);
			lcd_set_position(&LCD2, 2, 3);
			lcd_send_string(&LCD2,"Right ID!");
			lcd_set_position(&LCD2, 3, 0);
			lcd_send_string(&LCD2,"Exit Gate Opens");

			//Green led*/
			MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
			Servo2_Exit_Gate(UP);
			Available_Slots++;
			dms(300);
			while(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)==1) //Read the PIR2 state
			{
				dms(200);
			}
			MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
			Servo2_Exit_Gate(Down);

			RFID_CARD_EXIT =0;
			Search_Done =0;

			//	Dash Board LCD
			LCD_Welcome() ;
			dms(200) ;
			LCD_Display_Empty_Slots() ;
		}

		// =====================	Wrong ID	=====================

		if(Search_Done == 0 && (RFID_CARD_Enter > 0 || RFID_CARD_EXIT > 0))
		{
			lcd_clear(&LCD2) ;
			lcd_set_position(&LCD2, 0, 0) ;
			lcd_send_string(&LCD2,"Wrong ID!") ;
			lcd_set_position(&LCD2, 2, 3) ;
			lcd_send_string(&LCD2,"Try Again") ;

			for(i=0;i<3;i++)
			{
				MCAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0) ;
				dms(150) ;
			}
			MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1); //to ensure Red Led off after toggle


			//	Dash Board LCD
			LCD_Welcome() ;
			dms(150) ;
			LCD_Display_Empty_Slots() ;

			// Reset
			RFID_CARD_EXIT = 0 ;
			RFID_CARD_Enter = 0 ;

		}
	}
	return 0 ;


}

void LCD_Welcome(void)
{

	lcd_clear(&LCD2) ;
	lcd_set_position(&LCD2, 1, 1) ;
	lcd_send_string(&LCD2,"Welcome in") ;
	lcd_set_position(&LCD2,2,0 );
	lcd_send_string(&LCD2,"Menna Parking") ;
}

void LCD_Display_Empty_Slots(void)
{
	lcd_clear(&LCD2) ;
	lcd_set_position(&LCD2, 0, 0) ;
	lcd_send_string(&LCD2,"Empty Slots=") ;
	lcd_set_position(&LCD2, 0, 14) ;
	lcd_send_char(&LCD2,Available_Slots) ;
}

void LEDs_Init(void)
{
	//RED LED A0
	GPIO_PinConfig_t PinCinfg ;
	PinCinfg.GPIO_PinNumber=GPIO_PIN_0 ;
	PinCinfg.GPIO_MODE = GPIO_MODE_Output_push_pull ;
	PinCinfg.GPIO_Output_Speed=GPIO_Output_Speed_10M ;
	MCAL_GPIO_Init(GPIOA, &PinCinfg) ;

	//GREEN LED A11
	PinCinfg.GPIO_PinNumber=GPIO_PIN_11 ;
	PinCinfg.GPIO_MODE = GPIO_MODE_Output_push_pull ;
	PinCinfg.GPIO_Output_Speed =GPIO_Output_Speed_10M ;
	MCAL_GPIO_Init(GPIOA, &PinCinfg) ;
}

void PIRs_Iint(void) // Sensor
{
	//PIR1 A7
	GPIO_PinConfig_t PinCinfg ;
	PinCinfg.GPIO_PinNumber=GPIO_PIN_7 ;
	PinCinfg.GPIO_MODE = GPIO_MODE_Input_pull_up ;
	MCAL_GPIO_Init(GPIOA, &PinCinfg) ;

	//PIR2 A1
	PinCinfg.GPIO_PinNumber=GPIO_PIN_1 ;
	PinCinfg.GPIO_MODE = GPIO_MODE_Input_pull_up ;
	MCAL_GPIO_Init(GPIOA, &PinCinfg) ;

	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1) ;
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1) ;

}

void Store_IDs_From_Admin(void)      // Private FUN
{
	lcd_send_command(&LCD1, display_on_cursor_off);
	lcd_set_position(&LCD1, 0, 0);
	lcd_send_string(&LCD1,"IDs of system");
	lcd_set_position(&LCD1, 2, 0);
	lcd_send_string(&LCD1,"First  ID:");
	while(keypad_Read()=='N');
	Pass[0]=keypad_Read();
	while(keypad_Read()!='N');
	lcd_set_position(&LCD1,14,1 );
	lcd_send_char(&LCD1, Pass[0]);
	lcd_send_command(&LCD1, display_on_cursor_off);

	lcd_set_position(&LCD1, 3, 0);
	lcd_send_string(&LCD1,"Second ID:");
	while(keypad_Read()=='N');
	Pass[1]=keypad_Read();
	while(keypad_Read()!='N');
	lcd_set_position(&LCD1, 10,2);
	lcd_send_char(&LCD1, Pass[1]);
	lcd_send_command(&LCD1, display_on_cursor_off);

	lcd_set_position(&LCD1, 4, 0);
	lcd_send_string(&LCD1,"Third  ID:");
	while(keypad_Read()=='N');
	Pass[2]=keypad_Read();
	while(keypad_Read()!='N');
	lcd_set_position(&LCD1, 10,3 );
	lcd_send_char(&LCD1, Pass[2]);
	lcd_send_command(&LCD1, display_on_cursor_off);


	lcd_clear(&LCD1);
	lcd_set_position(&LCD1, 0, 0);
	lcd_send_string(&LCD1,"IDs are Stored");
	lcd_send_command(&LCD1, display_on_cursor_off);

	lcd_set_position(&LCD1, 2, 4);
	lcd_send_char(&LCD1, Pass[0]);
	lcd_set_position(&LCD1, 2, 8);
	lcd_send_char(&LCD1, Pass[1]);
	lcd_set_position(&LCD1, 2, 12);
	lcd_send_char(&LCD1, Pass[2]);
}

