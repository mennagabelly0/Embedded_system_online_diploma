#include "UART.h"
                                //UART REGISTER
#define UATR0DR *((volatile unsigned int* const)((unsigned int*)0x101f1000))

void Uart_send_string(unsigned char* p_tx_strind){
	while(*p_tx_strind != '\0'){                   //LOOP UNTIL END OF STRING
		UATR0DR = (unsigned int)(*p_tx_strind);   //TRANSMIT CHAR
		p_tx_strind++;                           //NEW CHAR
	}
}
