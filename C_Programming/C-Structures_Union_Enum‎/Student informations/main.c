#include <stdio.h>
#include <stdlib.h>

//student informations
struct Sdata{
    char name[50];
    int roll;
    float marks;
}Gstudent;

int main()
{
    printf("Enter informations of students: \n");
    printf("\nEnter name: ");
    scanf("%s", &Gstudent.name);
    printf("Enter roll numbers: ");
    scanf("%d" , &Gstudent.roll);
    printf("Enter marks: ");
    scanf("%f" , &Gstudent.marks);


    printf("\nDisplaying Informations \n");
    printf("Name: %s" , Gstudent.name);
    printf("\nRoll: %d" , Gstudent.roll);
    printf("\nMarkS: %.2f" , Gstudent.marks);

    return 0;
}
