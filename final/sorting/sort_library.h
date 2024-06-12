#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE(i) ((char *)base + (i) * size)
#define SRC(i) ((char *)src + (i) * size)
#define DST(i) ((char *)dst + (i) * size) 
typedef int (*FCMP)(const void *, const void *);

// general sort function
void select_sort(void *base, int n_elem, int size, FCMP fcmp);
void bubble_sort(void *base, int n_elem, int size, FCMP fcmp);
void insert_sort(void *base, int n_elem, int size, FCMP fcmp);
void shell_sort(void *base, int n_elem, int size, FCMP fcmp);
void quick_sort(void *base, int n_elem, int size, FCMP fcmp);

// heap sort function
void _upheap(void *base, int h_elem, int size, FCMP fcmp);
void _downheap(void *base, int h_elem, int p, int size, FCMP fcmp);
void _insert(void *base, void *value, int *h_elem, int size, FCMP fcmp);
void _extract(void *base, void *value, int *h_elem, int size, FCMP fcmp);
void up_heap_sort(void *base, int n_elem, int size, FCMP fcmp);
void dn_heap_sort(void *base, int n_elem, int size, FCMP fcmp);

// util function
void _swap(void *a, void *b, int size);
void _shift(void *base, int n_elem, int size, int r);
void sort(void *dst, void *src, int n_elem, int size, FCMP fcmp, void(* fptr)(void *, int, int, FCMP));
int intcmp(const void *a, const void *b);
void print_int(void *base, int n_elem);