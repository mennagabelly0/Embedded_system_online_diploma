#ifndef US_H_INCLUDED
#define US_H_INCLUDED

// Ultrasonic sensor

#include"state.h"
enum{
    US_busy
}US_state_id;

// prototypes
STATE_define(US_busy) ;
void US_init() ;
void (*US_state)() ;
int generate_random(int l, int r, int count) ;


#endif // US_H_INCLUDED
