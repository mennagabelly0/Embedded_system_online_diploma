/*
 * LCD_ME.c
 *
 *  Created on: Mar 28, 2024
 *      Author: ENG.Menna Gabely.
 */

#include "LCD_ME.h"

GPIO_PinConfig_t pin_cfg;
uint16_t LCD_data_pins[] = {GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,
							GPIO_PIN_12,GPIO_PIN_13,GPIO_PIN_14,GPIO_PIN_15};

void delay_ms(uint32_t time)
{
	uint32_t i,j;
	for(i=0; i<time; i++)
		for(j=0; j<255; j++);
}

void lcd_init(LCD_Pins_Config_t * Lcd_No)
{
	//delay_ms(20);
	dms(10);
	//LCD data set as output
	int i;
	if(Lcd_No == &LCD1)
	{
		for(i=4; i<8; i++)
		{
			pin_cfg.GPIO_PinNumber= LCD_data_pins[i];
			pin_cfg.GPIO_MODE = GPIO_MODE_Output_push_pull;
			pin_cfg.GPIO_Output_Speed = GPIO_Output_Speed_10M;
			MCAL_GPIO_Init(LCD1.lcd_data_dir, &pin_cfg);
		}

		//set RS SWITCH as output
		pin_cfg.GPIO_PinNumber = LCD1.RS;
		pin_cfg.GPIO_MODE = GPIO_MODE_Output_push_pull;
		pin_cfg.GPIO_Output_Speed = GPIO_Output_Speed_10M;
		MCAL_GPIO_Init(LCD1.lcd_ctrl_dir, &pin_cfg);
		//set ENABLE SWITCH as output
		pin_cfg.GPIO_PinNumber = LCD1.EN;
		pin_cfg.GPIO_MODE = GPIO_MODE_Output_push_pull;
		pin_cfg.GPIO_Output_Speed = GPIO_Output_Speed_10M;
		MCAL_GPIO_Init(LCD1.lcd_ctrl_dir, &pin_cfg);
		//clear RS,RW,EN
		MCAL_GPIO_WritePin(LCD1.lcd_ctrl_port, LCD1.RS, GPIO_PIN_Reset);
		MCAL_GPIO_WritePin(LCD1.lcd_ctrl_port, LCD1.EN, GPIO_PIN_Reset);

		lcd_send_command(&LCD1,0x30);
		delay_ms(10);
		lcd_send_command(&LCD1,0x30);
		delay_ms(1);
		lcd_send_command(&LCD1,0x30);
	}
	else if(Lcd_No == &LCD2)
	{
		for(i=4; i<8; i++)
		{
			pin_cfg.GPIO_PinNumber= LCD_data_pins[i];
			pin_cfg.GPIO_MODE = GPIO_MODE_Output_push_pull;
			pin_cfg.GPIO_Output_Speed = GPIO_Output_Speed_10M;
			MCAL_GPIO_Init(LCD2.lcd_data_dir, &pin_cfg);
		}

		//set RS SWITCH as output
		pin_cfg.GPIO_PinNumber = LCD2.RS;
		pin_cfg.GPIO_MODE = GPIO_MODE_Output_push_pull;
		pin_cfg.GPIO_Output_Speed = GPIO_Output_Speed_10M;
		MCAL_GPIO_Init(LCD2.lcd_ctrl_dir, &pin_cfg);
		//set ENABLE SWITCH as output
		pin_cfg.GPIO_PinNumber = LCD2.EN;
		pin_cfg.GPIO_MODE = GPIO_MODE_Output_push_pull;
		pin_cfg.GPIO_Output_Speed = GPIO_Output_Speed_10M;
		MCAL_GPIO_Init(LCD2.lcd_ctrl_dir, &pin_cfg);
		//clear RS,RW,EN
		MCAL_GPIO_WritePin(LCD2.lcd_ctrl_port, LCD2.RS, GPIO_PIN_Reset);
		MCAL_GPIO_WritePin(LCD2.lcd_ctrl_port, LCD2.EN, GPIO_PIN_Reset);

		lcd_send_command(&LCD2,0x30);
		delay_ms(10);
		lcd_send_command(&LCD2,0x30);
		delay_ms(1);
		lcd_send_command(&LCD2,0x30);
	}


#ifdef EIGHT_BIT_MODE
//select 8-bit mode
	lcd_write_command(function_set_8bit);
#endif

#ifdef FOUR_BIT_MODE
	//select 4-bit mode
	if(Lcd_No == &LCD1)
	{
		lcd_send_command(&LCD1,0x02);
		lcd_send_command(&LCD1,function_set_4bit);
		lcd_send_command(&LCD1,0x08);
	}
	else if(Lcd_No == &LCD2)
	{
		lcd_send_command(&LCD2,0x02);
		lcd_send_command(&LCD2,function_set_4bit);
		lcd_send_command(&LCD2,0x08);
	}

#endif
	if(Lcd_No == &LCD1)
	{
		//display off
		lcd_send_command(&LCD1,display_off_cursor_off);
		//clear display
		lcd_clear(&LCD1);
		//entry mode set
		lcd_send_command(&LCD1,Entry_mode);
		//display on cursor blinking
		lcd_send_command(&LCD1,Display_on_Cursor_blinking);
	}
	else if(Lcd_No == &LCD2)
	{
		//display off
		lcd_send_command(&LCD2,display_off_cursor_off);
		//clear display
		lcd_clear(&LCD2);
		//entry mode set
		lcd_send_command(&LCD2,Entry_mode);
		//display on cursor blinking
		lcd_send_command(&LCD2,Display_on_Cursor_blinking);
	}

}


