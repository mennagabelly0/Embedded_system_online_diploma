#include <stdio.h>
#include <stdlib.h>

int main()
{
    float x [2][2] , y [2][2] ,z [2][2];
    int i ,j;

    printf("Enter the elements of 1st matrix \n");
    for(i=0; i<2;++i){
        for(j=0;j<2;++j){
            printf("Enter  a%d%d : ",i+1 ,j+1);
            scanf("%f", &x[i][j]);
        }
    }
    printf("\nEnter the elements of 2nd matrix \n");
    for(i=0; i<2 ;++i){
        for(j=0;j<2;++j){
            printf("Enter  b%d%d : ",i+1 ,j+1);
            scanf("%f", &y[i][j]);
        }
    }
      for(i=0; i<2 ;++i)
        for(j=0;j<2;++j){
           z[i][j]=x[i][j]+y[i][j];
        }

    printf("\nSum Of Matrix :\n");
     for(i=0; i<2 ;++i)
        for(j=0;j<2;++j){
            printf("%.1f " , z[i][j]);
            if(j==1)
                printf("\n");
        }
    return 0;
}
