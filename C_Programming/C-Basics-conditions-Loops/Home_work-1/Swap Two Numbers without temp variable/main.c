#include <stdio.h>
#include <stdlib.h>

int main()
{
    float i , j ;
    printf("Enter value of a: ");
    scanf("%f" , &i );
    printf("Enter value of b: ");
    scanf("%f" , &j);

    //Swap Two Numbers without temp variable
    // for ex if i = 5 , j = 3
    i = i+j; // 5+3 = 8=> new i
    j = i-j; // 8-3 = 5=> new j
    i = i-j; // 8-5 = 3=> new i
    // so ...>  i = 3 , j = 5

    printf("\nAfter swapping, value of a = %.f" , i );
    printf("\nAfter swapping, value of b = %.f" , j );

    return 0;
}
