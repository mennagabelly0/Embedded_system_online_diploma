#ifndef DC_H_INCLUDED
#define DC_H_INCLUDED

#include"state.h"
enum{
    DC_idle ,
    DC_busy
}DC_state_id;

// prototypes
STATE_define(DC_idle) ;
STATE_define(DC_busy) ;

void DC_init() ;
extern void (*DC_state)() ;

#endif // DC_H_INCLUDED
