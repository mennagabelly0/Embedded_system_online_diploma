#include <stdio.h>
#include <stdlib.h>

//calculate the power of numbers using recursion

int main()
{
    int power(int x , int y);
    int base ,p;
    printf("Enter base number: ");
    scanf("%d" , &base);
    printf("Enter power of number(positive integer): ");
    scanf("%d", &p);
    printf("%d^%d = %d" , base , p , power(base ,p));
    return 0;
}

int power(int base , int p){
    if(p !=0){
        return(base*power(base, p-1));
    }
    else
    return 1;
}


