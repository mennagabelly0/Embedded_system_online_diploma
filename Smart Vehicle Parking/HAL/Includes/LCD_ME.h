/*
 * LCD_ME.c
 *
 *  Created on: Mar 28, 2024
 *      Author: ENG.Menna Gabely.
 */

#ifndef INCLUDES_LCD_ME_C_
#define INCLUDES_LCD_ME_C_

//-----------------------------
//Includes
//-----------------------------

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
#include "lcd.h"
#include "keypad.h"

//LCD modes
//#define EIGHT_BIT_MODE
#define FOUR_BIT_MODE

typedef struct
{
	GPIO_Typedef * lcd_data_dir;
	GPIO_Typedef * lcd_data_port;
	GPIO_Typedef * lcd_ctrl_dir;
	GPIO_Typedef * lcd_ctrl_port;
	uint16_t		RS;
	uint16_t		EN;
}LCD_Pins_Config_t;


extern LCD_Pins_Config_t LCD1;
extern LCD_Pins_Config_t LCD2;



//LCD commands
#define clear_display					0x01
#define cursor_first_line				0x80
#define cursor_second_line				0xc0
#define cursor_line1_pos3				0x83
#define activate_second_line			0x3c
#define second_line_pos1				0xc1
#define function_set_8bit				0x38
#define function_set_4bit				0x28
#define Entry_mode						0x06
#define display_off_cursor_off			0x08
#define display_on_cursor_on			0x0e
#define display_on_cursor_off			0x0c
#define Display_on_Cursor_blinking		0x0f
#define shift_display_left				0x18
#define shift_display_right				0x1c
#define move_cursor_left_one_char		0x10
#define move_cursor_right_one_char		0x14
#define cursor_third_line				0x90
#define cursor_fourth_line				0xD0


//APIS
void lcd_init(LCD_Pins_Config_t * Lcd_No);
void lcd_is_busy(LCD_Pins_Config_t * Lcd_No);
void lcd_send_command(LCD_Pins_Config_t * Lcd_No,unsigned char command);
void lcd_send_char(LCD_Pins_Config_t * Lcd_No,unsigned char data);
void lcd_send_string(LCD_Pins_Config_t * Lcd_No,char *str);
void lcd_set_position(LCD_Pins_Config_t * Lcd_No,int line, int position);
void lcd_clear(LCD_Pins_Config_t * Lcd_No);

#endif /* INCLUDES_LCD_ME_C_ */
