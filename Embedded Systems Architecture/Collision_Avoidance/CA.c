#include "CA.h"
#include "state.h"
#include <conio.h>
#include <stdlib.h>
#include <time.h>
static unsigned int distance , speed , threshold = 50 ;

// global pointer to fun
void (*CA_state)() ;
void US_distance_set(int d)
{
    distance = d ;
    (distance <= threshold)? (CA_state = STATE(CA_waiting)) : (CA_state = STATE(CA_driving)) ;
    printf("ULTRASONIC ---------DISTANCE = %d -----------> COLLISION AVOIDENVE \n" , distance);
}

STATE_define(CA_waiting)
{
    // state action
    CA_state_id = CA_waiting ;
    printf("Waiting State : Distance = %d , Speed = %d \n" , distance , speed) ;

    speed = 0 ;
    DC_motor(speed ) ;

}

STATE_define(CA_driving)
{
    // state action
    CA_state_id = CA_driving ;
    printf("Drive State : Distance = %d , Speed = %d \n" , distance , speed) ;

    speed = 30 ;
    DC_motor(speed ) ;


}
