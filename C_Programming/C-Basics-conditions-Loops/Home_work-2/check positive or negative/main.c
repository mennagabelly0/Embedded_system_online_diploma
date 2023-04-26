#include <stdio.h>
#include <stdlib.h>

int main()
{
    float x ;
    printf("Enter a number: ");
    scanf("%f" ,&x);

    //check positive || negative || zero:
    if(x<=0){
        if(x==0)
            printf("You entered zero.");
        else
            printf("%.2f is Negative." , x);
    }
    else
        printf("%.2f is Positive." , x);
    return 0;
}
