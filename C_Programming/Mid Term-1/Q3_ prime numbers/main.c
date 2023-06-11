#include <stdio.h>
#include <stdlib.h>
//prime numbers between two numbers : A prime number (or a prime) is a natural number greater than 1 that is not a product of two smaller natural numbers.
int check (int num){
    int x , y=0;
    for(x=2; x<=num/2; ++x){
        if(num%x==0){
            y=1;
            break;
        }
    }
    return y;
}

int main()
{
    int n1, n2, i, y;

    printf("input n1: ");
    scanf("%d" ,&n1);
    printf("n2: ");
    scanf("%d" , &n2);

    printf("\noutput: ");

    for(i=n1+1;i<n2;++i){
        y =check(i);
        if(y==0)
            printf("%d " ,i);
        }

    return 0;
}
