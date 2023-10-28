#ifndef AC_H_INCLUDED
#define AC_H_INCLUDED

#include"state.h"
enum{
    CA_waiting ,
    CA_driving
}CA_state_id;

// prototypes
STATE_define(CA_waiting) ;
STATE_define(CA_driving) ;
extern void (*CA_state)() ;


#endif // AC_H_INCLUDED
