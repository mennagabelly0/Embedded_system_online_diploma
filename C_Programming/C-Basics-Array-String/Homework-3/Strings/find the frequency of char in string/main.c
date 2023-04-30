#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c , ch[100];
    int i , count=0;
    printf("Enter a string : ");
    gets(ch);
    printf("\nEnter the character to find frequency : ");
    scanf("%s", &c);

    for(i=0; ch[i]!='\0';++i){
        if(ch[i]==c)
            ++count;
    }
    printf("\nFrequency Of %c = %d" , c , count);

    return 0;
}
