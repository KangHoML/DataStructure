#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(void *a, void *b, int size);

int intcmp(const void *a, const void *b);
void print_int(void *base, int n_elem);

int charcmp(const void *a, const void *b);
void print_char(void *base, int n_elem);