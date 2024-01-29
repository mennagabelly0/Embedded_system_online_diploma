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

//NVIC Register Mapping
#define NVIC_Base 								0xE000E100UL
#define NVIC_ISER0								*(volatile uint32_t* ) (NVIC_Base + 0x000)
#define NVIC_ISER1								*(volatile uint32_t* ) (NVIC_Base + 0x004)
#define NVIC_ISER2								*(volatile uint32_t* ) (NVIC_Base + 0x008)
#define NVIC_ICER0								*(volatile uint32_t* ) (NVIC_Base + 0x080)
#define NVIC_ICER1								*(volatile uint32_t* ) (NVIC_Base + 0x084)
#define NVIC_ICER2								*(volatile uint32_t* ) (NVIC_Base + 0x088)

//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------

#define RCC_Base  								0x40021000UL


//-----------------------------
//Base addresses for ABP1 Peripherals
//-----------------------------
// USART
#define USART2_Base  							0x40004400UL
#define USART3_Base  							0x40004800UL

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

// USART
#define USART1_Base  							0x40013800UL


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
	volatile uint32_t EXTICR[4] ;
//	volatile uint32_t EXTICR2 ;
//	volatile uint32_t EXTICR3 ;
//	volatile uint32_t EXTICR4 ;
	uint32_t RESERVED0 ; //0X18
	volatile uint32_t MAPR2 ; //0X1C
}AFIO_Typedef;

//-----------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*
//USART register map
typedef struct{
	volatile uint32_t USART_SR ;
	volatile uint32_t USART_DR;
	volatile uint32_t USART_BRR ;
	volatile uint32_t USART_CR1 ;
	volatile uint32_t USART_CR2 ;
	volatile uint32_t USART_CR3 ;
	volatile uint32_t USART_GTPR ;
}USART_Typedef;

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

#define USART1 							((USART_Typedef *)USART1_Base)
#define USART2 							((USART_Typedef *)USART2_Base)
#define USART3 							((USART_Typedef *)USART3_Base)


//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define RCC_GPIOA_CLK_EN() 				(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN() 				(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN() 				(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN() 				(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN() 				(RCC->APB2ENR |= 1<<6)

#define RCC_AFIO_CLK_EN() 				(RCC->APB2ENR |= 1<<0)

// Clock Enable USART
#define RCC_USART1_CLK_EN() 			(RCC->APB2ENR |= 1<<14)
#define RCC_USART2_CLK_EN() 			(RCC->APB1ENR |= 1<<17)
#define RCC_USART3_CLK_EN() 			(RCC->APB1ENR |= 1<<18)

// RCC Reset Mechanism
#define RCC_USART1_Reset() 				(RCC->APB2RSTR |= 1<<14)
#define RCC_USART2_Reset() 				(RCC->APB1RSTR |= 1<<17)
#define RCC_USART3_Reset() 				(RCC->APB1RSTR |= 1<<18)



//-*-*-*-*-*-*-*-*-*-*-*-
//Interrupt Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define EXTI0_IRQ	6
#define EXTI1_IRQ	7
#define EXTI2_IRQ	8
#define EXTI3_IRQ	9
#define EXTI4_IRQ	10
#define EXTI5_IRQ	23
#define EXTI6_IRQ	23
#define EXTI7_IRQ	23
#define EXTI8_IRQ	23
#define EXTI9_IRQ	23
#define EXTI10_IRQ	40
#define EXTI11_IRQ	40
#define EXTI12_IRQ	40
#define EXTI13_IRQ	40
#define EXTI14_IRQ	40
#define EXTI15_IRQ	40

#define USART1_IRQ	37
#define USART2_IRQ	38
#define USART3_IRQ	39


//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC IRQ Enable/Disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define NVIC_IRQ6_EXTI0_Enable 					(NVIC_ISER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_Enable 					(NVIC_ISER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_Enable 					(NVIC_ISER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_Enable 					(NVIC_ISER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_Enable 				(NVIC_ISER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Enable 				(NVIC_ISER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_Enable 			(NVIC_ISER1 |= 1<<8) // 40-32 = 8

#define NVIC_IRQ6_EXTI0_Disable					(NVIC_ICER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_Disable					(NVIC_ICER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_Disable	 				(NVIC_ICER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_Disable	 				(NVIC_ICER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_Disable	 			(NVIC_ICER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Disable	 			(NVIC_ICER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_Disable	 		(NVIC_ICER1 |= 1<<8) // 40-32 = 8

// USART
#define NVIC_IRQ37_USART1_Enable 				(NVIC_ISER1 |= 1<<(USART1_IRQ - 32))   // IRQ - 32
#define NVIC_IRQ38_USART2_Enable 				(NVIC_ISER1 |= 1<<(USART2_IRQ - 32))  // IRQ - 32
#define NVIC_IRQ39_USART3_Enable 				(NVIC_ISER1 |= 1<<(USART3_IRQ - 32)) // IRQ - 32

#define NVIC_IRQ37_USART1_Disable 				(NVIC_ICER1 |= 1<<(USART1_IRQ - 32))   // IRQ - 32
#define NVIC_IRQ38_USART2_Disable 				(NVIC_ICER1 |= 1<<(USART2_IRQ - 32))  // IRQ - 32
#define NVIC_IRQ39_USART3_Disable 				(NVIC_ICER1 |= 1<<(USART3_IRQ - 32)) // IRQ - 32


#endif /* INC_STM32F103X6_H_ */
