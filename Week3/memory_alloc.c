#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warninig(disable: 4996)

void compute(int** matrix, int len);
void main() {
    int len;
    printf("input matrix size: ");
    scanf("%d", &len);

    int** matrix = (int**)calloc(len, sizeof(int*));
    for(int i = 0; i < len; i++) {
        *(matrix + i) = (int *)calloc(len, sizeof(int));
    }

    compute(matrix, len);
    
    for(int i = 0; i < len; i++) {
        free(*(matrix + i));
    }
    free(matrix);
}

void compute(int** matrix, int len) {
    float avg = 0.0;
    
    for(int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            scanf("%d", (*(matrix + i) + j));
            avg +=(float)(*(*(matrix + i) + j));
        }
    }
    
    avg /= (float)(len * len);
    printf("%f\n", avg);
}