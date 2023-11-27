/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Eng Menna Gabely by STM32CubeIDE
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

/*#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
*/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
typedef volatile unsigned int Vuint32_t ;

// register address
#define GPIOA_BASE 0x40010800
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0X0C)

//Enable RCC
#define RCC_BASE 0x40021000
//#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0X18)
#define RCC_CFGR *(volatile uint32_t *)(RCC_BASE + 0X04)
void clock_init(){

	/*	APB low-speed prescaler (APB1)
	Set and cleared by software to control the division factor of the APB low-speed clock
	(PCLK1).
	Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
	0xx: HCLK not divided
	100: HCLK divided by 2
	101: HCLK divided by 4
	110: HCLK divided by 8
	111: HCLK divided by 16 */

	RCC_CFGR |= (0b100 << 8) ;

	/* APB high-speed prescaler (APB2)
	Set and cleared by software to control the division factor of the APB high-speed clock
	(PCLK2).
	0xx: HCLK not divided
	100: HCLK divided by 2
	101: HCLK divided by 4
	110: HCLK divided by 8
	111: HCLK divided by 16 */

	RCC_CFGR |= (0b101 << 11) ;


}


int main(void)
{
	clock_init() ;
	// Enable IO port A clock
	//RCC_APB2ENR |= 1<<2 ;
    //Init GPIO
	GPIOA_CRH &= 0xFF0FFFFF ;
	GPIOA_CRH |= 0x00200000 ;
	while(1){
		GPIOA_ODR |= 1<<13 ;
			for(int i = 0 ; i<5000 ;i++) ; //DELAY
			GPIOA_ODR &= ~(1<<13) ;
			for(int i = 0 ; i<5000 ;i++) ; //DELAY

	}
}
