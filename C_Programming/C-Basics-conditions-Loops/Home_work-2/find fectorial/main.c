#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n , i;
    unsigned long int Fact = 1;
    printf("Enter a number: ");
    scanf("%d" ,&n);

    //Find Factorial num:
    if (n<0){
        printf("Error!!! Factorial of negative number doesn't exist. ");
    }
    else{
            for(i=1; i<=n ;++i){
                Fact*=i; // Factorial = Factorial * i
    }
    printf("Factorial = %lu" , Fact);
    }
    return 0;
}
