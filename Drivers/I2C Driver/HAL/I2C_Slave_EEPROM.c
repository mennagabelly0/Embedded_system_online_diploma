/*
 * I2C_Slave_EEPROM.c
 *
 *  Created on: Mar 21, 2024
 *      Author: HFCS
 */

//-----------------------------
//Includes
//-----------------------------

#include "I2C_Slave_EEPROM.h"

/**================================================================
 * @Fn					-	EEPROM_Init
 * @brief 				-	EEPROM Initialization IN I2C Slave
 * @param[in] 			-	NONE
 * @param[in] 			-	NONE
 * @retval				-	NONE
 * Note					-	NONE
 *						-
 */
void EEPROM_Init(void)
{
	/*================ I2C Init ====================*/
	//PB6 : I2C1_SCL
	//PB7 : I2C1_I2C1_SDA
	I2C_PinConfig_t I2C1CFG ;

	//I2C controller act as Master
	I2C1CFG.I2C_Call_Address_Detection = I2C_Call_Address_Detection_ENGC_Enable ;
	I2C1CFG.I2C_ACK_Control = I2C_ACK_Control_Enable ;
	I2C1CFG.I2C_ClockSpeed = I2C_SCLK_SM_100K ;
	I2C1CFG.I2C_Mode = I2C_Mode_I2C ;
	I2C1CFG.P_Slave_Event_CallBack = NULL ;
	I2C1CFG.I2C_STRETCH_Mode = I2C_STRETCH_Mode_Enable ;

	MCAL_I2C_GPIO_Set_Pins(I2C1) ;
	MCAL_I2C_Init(I2C1, &I2C1CFG) ;

}

/**================================================================
 * @Fn					-	EEPROM_Write_NBytes
 * @brief 				-	EEPROM Write NBytes IN I2C Slave
 * @param[out] 			-	Memory_Address
 * @param[out] 			-	Bytes
 * @param[out] 			-	Data_Lenght
 * @retval				-	NONE
 * Note					-	NONE
 *						-
 */
unsigned char EEPROM_Write_NBytes(unsigned int Memory_Address , unsigned char *Bytes , uint8_t Data_Lenght)
{
	uint8_t i = 0 ;
	uint8_t buffer[256] ;
	buffer[0] = (uint8_t)(Memory_Address>>8) ; //Upper byte Memory Address
	buffer[1] = (uint8_t)(Memory_Address) ;    //Lower byte Memory Address

	for(i=2 ; i<(Data_Lenght+2) ; i++)
	{
		buffer[i] = Bytes[i-2] ;
	}

	MCAL_I2C_Master_Send_Data_TX( I2C1, EEPROM_SLAVE_ADDRESS , buffer , (Data_Lenght+2), With_Stop, Start) ;
	return 0 ;

}

/**================================================================
 * @Fn					-	EEPROM_Read_Byte
 * @brief 				-	EEPROM Read Byte IN I2C Slave
 * @param[out] 			-	Memory_Address
 * @param[out] 			-	DataOut
 * @param[out] 			-	Data_Lenght
 * @retval				-	NONE
 * Note					-	NONE
 *						-
 */
uint8_t EEPROM_Read_Byte(unsigned int Memory_Address , uint8_t* DataOut , uint8_t Data_Lenght){
	uint8_t  buffer[2] ;
	buffer[0] = (uint8_t)(Memory_Address>>8) ; //upper byte memory address
	buffer[1] = (uint8_t)(Memory_Address) ;    //lower byte memory address

	MCAL_I2C_Master_Send_Data_TX(I2C1, EEPROM_SLAVE_ADDRESS , &buffer , 2, Without_Stop, Start ) ;  //write address only
	MCAL_I2C_Master_Receive_Data_RX(I2C1, EEPROM_SLAVE_ADDRESS , DataOut , Data_Lenght, With_Stop, RepeatedStart) ;   //Read

	return 0;

}


