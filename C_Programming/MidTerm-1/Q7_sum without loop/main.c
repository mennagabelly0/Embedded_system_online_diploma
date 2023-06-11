#include <stdio.h>
#include <stdlib.h>

int sum(int num) {
    if (num == 1) {
        return 1;
    } else {
        return num + sum(num - 1);
    }
}

int main() {
    int result = sum(100);
    printf("Sum of numbers from 1 to 100 is %d\n", result);

    return 0;
}
