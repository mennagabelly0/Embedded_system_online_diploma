#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countMaxOnes(char str[]) {
    int maxCount = 0, count = 0, zeroIndex = -1;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '0') {
            if (zeroIndex != -1) {
                maxCount = (count > maxCount) ? count : maxCount;
                count = 0;
            }
            zeroIndex = i;
        } else if (str[i] == '1') {
            if (zeroIndex != -1) {
                count++;
            }
        }
    }

    return maxCount;
}
int main() {
    char str[100];
    printf("Enter a binary string: ");
    fgets(str, 100, stdin);

    int result = countMaxOnes(str);
    printf("Maximum number of ones between two zeros is %d\n", result);

    return 0;
}
