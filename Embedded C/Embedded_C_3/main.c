/*
 ******************************************************************************
 * @file           : main.c
 * @author         : Menna_Gabely
 * @brief          : Main program body
 ******************************************************************************
*/

#include "stdint.h"
typedef volatile unsigned int vuint32_t ;
//REGISTERS ADRESSESS

#define RCC_BASE  	    0x40021000
#define GPIOA_BASE		0x40010800
#define RCC_APB2ENR		*(volatile uint32_t *)(RCC_BASE + 0x18)
#define GPIOA_CRH		*(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR		*(volatile uint32_t *)(GPIOA_BASE + 0x0c)

//BIT FIELDS
#define RCC_IOPAEN  	(1<<2)
#define GPIOA13 		(1UL<<13)

typedef union {
	vuint32_t			all_fields;
	struct{
		vuint32_t		reserved:13 ;
		vuint32_t		p_13:1 ;
	} Pin;
}R_ODR_T;

volatile R_ODR_T* R_ODR = (volatile R_ODR_T*)(GPIOA_BASE + 0x0c);
unsigned char g_var[3] = {1,2,3};
unsigned char const g_var_two[3] = {1,2,3};

int main(void)
{
	int i =0;
	RCC_APB2ENR |= RCC_IOPAEN ;
	GPIOA_CRH   &= 0xFF0FFFFF ;
	GPIOA_CRH   |= 0x00200000 ;
	while(1){
		R_ODR->Pin.p_13 = 1;
		for(i =0 ;i<50000; i++); //delay
		R_ODR->Pin.p_13 = 0;
		for(i =0 ;i<50000; i++); //delay
	}
	return 0;
}
