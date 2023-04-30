#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num,val , i ,x[50];

    printf("\nEnter no of elements : ");
    scanf("%d",&num);
    if(num>50 || num<=0){
        printf("Error!!Enter count of elements range of(1 to 50).\n");
        printf("Enter no of elements : ");
        scanf("%d",&num);
    }
    for(i=0;i<num;i++){
        scanf("%d",&x[i]);
    }

    printf("\nEnter the element to be searched : ");
    scanf("%d",&val);

    //search an element of array
    for(i=0;i<num && val!=x[i];){
       i++;
    }

    if(i<num){
       printf("\nNumber found at the location = %d" , i+1);
    }
    else
    printf("Number not found.");

    return 0;
}
