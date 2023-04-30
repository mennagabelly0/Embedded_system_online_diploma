#include <stdio.h>
#include <stdlib.h>

int main()
{
    float num[100] ,average , sum = 0.0;
    int i ,n;

    printf("Enter the number of data : ");
    scanf("%d",&n);

    if(n>100 || n<=0){
        printf("Error!! Enter the number of data range of(1 to 100).\n");
        printf("Enter the number of data again : ");
        scanf("%d",&n);
    }

    for(i=1; i<=n;i++){
        printf("%d. Enter number: ",i );
        scanf("%f" ,&num[i]);
        sum = sum + num[i];
    }
    //calculate average using array : adding a group of numbers and then dividing by the count of those numbers
    average = sum/n;
    printf("Average = %.2f" , average);
    return 0;
}
