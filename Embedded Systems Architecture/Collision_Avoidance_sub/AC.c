#include "AC.h"
#include "state.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
unsigned int distance , speed , threshold = 50 ;

// global pointer to fun
void (*state)() ;

int generate_random(int l , int r , int count) ;

STATE_define(waiting)
{
    // state action
    state_id = waiting ;
    speed = 0 ;
    distance = generate_random(45 ,55 , 1) ;
    // check event
    (distance <= threshold)? (state = STATE(waiting)) : (state = STATE(driving)) ;
    printf("Waiting State : Distance = %d , Speed = %d \n" , distance , speed) ;

}

STATE_define(driving)
{
    // state action
    state_id = driving ;
    speed = 30 ;
    distance = generate_random(45 ,55 , 1) ;

     // check event
    (distance <= threshold) ? (state = STATE(waiting)) :(state = STATE(driving)) ;
    printf("Drive State : Distance = %d , Speed = %d \n" , distance , speed) ;
}


int generate_random(int l, int r, int count) {

    int i;
    for (i = 0; i < count; i++) {
        int rand_num = (rand() % (r - l + 1)) + l;
        return rand_num ;
    }
}
