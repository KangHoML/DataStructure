#include "bt_library.h"

void init_tree(node **p) {
    *p = (node *)malloc(sizeof(node));
    (*p)->left = NULL;
    (*p)->right = NULL;
}

void *bt_search(void *key, node *base, FCMP fcmp) {
    node *t;
    
    t = base->left;
    while(t != NULL && fcmp(key, t+1) != 0) {
        if (fcmp(key, t+1) < 0) t = t->left;
        else t = t->right;
    }

    return t == NULL ? NULL : t + 1;
}

void *bt_insert(void *key, node *base, int *n_elem, int size, FCMP fcmp) {
    node *p, *t;
    
    p = base, t = base->left;
    while(t != NULL) {
        p = t;
        if (fcmp(key, t+1) < 0) t = t->left;
        else t = t->right;
    }

    t = (node *)malloc(sizeof(node) + size);
    memcpy(t+1, key, size);
    t->left = NULL, t->right = NULL;

    if (fcmp(key, p+1) < 0 || p == base) p->left = t;
    else p->right = t;

    (*n_elem)++;

    return t;
}

void *bt_delete(void *key, node *base, int *n_elem, FCMP fcmp) {
    node *p, *s, *d, *n;
    
    if(*n_elem < 1) return NULL;

    p = base, d = base->left;
    while(d != NULL && fcmp(key, d+1) != 0) {
        p = d;
        if (fcmp(key, d+1) < 0) d = d->left;
        else d = d->right;
    }

    if (d == NULL) return NULL;

    if (d->right == NULL)
        s = d->left;
    
    else if (d->right->left == NULL) {
        s = d->right;
        s->left = d->left;
    }
    
    else {
        n = d->right;
        while(n->left->left != NULL) n = n->left;

        s = n->left;
        n->left = s->right;

        s->left = d->left;
        s->right = d->right;
    }

    if (fcmp(key, p+1) < 0 || p == base) p->left = s;
    else p->right = s;

    free(d);
    (*n_elem)--;

    return p;
}

void _deleteall(node *t) {
    if (t == NULL) return;

    _deleteall(t->left);
    _deleteall(t->right);
    free(t);
}

void *delete_tree(node *base, int *n_elem) {
    _deleteall(base->left);

    base->left = NULL, base->right = NULL;
    *n_elem = 0;

    return base;   
}

int _index;

void _sort(node *t, void *a, int size) {
    if (t == NULL) return;

    _sort(t->left, a, size);
    memcpy((char *)a + (_index++) * size, t+1, size);
    _sort(t->right, a, size);
}

void *_balance(int n, void *a, int size) {
    int low, high;
    node *t;

    if (n <= 0) return NULL;

    low = (n - 1) / 2;
    high = n - 1 - low;

    t = (node *)malloc(sizeof(node) + size);
    
    t->left = _balance(low, a, size);
    memcpy(t+1, (char *)a + (_index++) * size, size);
    t->right = _balance(high, a, size);

    return t;
}

void balancify(node *base, int *n_elem, int size) {
    void *a;
    int tree_size;

    a = malloc(*n_elem * size);
    _index = 0;
    _sort(base->left, a, size);

    tree_size = *n_elem;
    delete_tree(base, n_elem);
    
    _index = 0;
    base->left = _balance(tree_size, a, size);
    *n_elem = tree_size;

    free(a);
}

void print_tree(node *t, void (*fptr)(void *), int level) {
    if (t == NULL) return;

    print_tree(t->right, fptr, level + 1);
    for (int i = 0; i < level; i++) printf("\t");
    fptr(t+1);
    print_tree(t->left, fptr, level + 1);
}