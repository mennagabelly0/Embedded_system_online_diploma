#include "stdio.h"
#include "stdlib.h"
#include <conio.h>
#include <stdlib.h>
#include "CA.h"
#include "DC.h"
#include "state.h"
#include "US.h"

// global pointer to fun
//extern void (*CA_state)() ;

void setup()
{
    // motor_init() ; left & right speed
    // init SOC modules
    US_init () ;
    DC_init () ;
    CA_state = STATE(CA_waiting) ;
    US_state = STATE(US_busy) ;
    DC_state = STATE(DC_idle) ;

}
void main()
{
    volatile int d ;
    setup() ;
    while(1)
    {
        US_state() ;
        CA_state() ;
        DC_state() ;
        //delay
        for(d=0 ; d<= 10000 ; d++);
    }

 return 0;
}
