#include <stdio.h>
#include <stdlib.h>

int main()
{
    char x;
    float num1 ,num2;
    printf("Enter operator either + or - or * or / ");
    scanf("%c" ,&x);
    printf("Enter two Numbers: ");
    scanf("%f %f", &num1 , &num2);
    //calc:
    switch(x){
    case '+':
        printf("%.1f + %.1f = %.1f" , num1 , num2 , num1+num2);
        break;
    case '-':
        printf("%.1f - %.1f = %.1f" , num1 , num2 , num1-num2);
        break;
    case '*':
        printf("%.1f * %.1f = %.1f" , num1 , num2 , num1*num2);
        break;
    case '/':
        printf("%.1f / %.1f = %.1f" , num1 , num2 , num1/num2);
        break;
    default:
        printf("Error !!");
        break;
    }
    return 0;
}
