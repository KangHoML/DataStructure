#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10

void bubble_sort(int *a, int N);
int intcmp(const void *a, const void *b);
void swap(void *a, void *b, size_t size);
void gen_bubble_sort(void *base, int n_elem, size_t size, 
                     int (*fcmp)(const void *a, const void *b));
void print_list(void *base, int n_elem);

void main() {
    srand(time(NULL));
    int number[SIZE];

    printf("--- Direct ---\n");
    for (int i = 0; i < SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }
    bubble_sort(number, SIZE);
    print_list((void *)number, SIZE);

    printf("--- Generalized ---\n");
    for (int i = 0; i < SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }
    gen_bubble_sort(number, SIZE, sizeof(int), intcmp);
    print_list((void *)number, SIZE);
}

void bubble_sort(int *a, int N) {
    int temp;

    for (int i = 0; i < N - 1; i++) {
        for (int j = 1; j < N - i; j++) {
            if (a[j-1] > a[j]) {
                temp = a[j-1];
                a[j-1] = a[j];
                a[j] = temp;
            }
        }
    }
}

int intcmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void swap(void *a, void *b, size_t size) {
    void *temp = malloc(size);

    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    
    free(temp);
}

void gen_bubble_sort(void *base, int n_elem, size_t size, int (*fcmp)(const void *a, const void *b)) {
    for (int i = 0; i < n_elem - 1; i++) {
        for (int j = 1; j < n_elem - i; j++) {
            if (fcmp((char *)base + (j-1) * size, (char *)base + j * size) > 0) {
                swap((char *)base + (j-1) * size, (char *)base + j * size, size);
            }
        }
    }
}

void print_list(void *base, int n_elem) {
    for (int i = 0; i < n_elem; i++) {
        printf("%-5d", *((int*)base + i));
    }
    printf("\n");
}