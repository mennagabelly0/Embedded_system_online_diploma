#include "stdio.h"
#include "stdlib.h"
#include <conio.h>
#include <stdlib.h>
#include "AC.h"
#include "state.h"

// global pointer to fun
extern void (*state)() ;

void setup()
{
    // motor_init() ; left & right speed
    // init SOC modules
    state = STATE(waiting) ;

}
void main()
{
    volatile int d ;
    setup() ;
    while(1)
    {
        state() ;
        //delay
        for(d=0 ; d<= 10000 ; d++);
    }

 return 0;
}
/*int generate_random(int l , int r , int count)
{
    //this will generated random num in range l and r
    int i ;
    for(i = 0 ; i< count; i++){
        int rand_num = (rand() % (r - l + 1)) + 1 ;
        return rand_num ;
    }
}
*/
