/*
 * Interrupt Controller On Atmega32.c
 *
 * Created: 12/8/2023 1:38:30 AM
 * Author : Menna
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#define Set_bit(Address , Bit) Address |= (1<<Bit)
#define Reset_bit(Address , Bit) Address &= ~(1<<Bit)
#define Toggle_bit(Address , Bit) Address ^= (1<<Bit)
#define Read_bit(Address , Bit) ((Address & (1<<Bit))>>Bit)

#define BASE 0x20
// External Interrupt Request
//MCU Control Register –MCUCR
#define MCUCR *((volatile uint32_t *)(BASE + 0x35))
//MCU Control and Status Register – MCUCSR
#define MCUCSR *((volatile uint32_t *)(BASE + 0x34))
//General Interrupt ControlRegister – GICR
#define GICR *((volatile uint32_t *)(BASE + 0x3B))
//General Interrupt Flag Register – GIFR
#define GIFR *((volatile uint32_t *)(BASE + 0x3A))
//The AVR Status Register – SREG
#define SREG *((volatile uint32_t *)(BASE + 0x3F))

// Enable GPIO
#define PORTA *(volatile uint32_t *)(BASE + 0x1B)
#define DDRA *(volatile uint32_t *)(BASE + 0x1A)
#define PORTB *(volatile uint32_t *)(BASE + 0x18)
#define DDRB *(volatile uint32_t *)(BASE + 0x17)
#define PORTD *(volatile uint32_t *)(BASE + 0x12)
#define DDRD *(volatile uint32_t *)(BASE + 0x11)
 

int main(void)
{
	// pin (5,6,7) output in PortD pin =0
	Set_bit(DDRD,5) ;
	Set_bit(DDRD,6) ;
	Set_bit(DDRD,7) ;
	// sit INT0 logical
	Set_bit(MCUCR,0) ;
	Reset_bit(MCUCR,1) ;
	// sit INT1 Rising edge
	Set_bit(MCUCR,2) ;
	Set_bit(MCUCR,3) ;
	// sit INT2 Falling edge
	Reset_bit(MCUCSR,6) ;
	//Enable all INT0 ,INT1 , TNT2
	Set_bit(GICR,5) ;
	Set_bit(GICR,6) ;
	Set_bit(GICR,7) ;
	//Enable global interrupt
	sei();

    while (1) 
    {
		Reset_bit(PORTD,5) ;
		Reset_bit(PORTD,6) ;
		Reset_bit(PORTD,7) ;
    }
	return 0;
}
// ISR INT0,1,2
ISR(INT0_vect)
{
	Set_bit(PORTD,5) ;
	_delay_ms(1000) ;
}
ISR(INT1_vect)
{
	Set_bit(PORTD,6) ;
	_delay_ms(1000);
}
ISR(INT2_vect)
{
	Set_bit(PORTD,7) ;
	_delay_ms(1000);
}

