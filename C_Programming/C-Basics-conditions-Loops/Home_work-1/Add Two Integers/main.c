#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, sum =0;

    printf("Enter two integers: ");
    scanf("%d %d", &i, &j);

    // calculate the sum
    sum = i + j;

    printf("Sum: %d", sum);
    return 0;
}
