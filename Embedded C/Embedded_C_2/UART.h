#ifndef _UART_H_
#define _UART_H_

#define UATR0DR *((volatile unsigned int* const)((unsigned int*)0x101f1000))
void Uart_send_string (unsigned char* p_tx_strind);


#endif