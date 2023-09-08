#include "UART.h"

unsigned char string_buffer[100] = "learn-in-depth : MENNA_GABELY" ;
unsigned char const string_buffer_2[100] = "Creat rodata section" ;

void main(void){
	Uart_send_string(string_buffer);
}