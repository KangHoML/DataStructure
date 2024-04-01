#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

void main(){
    int a[SIZE] = {1, 2, 3, 4, 5};
    int b[SIZE], c[SIZE];

    for (int j = 0; j < SIZE; j++) {
        b[j] = a[SIZE - j - 1];
        c[j] = a[j] * b[j];
    }

    for (int j = 0; j < SIZE; j++) {
        printf("%d * %d = %d\n", a[j], b[j], c[j]);
    }
}
