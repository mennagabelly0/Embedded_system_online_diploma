#include <stdio.h>
#include <stdlib.h>

int getUnique(int arr[], int size) {
    int result = 0;

    for (int i = 0; i < size; i++) {
        result ^= arr[i];
    }

    return result;
}

int main() {
    int size;
    printf("Enter size of array: ");
    scanf("%d", &size);

    int arr[size];
    printf("Enter %d numbers:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    int result = getUnique(arr, size);
    printf("Unique number in array is %d\n", result);

    return 0;
}
