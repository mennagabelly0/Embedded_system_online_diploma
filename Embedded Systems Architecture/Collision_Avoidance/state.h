#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include "stdio.h"
#include "stdlib.h"

//auto state function
#define STATE_define(_statefunc_) void ST_##_statefunc_()
#define STATE(_statefunc_) ST_##_statefunc_

// states connection
void US_distance_set(int d) ;
void DC_motor(int s) ;

#endif // STATE_H_INCLUDED
