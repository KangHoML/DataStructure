#include <stdio.h>
#include <stdlib.h>

// void pointer function
void* my_add(void* x, void* y, int size);
void* my_sub(void* x, void* y, int size);
void* my_mul(void* x, void* y, int size);
void* my_div(void* x, void* y, int size);

// function pointer array
void* (*fptr[4])(void*, void*, int) = {my_add, my_sub, my_mul, my_div};

void main() {
    int a_i = 1;
    int b_i = 2;

    double a_f = 1.5;
    double b_f = 2.5;

    // int type result
    for (int i = 0; i < 4; i++) {
        int *result = (int*)fptr[i](&a_i, &b_i, sizeof(int));
        printf("result(int): %d\n", *result);
        free(result);
    }

    // double type result
    for (int i = 0; i < 4; i++) {
        double *result = (double*)fptr[i](&a_f, &b_f, sizeof(double));
        printf("result(double): %f\n", *result);
        free(result);
    }
}

void* my_add(void* x, void* y, int size) {
    void* result = malloc(size);

    if (size == sizeof(int)) {
        *(int*)result = *(int*)x + *(int*)y;
    }
    else if (size == sizeof(double)) {

        *(double*)result = *(double*)x + *(double*)y;
    }

    return result;
}

void* my_sub(void* x, void* y, int size) {
    void* result = malloc(size);

    if (size == sizeof(int)) {
        *(int*)result = *(int*)x - *(int*)y;
    }
    else if (size == sizeof(double)) {

        *(double*)result = *(double*)x - *(double*)y;
    }

    return result;
}

void* my_mul(void* x, void* y, int size) {
    void* result = malloc(size);

    if (size == sizeof(int)) {
        *(int*)result = *(int*)x * *(int*)y;
    }
    else if (size == sizeof(double)) {

        *(double*)result = *(double*)x * *(double*)y;
    }

    return result;
}

void* my_div(void* x, void* y, int size) {
    void* result = malloc(size);

    if (size == sizeof(int)) {
        *(int*)result = *(int*)x / *(int*)y;
    }
    else if (size == sizeof(double)) {

        *(double*)result = *(double*)x / *(double*)y;
    }

    return result;
}