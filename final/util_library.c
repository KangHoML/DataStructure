#include "util_library.h"

void swap(void *a, void *b, int size) {
    void *t = malloc(size);

    memcpy(t, a, size);
    memcpy(a, b, size);
    memcpy(b, t, size);

    free(t);
}

int intcmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void print_int(void *base, int n_elem) {
    for (int i = 0; i < n_elem; i++) {
        printf("%-5d", *((int *)base + i));
    }
    printf("\n");
}

int charcmp(const void *a, const void *b) {
    return *(char *)a - *(char *)b;
}

void print_char(void *base, int n_elem) {
    for (int i = 0; i < n_elem; i++) {
        printf("%c ", *((char *)base + i));
    }
    printf("\n");
}