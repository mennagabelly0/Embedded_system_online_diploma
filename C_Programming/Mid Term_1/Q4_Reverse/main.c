#include <stdio.h>
#include <stdlib.h>

//Reverse sentence using Recursion
void reverse(){
    char x;
    scanf("%c" , &x);
    if(x !='\n'){
        reverse();
        printf("%c" , x);
    }

}
int main()
{
    printf("input: ");
    reverse();
    return 0;
}
