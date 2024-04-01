#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

void toss_dice(int n) {
    int* freq = (int*)calloc(6, sizeof(int));

    for (int i = 0; i < n; i++) {
        int dice = rand() % 6 + 1;
        *(freq + dice - 1) += 1;
    }

    for (int i = 0; i < 6; i++) {
        printf("%d: %d \n",i+1, *(freq + i));
    }
}

void main() {
    int n;
    srand(time(NULL));
    scanf("%d", &n);
    
    toss_dice(n);
}