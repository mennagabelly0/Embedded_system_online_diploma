#include <stdio.h>
#include <stdlib.h>

void reverse(char *px ){
    if(*px =='\0'){
        return;
    }
    reverse(px+1);
    printf("%c", *px);

}

int main()
{
    char x[] = "w3resource";
    char *px = &x;
    printf("Input a string : %s\n" ,px);
    printf("Reverse of the string is : ");
    reverse(px);
    return 0;
}
