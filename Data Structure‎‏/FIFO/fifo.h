#ifndef FIFO_H_INCLUDED
#define FIFO_H_INCLUDED

#include "stdio.h"
#include "stdint.h"

//User configuration
//Select element type (unit8_t , unit32_t  ,... )
#define element_type uint8_t
//Create Buffer
#define width1 5
element_type uart_buffer[width1];

// FIFO Data Types

typedef struct{
    unsigned int length ;
    unsigned int count ;
    element_type* base ;
    element_type* head ;
    element_type* tail ;

}FIFO_Buf_t ;

typedef enum {
    FIFO_no_error,
    FIFO_full,
    FIFO_empty,
    FIFO_Null

}FIFO_Buf_status ;


//APIs
FIFO_Buf_status FIFO_init (FIFO_Buf_t* fifo , element_type* buf , uint32_t length) ;
FIFO_Buf_status FIFO_enqueue (FIFO_Buf_t* fifo , element_type item) ;
FIFO_Buf_status FIFO_dequeue (FIFO_Buf_t* fifo , element_type* item) ;
FIFO_Buf_status FIFO_is_full (FIFO_Buf_t* fifo) ;
void FIFO_print (FIFO_Buf_t* fifo) ;


#endif // FIFO_H_INCLUDED
