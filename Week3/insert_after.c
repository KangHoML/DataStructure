#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int val;
    struct _node *next;
}node;

node *insert_after(int k, node *t) {
    node *p = t->next;
    p->val = k;
    
    return p;
}

void main() {
    node *s1, *p;

    s1->val = 3;

    p = insert_after(5, s1);
    printf("val: %d\n", p->val);
}