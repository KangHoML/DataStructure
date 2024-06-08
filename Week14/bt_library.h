#include <stdio.h>
#include <stdlib.h>

typedef int (*FCMP)(const void *, const void *);

typedef struct _node {
    struct _node *left;
    struct _node *right;
}node;

void init_tree(node **p);

void *bt_search(void *key, node *base, int *num, size_t size, FCMP fcmp);
void *bt_insert(void *key, node *base, int *num, size_t size, FCMP fcmp);
void *bt_delete(void *key, node *base, int *num, size_t size, FCMP fcmp);

void _deleteall(node *t);
void *delete_tree(node *base, int *num);

void _sort(node *p, void *a, size_t size);
node *_balance(int n, void *a, size_t size);
void balancify(node *base, int *num, size_t size);

void print_tree(node *t, void(*fptr)(void *), int level);