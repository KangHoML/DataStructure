#include <stdio.h>

typedef struct _node {
    int key;
    struct _node *next;
}node;

node *head, *tail;

int push(int k) {
    node *t;
    if ((t = (node *)malloc(sizeof(node))) == NULL) {
        printf("Out of Memory !\n");
        return -1;
    }

    t->key = k;
    t->next = head->next;
    head->next = t;

    return k;
}

int pop() {
    node *t;
    int k;

    if (head->next == tail) {
        printf("Stack Underflow !\n");
        return -1;
    }

    t = head->next;
    k = t->key;
    head->next = t->next;
    free(t);

    return k;

}