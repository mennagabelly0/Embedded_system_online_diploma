#include <stdio.h>
#include <stdlib.h>

int main()
{
    float x;
    x = 4+2%-8;
    printf("%f" ,x);
    int i ;
    i = 5/2;
    printf("\n%d" ,i);
    int a;
    a = 7/22*(3.14+2)*3/5;
    printf("\n%d" ,a);

    printf("\n%d", 1<< 2+3 <<4 );

    char c =125;
    c= c+10;
    printf("\n%d" , c);

    char m ='\012';
    printf("\n%d" , m);

    int v =0;
    int t;
    v = (v ==(v==1));
    printf("\n%d" , v);

    int z = (1,2,3);
    printf("\n%d" , z);

    float n =5.0;
    printf("\n%.2f" , (9/5)*n+32);
     //   i     j    k
    int q =5, w=10,e=15;
    printf("\n%d" , sizeof(e/=q+w));
    printf("\n%d", e);
    return 0;
}