void lcd_kick(LCD_Pins_Config_t * Lcd_No)
{
	if(Lcd_No == &LCD1)
	{
		MCAL_GPIO_WritePin(LCD1.lcd_ctrl_port, LCD1.EN, GPIO_PIN_Set);
		//delay_ms(3);
		dms(2);
		MCAL_GPIO_WritePin(LCD1.lcd_ctrl_port, LCD1.EN, GPIO_PIN_Reset);
	}
	else if(Lcd_No == &LCD2)
	{
		MCAL_GPIO_WritePin(LCD2.lcd_ctrl_port, LCD2.EN, GPIO_PIN_Set);
		//delay_ms(3);
		dms(2);
		MCAL_GPIO_WritePin(LCD2.lcd_ctrl_port, LCD2.EN, GPIO_PIN_Reset);
	}

}

void lcd_send_char(LCD_Pins_Config_t * Lcd_No,unsigned char data)
{
#ifdef EIGHT_BIT_MODE
	lcd_is_busy();
	//make LCD in write mode
	MCAL_GPIO_WritePin(lcd_ctrl_port, RS, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(lcd_ctrl_port, RW, GPIO_PIN_RESET);
	//write data
	MCAL_GPIO_WritePort(lcd_data_port, data);
	lcd_kick();
#endif

#ifdef FOUR_BIT_MODE
	//lcd_is_busy();
	//delay_ms(3);
	dms(2);
	if(Lcd_No == &LCD1)
	{
		//send last four bits of data
		MCAL_GPIO_WritePin(LCD1.lcd_ctrl_port, LCD1.RS, GPIO_PIN_Set);
		unsigned char tmp_data = (data & 0xF0);
		int i;
		for(i=4; i<8; i++)
		{
			MCAL_GPIO_WritePin(LCD1.lcd_data_port, LCD_data_pins[i], ((tmp_data & (1<<i))>>i));
		}
		//MCAL_GPIO_WritePort(lcd_data_port, tmp_data);
		lcd_kick(&LCD1);
		//send first four bits of data
		MCAL_GPIO_WritePin(LCD1.lcd_ctrl_port, LCD1.RS, GPIO_PIN_Set);
		tmp_data = (data << 4);
		for(i=4; i<8; i++)
		{
			MCAL_GPIO_WritePin(LCD1.lcd_data_port, LCD_data_pins[i], ((tmp_data & (1<<i))>>i));
		}
		//MCAL_GPIO_WritePort(lcd_data_port, tmp_data);
		lcd_kick(&LCD1);
	}
	else if(Lcd_No == &LCD2)
	{
		//send last four bits of data
		MCAL_GPIO_WritePin(LCD2.lcd_ctrl_port, LCD2.RS, GPIO_PIN_Set);
		unsigned char tmp_data = (data & 0xF0);
		int i;
		for(i=4; i<8; i++)
		{
			MCAL_GPIO_WritePin(LCD2.lcd_data_port, LCD_data_pins[i], ((tmp_data & (1<<i))>>i));
		}
		//MCAL_GPIO_WritePort(lcd_data_port, tmp_data);
		lcd_kick(&LCD2);
		//send first four bits of data
		MCAL_GPIO_WritePin(LCD2.lcd_ctrl_port, LCD2.RS, GPIO_PIN_Set);
		tmp_data = (data << 4);
		for(i=4; i<8; i++)
		{
			MCAL_GPIO_WritePin(LCD2.lcd_data_port, LCD_data_pins[i], ((tmp_data & (1<<i))>>i));
		}
		//MCAL_GPIO_WritePort(lcd_data_port, tmp_data);
		lcd_kick(&LCD2);
	}

#endif
}

void lcd_send_string(LCD_Pins_Config_t * Lcd_No,char *str)
{
	int character_counter1 = 0;
	int character_counter2 = 0;

	while(*str != '\0')
	{
		if(Lcd_No == &LCD1)
		{
			character_counter1++;
			if(character_counter1 == 17)
			{
				//go to second line position 0
				lcd_set_position(&LCD1,2,0);
			}
			else if(character_counter1 > 32)
			{
				//clear display
				lcd_send_command(&LCD1,clear_display);
				//go to first line position 0
				lcd_set_position(&LCD1,1,0);
				character_counter1 = 0;
			}
			lcd_send_char(&LCD1,*str);
		}
		else if(Lcd_No == &LCD2)
		{
			character_counter2++;
			if(character_counter2 == 17)
			{
				//go to second line position 0
				lcd_set_position(&LCD2,2,0);
			}
			else if(character_counter2 > 32)
			{
				//clear display
				lcd_send_command(&LCD2,clear_display);
				//go to first line position 0
				lcd_set_position(&LCD2,1,0);
				character_counter2 = 0;
			}
			lcd_send_char(&LCD2,*str);
		}
		str++;
	}
}

void lcd_is_busy(LCD_Pins_Config_t * Lcd_No)
{
	//make data lines as input
	int i;
	if(Lcd_No == &LCD1)
	{
		for(i=4; i<8; i++)
		{
			pin_cfg.GPIO_PinNumber= LCD_data_pins[i];
			pin_cfg.GPIO_MODE = GPIO_MODE_Input_Floating;
			MCAL_GPIO_Init(LCD1.lcd_data_dir, &pin_cfg);
		}
		//make LCD in read mode RS = 0, RW = 1
		MCAL_GPIO_WritePin(LCD1.lcd_ctrl_port, LCD1.RS, GPIO_PIN_Reset);
		lcd_kick(&LCD1);
		//make data lines as output
		for(i=4; i<8; i++)
		{
			pin_cfg.GPIO_PinNumber= LCD_data_pins[i];
			pin_cfg.GPIO_MODE = GPIO_MODE_Output_push_pull;
			pin_cfg.GPIO_Output_Speed = GPIO_Output_Speed_10M;
			MCAL_GPIO_Init(LCD1.lcd_data_dir, &pin_cfg);
		}
	}
	else if(Lcd_No == &LCD2)
	{
		for(i=4; i<8; i++)
		{
			pin_cfg.GPIO_PinNumber= LCD_data_pins[i];
			pin_cfg.GPIO_MODE = GPIO_MODE_Input_Floating;
			MCAL_GPIO_Init(LCD2.lcd_data_dir, &pin_cfg);
		}
		//make LCD in read mode RS = 0, RW = 1
		MCAL_GPIO_WritePin(LCD2.lcd_ctrl_port, LCD2.RS, GPIO_PIN_Reset);
		lcd_kick(&LCD2);
		//make data lines as output
		for(i=4; i<8; i++)
		{
			pin_cfg.GPIO_PinNumber= LCD_data_pins[i];
			pin_cfg.GPIO_MODE = GPIO_MODE_Output_push_pull;
			pin_cfg.GPIO_Output_Speed = GPIO_Output_Speed_10M;
			MCAL_GPIO_Init(LCD2.lcd_data_dir, &pin_cfg);
		}
	}

}

void lcd_send_command(LCD_Pins_Config_t * Lcd_No,unsigned char command)
{
#ifdef EIGHT_BIT_MODE
	lcd_is_busy();
	//switch to write mode and select instruction reg to send command
	MCAL_GPIO_WritePin(lcd_ctrl_port, RS, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(lcd_ctrl_port, RW, GPIO_PIN_RESET);
	MCAL_GPIO_WritePort(lcd_data_port, command);
	lcd_kick();
#endif

#ifdef FOUR_BIT_MODE
	int i;
	//delay_ms(3);
	dms(2);
	if(Lcd_No == &LCD1)
	{
		//send last four bits of command
		MCAL_GPIO_WritePin(LCD1.lcd_ctrl_port, LCD1.RS, GPIO_PIN_Reset);
		char tmp_cmd;
		tmp_cmd = (command & 0xF0);
		for(i=4; i<8; i++)
		{
			MCAL_GPIO_WritePin(LCD1.lcd_data_port, LCD_data_pins[i], ((tmp_cmd & (1<<i))>>i));
		}
		//MCAL_GPIO_WritePort(lcd_data_port, tmp_cmd);
		lcd_kick(&LCD1);
		//send first four bits of command
		MCAL_GPIO_WritePin(LCD1.lcd_ctrl_port, LCD1.RS, GPIO_PIN_Reset);
		tmp_cmd = (command << 4);
		for(i=4; i<8; i++)
		{
			MCAL_GPIO_WritePin(LCD1.lcd_data_port, LCD_data_pins[i], ((tmp_cmd & (1<<i))>>i));
		}
		//MCAL_GPIO_WritePort(lcd_data_port, tmp_cmd);
		lcd_kick(&LCD1);
	}
	else if(Lcd_No == &LCD2)
	{
		//send last four bits of command
		MCAL_GPIO_WritePin(LCD2.lcd_ctrl_port, LCD2.RS, GPIO_PIN_Reset);
		char tmp_cmd;
		tmp_cmd = (command & 0xF0);
		for(i=4; i<8; i++)
		{
			MCAL_GPIO_WritePin(LCD2.lcd_data_port, LCD_data_pins[i], ((tmp_cmd & (1<<i))>>i));
		}
		//MCAL_GPIO_WritePort(lcd_data_port, tmp_cmd);
		lcd_kick(&LCD2);
		//send first four bits of command
		MCAL_GPIO_WritePin(LCD2.lcd_ctrl_port, LCD2.RS, GPIO_PIN_Reset);
		tmp_cmd = (command << 4);
		for(i=4; i<8; i++)
		{
			MCAL_GPIO_WritePin(LCD2.lcd_data_port, LCD_data_pins[i], ((tmp_cmd & (1<<i))>>i));
		}
		//MCAL_GPIO_WritePort(lcd_data_port, tmp_cmd);
		lcd_kick(&LCD2);
	}

#endif
}


void lcd_set_position(LCD_Pins_Config_t * Lcd_No,int line, int position)
{
	if(Lcd_No == &LCD1)
	{
		if(line == 1)
		{
			if(position >= 0 && position < 16)
			{
				lcd_send_command(&LCD1,cursor_first_line + position);
			}
		}

		else if (line == 2)
		{
			if(position >= 0 && position < 16)
			{
				lcd_send_command(&LCD1,cursor_second_line + position);
			}
		}
		else if (line == 3)
		{
			if(position >= 0 && position < 16)
			{
				lcd_send_command(&LCD1,cursor_third_line + position);
			}
		}
		else if (line == 4)
		{
			if(position >= 0 && position < 16)
			{
				lcd_send_command(&LCD1,cursor_fourth_line + position);
			}
		}
	}
	else if(Lcd_No == &LCD2)
	{
		if(line == 1)
		{
			if(position >= 0 && position < 16)
			{
				lcd_send_command(&LCD2,cursor_first_line + position);
			}
		}

		else if (line == 2)
		{
			if(position >= 0 && position < 16)
			{
				lcd_send_command(&LCD2,cursor_second_line + position);
			}
		}
		else if (line == 3)
		{
			if(position >= 0 && position < 16)
			{
				lcd_send_command(&LCD2,cursor_third_line + position);
			}
		}
		else if (line == 4)
		{
			if(position >= 0 && position < 16)
			{
				lcd_send_command(&LCD2,cursor_fourth_line + position);
			}
		}
	}

}

void lcd_clear(LCD_Pins_Config_t * Lcd_No)
{
	if(Lcd_No == &LCD1)
	{
		lcd_send_command(&LCD1,clear_display);
	}
	else if(Lcd_No == &LCD2)
	{
		lcd_send_command(&LCD2,clear_display);
	}

}
