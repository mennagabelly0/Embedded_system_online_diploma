#include <stdio.h>
#include <stdlib.h>

int main()
{
    char x[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *px;
    px =x;
    printf("The Alphabets are : \n" );
    while(*px != '\0'){
        printf("%c " , *px );
        px++;
    }

    return 0;
}
