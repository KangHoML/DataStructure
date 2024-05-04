#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10

void shell_sort(int *a, int N, int step);
int intcmp(const void *a, const void *b);
void gen_shell_sort(void *base, int n_elem, int step, size_t size, 
                     int (*fcmp)(const void *a, const void *b));
void print_list(void *base, int n_elem);

void main() {
    srand(time(NULL));
    int number[SIZE];
    int step = 3;

    printf("--- Direct ---\n");
    for (int i = 0; i < SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }
    shell_sort(number, SIZE, step);
    print_list((void *)number, SIZE);

    printf("--- Generalized ---\n");
    for (int i = 0; i < SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }

    gen_shell_sort(number, SIZE, step, sizeof(int), intcmp);
    print_list((void *)number, SIZE);
}

void shell_sort(int *a, int N, int step) {
    int value, key;
    
    for (int gap = (N + 1)/step; gap > 0; gap = (gap + 1) / step) {
        for (int i = 0; i < gap; i++) {
            for (int j = i + gap; j < N; j += gap) {
                value = a[j];
                key = j;

                while(key > gap - 1 && a[key - gap] > value) {
                    a[key] = a[key - gap];
                    key -= gap;
                }

                a[key] = value;
            }
        }

        if (gap == 1) break;
    }

}

int intcmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void gen_shell_sort(void *base, int n_elem, int step, size_t size, int (*fcmp)(const void *a, const void *b)) {
    void *value = malloc(size);
    int key;

    for (int gap = (n_elem + 1) / step; gap > 0; gap = (gap + 1) / step) {
        for (int i = 0; i < gap; i++) {
            for (int j = i + gap; j < n_elem; j += gap) {
                memcpy(value, (char *)base + j * size, size); // value = base[j];
                key = j;

                while(key > gap - 1 && intcmp((char *)base + (key - gap) *size, value) > 0) { // while(key > gap - 1 && base[key-gap] > value)
                    memcpy((char *)base + key *size, (char *)base + (key - gap) *size, size); // base[key] = base[key - gap];
                    key -= gap;
                }

                memcpy((char *)base + key *size, value, size); // base[key] = value;
            }
        }

        if (gap == 1) break;
    }

    free(value);
}

void print_list(void *base, int n_elem) {
    for (int i = 0; i < n_elem; i++) {
        printf("%-5d", *((int*)base + i));
    }
    printf("\n");
}