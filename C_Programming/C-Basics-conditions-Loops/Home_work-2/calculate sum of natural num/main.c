#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int sum =0 , n , i;
    printf("Enter a number: ");
    scanf("%d" ,&n);

    //calculate sum of natural num:
    for(i=0; i<=n ;i++){
        sum+=i; // sum = sum + i
    }
    printf("Sum = %d" , sum);
    return 0;
}
