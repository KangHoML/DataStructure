#include <stdio.h>
#include <stdlib.h>

typedef struct _complex {
    float re;
    float im;
}complex;

complex multiply(complex a, complex b) {
    complex c;
    c.re = a.re * b.re - a.im * b.im;
    c.im = a.re * b.im + a.im * b.re;
    return c;
}

void main() {
    complex a = {1.3, 3.9};
    complex b = {-3.3, 8.4};
    complex result;

    result = multiply(a, b);
    printf("re: %f, im: %f\n", result.re, result.im);
}