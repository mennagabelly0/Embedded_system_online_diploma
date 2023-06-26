#include <stdio.h>
#include <stdlib.h>

struct Scircle{
    float pi;
    int radi;
    float result;

}Garea ;
int main()
{
    Garea.pi = 3.14;
    printf("Enter The Radius: ");
    scanf("%d" , &Garea.radi);
    Garea.result = Garea.pi* Garea.radi * Garea.radi;
    printf("Area : %.2f" , Garea.result);
    return 0;
}
