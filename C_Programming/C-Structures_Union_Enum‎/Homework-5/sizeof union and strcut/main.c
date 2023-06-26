#include <stdio.h>
#include <stdlib.h>

union job{ //  union store a max size of data type so it will be => "32"
    char name[32];
    float salary;
    int work_on;

} u ;
struct job1{ // structures store as a sun all sizes of data types so it will be => "32 + 4 + 4 = 40"
    char name[32];
    float salary;
    int work_on;
} s ;
int main()
{
    printf("size of union = %d" , sizeof(u));
    printf("\nsize of structures = %d" , sizeof(s));
    return 0;
}
