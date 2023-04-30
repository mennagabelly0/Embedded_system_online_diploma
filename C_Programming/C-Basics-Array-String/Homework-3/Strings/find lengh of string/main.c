#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char c ,ch[100];
    printf("Enter a string: ");
    gets(ch);
    printf("\nLength of string : %zu",strlen(ch));
    return 0;
}
