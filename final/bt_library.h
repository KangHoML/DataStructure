#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*FCMP)(const void *a, const void *b);
typedef struct _node {
    struct _node *left;
    struct _node *right;
}node;

void init_tree(node **p);

void *bt_search(void *key, node *base, FCMP fcmp);
void *bt_insert(void *key, node *base, int *n_elem, int size, FCMP fcmp);
void *bt_delete(void *key, node *base, int *n_elem, FCMP fcmp);

void _deleteall(node *t);
void *delete_tree(node *base, int *n_elem);
void _sort(node *t, void *a, int size);
void *_balance(int idx, void *a, int size);
void balancify(node *base, int *n_elem, int size);

void *_rotate(void *key, node *pivot, node *base, FCMP fcmp);
void *rbt_insert(void *key, node *base, int *n_elem, int size, FCMP fcmp);

void print_tree(node *t, void (*fptr)(void *), int level);