#include <stdio.h>
#include <stdlib.h>
//add two distances in the inch-feet
struct Sspace{
    int feet;
    float inch;
}Gdist1 , Gdist2 ,Gtotal ;
int main()
{
    printf("Enter informations for 1st distance \n");
    printf("Enter feet: ");
    scanf("%d", &Gdist1.feet);
    printf("Enter inch: ");
    scanf("%f" , &Gdist1.inch);

    printf("\nEnter informations for 2nd distance \n");
    printf("Enter feet: ");
    scanf("%d", &Gdist2.feet);
    printf("Enter inch: ");
    scanf("%f" , &Gdist2.inch);

    Gtotal.feet = Gdist1.feet + Gdist2.feet;
    Gtotal.inch = Gdist2.inch + Gdist2.inch;

    if(Gtotal.inch>= 12.0){
        Gtotal.inch = Gtotal.inch -12.0;
        ++Gtotal.feet;
    }

    printf("\nSum of distances = %d\'-0.%.f\"" ,Gtotal.feet , Gtotal.inch );
    return 0;
}
