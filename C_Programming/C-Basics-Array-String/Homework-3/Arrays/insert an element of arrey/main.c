#include <stdio.h>
#include <stdlib.h>

int main()
{ //insert an element of array
    int num,val ,loc, i ,x[50];

    printf("\nEnter no of elements : ");
    scanf("%d",&num);
    if(num>50 || num<=0){
        printf("Error!!Enter count of elements range of(1 to 50).\n");
        printf("Enter count of elements again : ");
        scanf("%d",&num);
    }
    for(i=0;i<num;i++){
        scanf("%d",&x[i]);
    }
    printf("\nEnter the element to be inserted : ");
    scanf("%d",&val); //5
    printf("\nEnter the location : ");
    scanf("%d",&loc); //2
    // arr =>1 2 3 4 => new arr => 1 5 2 3 4
    for(i=num;i>=loc;i--){
        x[i]=x[i-1];
    }
    num++;
    x[loc-1]=val;
    for(i=0;i<num;i++)
        printf("%d ", x[i]);

    return 0;
}
