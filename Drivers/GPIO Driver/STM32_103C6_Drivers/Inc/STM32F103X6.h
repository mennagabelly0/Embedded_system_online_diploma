/*
 * STM32F103X6.h
 *
 *  Created on: Dec 23, 2023
 *  @author         : 			ENG Menna_Gabely
 *
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//-----------------------------
//Includes
//-----------------------------

#include "stdlib.h"
#include "stdint.h"

//-----------------------------
//Base addresses for Memories
//-----------------------------

#define Flash_Memory_Base						0x08000000UL
#define System_Memory_Base						0x1FFFF000UL
#define SRAM_Base								0x20000000UL

#define Peripherals_Base						0x40000000UL
#define Cortex_M3_Internal_Peripherals_Base		0xE0000000UL

//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------

#define RCC_Base  								0x40021000UL

//-----------------------------
//Base addresses for ABP2 Peripherals
//-----------------------------
//GPIO
//A , B fully included in LQFP48 Package
#define GPIOA_Base								0x40010800UL
#define GPIOB_Base  							0x40010C00UL

//C , D Partial included in LQFP48 Package
#define GPIOC_Base 								0x40011000UL
#define GPIOD_Base 								0x40011400UL

//E NOT included in LQFP48 Package
#define GPIOE_Base 								0x40011800UL

//-----------------------------

//External Interrupt
#define EXTI_Base   							0x40010400UL

//Alternate function
#define AFIO_Base  								0x40010000UL

//-----------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32_t CRL ;
	volatile uint32_t CRH ;
	volatile uint32_t IDR ;
	volatile uint32_t ODR ;
	volatile uint32_t BSRR ;
	volatile uint32_t BRR ;
	volatile uint32_t LCKR ;
}GPIO_Typedef;

//-----------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32_t CR ;
	volatile uint32_t CFGR ;
	volatile uint32_t CIR ;
	volatile uint32_t APB2RSTR ;
	volatile uint32_t APB1RSTR ;
	volatile uint32_t AHBENR ;
	volatile uint32_t APB2ENR ;
	volatile uint32_t APB1ENR ;
	volatile uint32_t BDCR ;
	volatile uint32_t CSR ;
	volatile uint32_t AHBSTR ;
	volatile uint32_t CFGR2 ;

}RCC_Typedef;

//-----------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
//External Interrupt
typedef struct{
	volatile uint32_t IMR ;
	volatile uint32_t EMR ;
	volatile uint32_t RTSR ;
	volatile uint32_t FTSR ;
	volatile uint32_t SWIER ;
	volatile uint32_t PR ;
}EXTI_Typedef;

//-----------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
//Alternate function
typedef struct{
	volatile uint32_t EVCR ;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1 ;
	volatile uint32_t EXTICR2 ;
	volatile uint32_t EXTICR3 ;
	volatile uint32_t EXTICR4 ;
	uint32_t RESERVED0 ; //0X18
	volatile uint32_t MAPR2 ; //0X1C
}AFIO_Typedef;

//-----------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA 							((GPIO_Typedef *)GPIOA_Base)
#define GPIOB 							((GPIO_Typedef *)GPIOB_Base)
#define GPIOC 							((GPIO_Typedef *)GPIOC_Base)
#define GPIOD 							((GPIO_Typedef *)GPIOD_Base)
#define GPIOE 							((GPIO_Typedef *)GPIOE_Base)

#define RCC 							((RCC_Typedef *)RCC_Base)
#define EXTI 							((EXTI_Typedef *)EXTI_Base)
#define AFIO 							((AFIO_Typedef *)AFIO_Base)

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define RCC_GPIOA_CLK_EN() 				(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN() 				(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN() 				(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN() 				(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN() 				(RCC->APB2ENR |= 1<<6)

#define AFIO_CLK_EN() 					(RCC->APB2ENR |= 1<<0)




#endif /* INC_STM32F103X6_H_ */
