#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a;
    printf("Enter a character: ");
    scanf("%c" , &a);

    //Find a character
    printf("ASCII value of %c = %d " , a , a);
    return 0;
}
