#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10

void select_sort(int *a, int N);
int intcmp(const void *a, const void *b);
void gen_select_sort(void *base, int n_elem, size_t size, 
                     int (*fcmp)(const void *a, const void *b));
void print_list(void *base, int n_elem);

void main() {
    srand(time(NULL));
    int number[SIZE];

    printf("--- Direct ---\n");
    for (int i = 0; i < SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }
    select_sort(number, SIZE);
    print_list((void *)number, SIZE);

    printf("--- Generalized ---\n");
    for (int i = 0; i < SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }
    gen_select_sort(number, SIZE, sizeof(int), intcmp);
    print_list((void *)number, SIZE);
}

void select_sort(int *a, int N) {
    int min, min_idx;

    for (int i = 0; i < N-1; i++) {
        min_idx = i;
        min = a[i];
        for (int j = i + 1; j < N; j++) {
            if (a[j] < min) {
                min_idx = j;
                min = a[j];
            }
        }
        a[min_idx] = a[i];
        a[i] = min;
    }
}

int intcmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void gen_select_sort(void *base, int n_elem, size_t size, int (*fcmp)(const void *a, const void *b)) {
    void *min = malloc(size);
    int min_idx;

    for (int i = 0; i < n_elem-1; i++) {
        min_idx = i;
        memcpy(min, (char *)base + i * size, size); // min = base[i];
        
        for (int j = i + 1; j < n_elem; j++) {
            if (fcmp(min, (char *)base + j * size) > 0) {
                min_idx = j;
                memcpy(min, (char *)base + j * size, size); // min = base[j];
            }
        }

        memcpy((char *)base + min_idx * size, (char *)base + i * size, size); // base[min_idx] = base[i];
        memcpy((char *)base + i * size, min, size); // base[i] = min
    }

    free(min);
}

void print_list(void *base, int n_elem) {
    for (int i = 0; i < n_elem; i++) {
        printf("%-5d", *((int*)base + i));
    }
    printf("\n");
}