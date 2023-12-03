/*
 ******************************************************************************
 * @file           : main.c
 * @author         : Menna_Gabely
 * @brief          : Main program body
 ******************************************************************************
 */

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

//RCC
#define RCC_BASE  	    0x40021000
#define RCC_APB2ENR		*(volatile uint32_t *)(RCC_BASE + 0x18)
#define RCC_IOPAEN  	(1<<2)      //BIT FIELDS

// EXTI0 Interrupt
#define EXTI_BASE  	    0x40010400
#define EXTI_IMR		*(volatile uint32_t *)(EXTI_BASE + 0x00)  //mask
#define EXTI_RTSR		*(volatile uint32_t *)(EXTI_BASE + 0x08) // EXTI_RTSR
#define EXTI_PR		*(volatile uint32_t *)(EXTI_BASE + 0x14)    // pending

//Enable bit AFIOEN : alternative function I/O clock
#define NVIC_EXTIE0		*(volatile uint32_t *)(0xE000E100)

//AFIO
#define AFIO_BASE  	    0x40010000
#define AFIO_EXTICR1	*(volatile uint32_t *)(AFIO_BASE + 0x08)

//GPIO REGISTERS ADRESSESS
#define GPIOA_BASE		0x40010800
#define GPIOA_CRH		*(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR		*(volatile uint32_t *)(GPIOA_BASE + 0x0c)
#define GPIOA_CRL		*(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA13 		(1UL<<13) //BIT FIELDS

void clock_init(){
	// enable clock GPIO
	RCC_APB2ENR |= RCC_IOPAEN ;
	RCC_APB2ENR |= (1<<0) ;
}

void GPIO_init(){
	// pin 13 port A output
	GPIOA_CRH   &= 0xFF0FFFFF ;
	GPIOA_CRH   |= 0x00200000 ;
	//Pin A 0 input : 01: floating input (reset state)
	GPIOA_CRL |= (1<<2) ;
}

void EXTI0_IRQHandler(void){
	//interrupt is happened EXTI0 >>> PORTA Pin 0 - rising  edge
	// toggle led PIN A 13
	GPIOA_ODR ^= (1<<13) ;
	//Enable EXTI_PR Pending
	EXTI_PR	|= (1<<0) ; // to clear pending request

}

int main(void)
{
	clock_init() ;
	GPIO_init() ;

	//Enable EXTI0 TO AFIO_BASE port A
	AFIO_EXTICR1 = 0 ;

	//Enable EXTI_RTSR trigger
	EXTI_RTSR |= (1<<0) ;

	//Enable EXTI0 MASK1
	EXTI_IMR |= (1<<0) ;

	//Enable bit 6 AFIOEN : alternative function I/O clock
	NVIC_EXTIE0 |= (1<<6) ;

	while(1) ;

}


