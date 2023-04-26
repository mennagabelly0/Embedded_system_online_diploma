#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x;
    printf("Enter an integer you want to check: ");
    scanf("%d" ,&x);

    //check if E/O:
    if(x % 2 == 0)
        printf("%d is Even" , x);
    else
        printf("%d is Odd" , x);

    return 0;
}
