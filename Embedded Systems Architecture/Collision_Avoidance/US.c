// Ultrasonic sensor

#include "US.h"
#include "state.h"
#include "CA.h"

extern void (*US_state)() ;
static unsigned int distance ;

int generate_random(int l, int r, int count) {

    int i;
    for (i = 0; i < count; i++) {
        int rand_num = (rand() % (r - l + 1)) + l;
        return rand_num ;
    }
}


void US_init()
{
    // init US sensor
    // call US Driver or Function
    printf("US_init\n") ;

}
STATE_define(US_busy)
{
    //state action
    US_state_id = US_busy ;
    // read from ultrasonic
    distance = generate_random(45 , 55 ,1) ;
    printf(" Ultrasonic sensor Busy State : Distance = %d \n" , distance) ;

    US_distance_set(distance) ;
    US_state = STATE(US_busy) ;

}
