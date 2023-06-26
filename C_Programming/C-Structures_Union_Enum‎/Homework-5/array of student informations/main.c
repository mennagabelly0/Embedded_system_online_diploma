#include <stdio.h>
#include <stdlib.h>

struct Sdata{
    char name[50];
    int roll;
    int marks;
}Gstudent[10];

int main()
{
    printf("Enter informations of students: \n");
    for(int i=1;i<=10;++i){
        printf("\nFor roll numbers ");
        scanf("%d", &Gstudent[i].roll);
        printf("Enter name: ");
        scanf("%s", &Gstudent[i].name);
        printf("Enter marks: ");
        scanf("%d" , &Gstudent[i].marks);
    }
    printf("\nDisplaying informations of students: \n");
    for(int i=1;i<=10;++i){
        printf("\nInformations for roll number : %d" , Gstudent[i].roll);
        printf("\nName: %s" , Gstudent[i].name);
        printf("\nMark: %d" , Gstudent[i].marks);
        }


    return 0;
}
