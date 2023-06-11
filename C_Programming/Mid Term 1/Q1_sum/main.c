#include <stdio.h>
#include <stdlib.h>

int fun(int num){
    int sum =0 ,val;
    while(num !=0){
       val= num%10;
       sum += val;
       num = num/10;
    }
    return sum;
}
int main()
{
    int num , res;
    printf("input: ");
    scanf("%d", &num);
    res = fun(num);
    printf("output: %d" , res);
    return 0;
}
