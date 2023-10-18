/*
        FIFO
        Created by Eng : Menna_Gabely

*/
#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"

void main()
{
    element_type i , temp ;
    FIFO_Buf_t FIFO_UART ;

    if(FIFO_init( &FIFO_UART , uart_buffer , 5 ) == FIFO_no_error)
        printf("FIFO Init --------Done\n");

    for(i =0 ; i<7 ;i++){
        printf("FIFO Enqueue (%x)\n" , i);
        if(FIFO_enqueue(&FIFO_UART , i) == FIFO_no_error)
            printf("\tFIFO Enqueue --------Done\n");
        else
            printf("\tFIFO Enqueue --------Failed\n");
    }

    FIFO_print(&FIFO_UART);
    for(i=0 ; i<7 ; i++){
            printf("FIFO Dequeue (%d) \n",i);
    if(FIFO_dequeue(&FIFO_UART , &temp) == FIFO_no_error)
            printf("\tFIFO Dequeue --------Done\n" , temp);
     else
            printf("\tFIFO Dequeue --------Failed\n");
    }

    FIFO_print(&FIFO_UART);

}
