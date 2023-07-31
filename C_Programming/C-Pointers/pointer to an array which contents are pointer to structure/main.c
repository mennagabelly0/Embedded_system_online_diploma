#include <stdio.h>
#include <stdlib.h>

struct Semployee{
    char name[50];
    int id;
};
int main()
{

	static struct Semployee a={"Menna",1001}, b={"Alex",1002} , c={"Nemo",1003};
	struct Semployee *arr[3]={&a,&b,&c};
	struct Semployee *((*p)[3])=&arr ;

	printf("Employee Name: %s",(*(*p+1))->name);
	printf("\nEmployee id: %d",(*(*p+1))->id);

	return 0;
}
