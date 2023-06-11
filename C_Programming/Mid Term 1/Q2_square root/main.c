#include <stdio.h>
#include <stdlib.h>

double squareRoot(int num) {
    double x = num;
    double y = 1;
    double epsilon = 0.000001; // set a small value for precision

    while (x - y > epsilon) {
        x = (x + y) / 2;
        y = num / x;
    }

    return x;
}

int main() {
    int num;
    printf("input: ");
    scanf("%d", &num);

    double result = squareRoot(num);
    printf("output %.3lf\n", result);

    return 0;
}
