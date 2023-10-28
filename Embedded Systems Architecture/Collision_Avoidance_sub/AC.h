#ifndef AC_H_INCLUDED
#define AC_H_INCLUDED

#include "state.h"

enum{
    waiting ,
    driving
}state_id;

// prototypes
STATE_define(waiting) ;
STATE_define(driving) ;




#endif // AC_H_INCLUDED
