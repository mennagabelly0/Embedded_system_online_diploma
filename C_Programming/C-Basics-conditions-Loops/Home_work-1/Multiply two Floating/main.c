#include <stdio.h>
#include <stdlib.h>

int main()
{
    float i , j , mul =0;

    printf("Enter two numbers: ");
    scanf("%f %f", &i, &j);

    // calculate Multiply two Floating Point Numbers
    mul = i*j;
    printf("Product: %.2f" , mul);
    return 0;
}
