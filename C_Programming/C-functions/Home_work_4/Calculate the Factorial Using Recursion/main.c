#include <stdio.h>
#include <stdlib.h>
//Calculate the Factorial Using Recursion
//Recursive function to find factorial

int fact(int x){
    if(x==0)
        return 1;
    return x * fact(x - 1);

}
int main()
{
    int a;
    printf("Enter an positive integer: ");
    scanf("%d" , &a);

    printf("\nFactorial of %d = %d \n" , a ,fact(a));

    return 0;
}
