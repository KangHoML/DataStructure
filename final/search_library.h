#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util_library.h"

#define BASE(i) ((char *)base + (i) * size)
#define MAX 100

typedef int (*FCMP)(const void *a, const void *b);
typedef struct _node {
    struct _node *next;
}node;

int bi_search(void *key, void *base, int n_elem, int size, FCMP fcmp);
int bi_insert(void *key, void *base, int *n_elem, int size, FCMP fcmp);
int bi_delete(void *key, void *base, int *n_elem, int size, FCMP fcmp);

int seq_search(void *key, void *base, int n_elem, int size, FCMP fcmp);
int seq_insert(void *key, void *base, int *n_elem, int size);
int seq_delete(void *key, void *base, int *n_elem, int size, FCMP fcmp);
int seq_f_search(void *key, void *base, int n_elem, int size, FCMP fcmp);

void init(node **p);
void *linked_search(void *key, node *base, FCMP fcmp);
void *linked_insert(void *key, node *base, int *n_elem, int size);
void *linked_delete(void *key, node *base, int *n_elem, FCMP fcmp);
void *linked_f_search(void *key, node *base, FCMP fcmp);