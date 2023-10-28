// DC MOTOR
#include "DC.h"
#include "state.h"
#include "stdio.h"
#include "stdlib.h"

static unsigned int speed = 0 ;
void (*DC_state)() ;

void DC_init()
{
     // init DC sensor
    // call DC Driver or Function
    printf("DC_init\n") ;
}
void DC_motor(int s)
{
    speed = s ;
    DC_state = STATE(DC_busy) ;
    printf("AC ---------speed = %d ---------- DC MOTOR () \n" , speed ) ;

}
STATE_define(DC_idle)
{      // state action
    DC_state_id = DC_idle ;
        //call DC DRIVER
   // DC_state = STATE(DC_idle) ;
    printf("DC idle state : speed = %d \n" , speed) ;

}
STATE_define(DC_busy)
{        // state action
    DC_state_id = DC_busy ;
        //call DC DRIVER
    DC_state = STATE(DC_idle) ;
    printf("DC Busy state : speed = %d \n" , speed) ;
}


