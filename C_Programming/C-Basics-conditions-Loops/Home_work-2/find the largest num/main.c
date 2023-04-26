#include <stdio.h>
#include <stdlib.h>

int main()
{
    float x , y , z;
    printf("Enter three numbers: ");
    scanf("%f %f %f" ,&x , &y ,&z);

    //find the largest num:
    if(x>y && x>z)
        printf("largest number = %.2f" , x);
    else if(y>x && y>z)
        printf("largest number = %.2f" , y);
    else
        printf("Largest number = %.2f" , z);

    return 0;
}
