#include <stdio.h>

int main() {
    int n , arr[16] ;
    int *pa= &arr;
    printf("Input the number of elements to store in the array (max 15) :");
    scanf("%d" , &n);
    printf("Input %d number of elements in the array :\n" ,n) ;
    for(int i=0;i<n;i++){
        printf("element - %d : " ,i+1);
        scanf("%d" ,&arr[i]);
        pa++;
    }
    printf("The elements of array in reverse order are :\n");
    for(int i=0;i<n;i++){
		pa--;
		printf("element - %d : %d\n",(n-i),*(pa));
	}

    return 0;
}

