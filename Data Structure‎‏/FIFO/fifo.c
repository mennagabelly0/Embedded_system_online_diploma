/*
        FIFO
        Created by Eng : Menna_Gabely

*/
#include "fifo.h"
#include "stdio.h"
#include "stdint.h"

//APIs
FIFO_Buf_status FIFO_init (FIFO_Buf_t* fifo , element_type* buf , uint32_t length)
{
    if (buf ==NULL)
        return FIFO_Null ;

    fifo->base = buf ;
    fifo->head = buf ;
    fifo->tail = buf ;
    fifo->length = length ;
    fifo->count = 0 ;

    return FIFO_no_error ;
}
FIFO_Buf_status FIFO_enqueue(FIFO_Buf_t* fifo , element_type item)
{
    if (!fifo->base || !fifo->head || !fifo->tail )
        return FIFO_Null ;

    // FIFO is full
    if (FIFO_is_full(fifo) == FIFO_full)
        return FIFO_full ;

    *(fifo->head) = item ;
    fifo->count++ ;

    //circler FIFO
    if(fifo->head == (fifo->base + (fifo->length * sizeof(element_type))))
        fifo->head = fifo->base ;
    else
       fifo->head++ ;

    return FIFO_no_error ;
}

FIFO_Buf_status FIFO_dequeue(FIFO_Buf_t* fifo , element_type* item)
{
     if (!fifo->base || !fifo->head || !fifo->tail )
        return FIFO_Null ;
    // check fifo is empty?
    if(fifo->count == 0 )
        return FIFO_empty ;

    *item =*(fifo->tail);
    fifo->count--;

    //circler FIFO
    if(fifo->tail == (fifo->base + (fifo->length * sizeof(element_type))))
        fifo->tail = fifo->base ;
    else
       fifo->tail++ ;

    return FIFO_no_error ;

}

FIFO_Buf_status FIFO_is_full(FIFO_Buf_t* fifo)
{
    if (!fifo->base || !fifo->head || !fifo->tail )
        return FIFO_Null ;

    if (fifo->count == fifo->length)
        return FIFO_full ;

    return FIFO_no_error ;
}

void FIFO_print (FIFO_Buf_t* fifo)
{
    element_type* temp ;
    int i;

    if(fifo->count == 0){
        printf("FIFO IS EMPTY \n");
    }
    else{
        temp = fifo->tail ;
        printf("--------------FIFO_print-------------- \n");

        for(i=0 ; i<fifo->count ; i++){
            printf("\t the element number %d is %d \n",i,*temp);
            temp++;
        }
        printf("--------------FIFO-------------- \n");
    }
}
