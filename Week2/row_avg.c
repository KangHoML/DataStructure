#include <stdio.h>
#include <stdlib.h>

#define ROWS 4
#define COLS 3

int m[ROWS][COLS] = {{1, 3, 5},
                     {9, 7, 3},
                     {3, 3, 9},
                     {2, 8, 6}};

float get_row_avg(int m[][COLS], int r) {
    int *start, *end;
    float avg = 0;

    start = *(m + r);
    end = *(m + r) + COLS - 1;

    while(start <= end) {
        avg += *start;
        printf("%d\n", *start);
        start++;
    }

    avg /= COLS;
    return avg;
}

void main() {
    for(int i = 0; i < ROWS; i++) {
        printf("%f\n", get_row_avg(m, i));
    }
}