#ifndef LIFO_H_INCLUDED
#define LIFO_H_INCLUDED

// type definitions
typedef struct{
    unsigned int length ;
    unsigned int count ;
    unsigned int* base ;
    unsigned int* head ;


}LIFO_Buf_t;

typedef enum{
    LIFO_no_error ,
    LIFO_full,
    LIFO_empty,
    LIFO_Null
}LIFO_status;


//APIs
LIFO_status LIFO_Add_item (LIFO_Buf_t* lifo_buf , unsigned int item );
LIFO_status LIFO_get_item (LIFO_Buf_t* lifo_buf , unsigned int* item );
LIFO_status LIFO_init (LIFO_Buf_t* lifo_buf , unsigned int* buf  , unsigned int length);


#endif // LIFO_H_INCLUDED
