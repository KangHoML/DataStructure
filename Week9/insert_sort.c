#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10

void insert_sort(int *a, int N);
int intcmp(const void *a, const void *b);
void indirect_insert_sort(int *a, int *index, int N);
void gen_insert_sort(void *base, int n_elem, size_t size, 
                     int (*fcmp)(const void *a, const void *b));
void print_list(void *base, int n_elem);
void print_indirect_list(void *base, int *index, int n_elem);

void main() {
    srand(time(NULL));
    int number[SIZE];

    printf("--- Direct ---\n");
    for (int i = 0; i < SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }
    insert_sort(number, SIZE);
    print_list((void *)number, SIZE);

    printf("--- Indirect ---\n");
    for (int i = 0; i < SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }

    int *index = (int *)calloc(SIZE, sizeof(int));
    indirect_insert_sort(number, index, SIZE);
    print_list((void *)number, SIZE);
    print_indirect_list((void *)number, index, SIZE);
    free(index);

    printf("--- Generalized ---\n");
    for (int i = 0; i < SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }

    gen_insert_sort(number, SIZE, sizeof(int), intcmp);
    print_list((void *)number, SIZE);
}

void insert_sort(int *a, int N) {
    int j, temp;

    for (int i = 1; i < N; i++) {
        temp = a[i];
        j = i;
        while(j > 0 && a[j-1] > temp) {
            a[j] = a[j-1];
            j--;
        }
        a[j] = temp;
    }
}

void indirect_insert_sort(int *a, int *index, int N) {
    int j, temp;

    for (int i = 0; i < N; i++) {
        index[i] = i;
    }

    for(int i = 1; i < N; i++) {
        temp = index[i];
        j = i;

        while(j > 0 && a[index[j-1]] > a[temp]) {
            index[j] = index[j-1];
            j--;
        }

        index[j] = temp;
    }
}

int intcmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void gen_insert_sort(void *base, int n_elem, size_t size, int (*fcmp)(const void *a, const void *b)) {
    void *temp = malloc(size);
    int j;

    for (int i = 1; i < n_elem; i++) {
        memcpy(temp, (char *)base + i * size, size); // temp = base[i];
        j = i;

        while(j > 0 && fcmp((char *)base + (j-1) * size, temp) > 0) {
            memcpy((char *)base + j * size, (char *)base + (j-1) * size, size);
            j--;
        }
        memcpy((char *)base + j * size, temp, size);
    }
    free(temp);
}

void print_list(void *base, int n_elem) {
    for (int i = 0; i < n_elem; i++) {
        printf("%-5d", *((int*)base + i));
    }
    printf("\n");
}

void print_indirect_list(void *base, int *index, int n_elem) {
    for (int i = 0; i < n_elem; i++) {
        printf("%-5d", *((int*)base + index[i]));
    }
    printf("\n");
}