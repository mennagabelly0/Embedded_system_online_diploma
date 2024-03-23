/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: Mar 21, 2024
 *      Author: HFCS
 */

#ifndef INCLUDES_I2C_SLAVE_EEPROM_H_
#define INCLUDES_I2C_SLAVE_EEPROM_H_

//-----------------------------
//Includes
//-----------------------------
#include "I2C_DRIVER_STM32F103C6.h"

// E2PROM is an I2C Slave .
// Idle Mode : Device is in impedance state and waits for Data .
// Master Transmitter Mode : The Device transmit Data to Slave Receiver .
// Master Receiver Mode : The device date from a Slave Transmitter .

#define EEPROM_SLAVE_ADDRESS          				0X2A

void EEPROM_Init(void) ;
unsigned char EEPROM_Write_NBytes(unsigned int Memory_Address , unsigned char *Bytes , uint8_t Data_Lenght) ;
uint8_t EEPROM_Read_Byte(unsigned int Memory_Address , uint8_t* DataOut , uint8_t Data_Lenght) ;



#endif /* INCLUDES_I2C_SLAVE_EEPROM_H_ */
