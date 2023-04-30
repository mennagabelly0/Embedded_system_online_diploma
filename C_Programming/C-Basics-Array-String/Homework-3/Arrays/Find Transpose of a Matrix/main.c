#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j , r , c , matrix[10][10] , transpose[10][10];
    printf("Enter rows and column of the matrix : ");
    scanf("%d %d" ,&r , &c);
     if(r&&c >10 || r&&c <=0){
        printf("Error!! Enter rows and column of the matrix range of(1 to 10).\n");
        printf("Enter rows and column of the matrix : ");
        scanf("%d %d" ,&r , &c);
    }
    printf("Enter the element of matrix :\n");
    for(i=0;i<r; ++i){
        for(j=0;j<c;++j){
            printf("Enter the element of a%d%d : " ,i+1 , j+1 );
            scanf("%d", &matrix[i][j]);
        }
    }
     printf("\nEntered Matrix:\n");
     for(i=0;i<r; ++i){
        for(j=0;j<c;++j){
           printf(" %d " ,matrix[i][j]);
        }
        printf("\n\n");
    }
    // Find Transpose of a Matrix
    for(i=0;i<r; ++i)
        for(j=0;j<c;++j){
            transpose[j][i]=matrix[i][j];
        }
    printf("\nTranspose of a Matrix :\n");
    for(i=0;i<c; ++i){
        for(j=0;j<r;++j){
            printf(" %d ", transpose[i][j]);
        }
    printf("\n\n");
    }
    return 0;
}
