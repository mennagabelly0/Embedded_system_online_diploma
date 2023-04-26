#include <stdio.h>
#include <stdlib.h>

int main()
{
    float i , j ,k;
    printf("Enter value of a:");
    scanf("%f" , &i );
    printf("Enter value of b:");
    scanf("%f" , &j);

    //swap num
    k = i; //a
    i = j; //b
    printf("\nAfter swapping, value of a = %.2f" , i );
    printf("\nAfter swapping, value of b = %.1f" , k );
    return 0;
}
