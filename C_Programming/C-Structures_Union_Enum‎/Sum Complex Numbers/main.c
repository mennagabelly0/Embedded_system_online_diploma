#include <stdio.h>
#include <stdlib.h>

//Add Two Complex Numbers
struct Snum{
    float real ;
    float imaginary ;

}Gcomp1 , Gcomp2 ,Greselt;

void add( struct Snum Gcomp1 , struct Snum Gcomp2){
    struct Snum temp;
    temp.real = Gcomp1.real + Gcomp2.real;
    temp.imaginary = Gcomp1.imaginary +Gcomp2.imaginary;
    printf("sum= %.1f + %.1fi" , temp.real , temp.imaginary );

}

int main()
{
    printf("For 1st complex numbers \n");
    printf("Enter real and imaginary respectively : ");
    scanf("%f %f" , &Gcomp1.real , &Gcomp1.imaginary );

    printf("\nFor 2nd complex numbers\n");
    printf("Enter real and imaginary respectively : ");
    scanf("%f %f" , &Gcomp2.real , &Gcomp2.imaginary );

    add(Gcomp1 , Gcomp2);

    return 0;
}
