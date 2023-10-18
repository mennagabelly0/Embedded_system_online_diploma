/*
        LIFO
        Created by Eng : Menna_Gabely

*/

#include <stdio.h>
#include <stdlib.h>
#include "Lifo.h"

unsigned int buffer1 [5]; // 5*4=20 byte in data memory
void main()
{
    int i , temp =0 ;
    //STATIC ALLOCATION
    LIFO_Buf_t uart_lifo  ,I2C_lifo ;
    LIFO_init(&uart_lifo ,buffer1 , 5 );

    //DYNAMIC ALLOCATION
    unsigned int* buffer2 = (unsigned int*) malloc(5 * sizeof(unsigned int));  // 5*4=20 byte in heap
    LIFO_init(&I2C_lifo , buffer2 , 5 );
    //STATIC ALLOCATION CHEACK
    for(i = 0 ; i<5 ;i++ ){
        if(LIFO_Add_item(&uart_lifo , i) == LIFO_no_error)
            printf("UART_LIFO_ADD : %d \n" ,i);
    }
    printf("\n");
    //DYNAMIC ALLOCATION CHEACK
    for(i = 0 ; i<5 ;i++ ){
        if(LIFO_get_item(&uart_lifo , &temp) == LIFO_no_error)
            printf("UART_LIFO_GET : %d \n" ,temp);
    }
    free(buffer2);
}
