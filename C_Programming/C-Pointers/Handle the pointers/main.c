#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m = 29;
    int* pm = &m;
    printf("Address of m : %x\n", pm);
    printf("Value of m : %d\n", *pm);

    int *ab = &m;
    printf("Address of pointer ab : %x\n", ab);
    printf("Content of pointer ab : %d\n", *ab);

    m = 34;
    printf("Address of pointer ab : %x\n", ab);
    printf("Content of pointer ab : %d\n", *ab);

    *pm =7;
    printf("Address of m : %x\n", pm);
    printf("Value of m : %d\n", *pm);

    printf("\n");
    return 0;
}
