#include <stdio.h>
#include <stdlib.h>

int main()
{
    char x;
    printf("enter an alphabet: ");
    scanf("%c" , &x);

    //a, e, i, o and u
    if(x== 'a' || x== 'e' || x== 'i' || x== 'o' || x== 'u' || x=='A' || x=='E' || x=='I' || x=='O' || x=='U' )
        printf("%c is a vowel" , x);
    else
        printf("%c is a consonant" , x);
    return 0;
}
