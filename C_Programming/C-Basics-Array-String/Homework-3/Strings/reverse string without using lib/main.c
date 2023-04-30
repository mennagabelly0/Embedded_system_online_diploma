#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char rev , ch[100];
    int i =0, j =0;
    printf("Enter the string : "); //menna
    gets(ch);
   // i = 0;
    i= strlen(ch)-1;              // i = 5 -1
    while(i>j){
        rev = ch[i];    // ver = ch[4]
        ch[i] = ch[j]; //  ch[i] = ch[0]
        ch[j] = rev;  //   ch[j] = ver = ch[4]
        i--;
        j++;
    }
    printf("Reverse string is :%s" ,ch);
    return 0;
}
