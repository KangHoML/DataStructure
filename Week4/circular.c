#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warninig(disable: 4996)

typedef struct _node {
    int key;
    struct _node *next;
}node;

node *head;

void insert_nodes(int k) {
    node *t = (node *)calloc(1, sizeof(node));

    t->key = 1;
    head = t;

    for(int i = 2; i <= k; i++) {
        t->next = (node *)calloc(1, sizeof(node));
        t = t->next;
        t->key = i;
    }
    t->next = head;
}

void delete_after(node *t) {
    node *s;
    
    s = t->next;
    t->next = t->next->next;
    free(s);
}

void circular(int n, int m) {
    node *t;
    int i;

    insert_nodes(n);
    t = head;

    while(t != t->next) {
        for (i = 0; i < m-1; i++) {
            t = t->next;
        }
        printf("%d ", t->next->key);
        delete_after(t);
    }
    
    printf("%d\n", t->key);
}

void main() {
    int n, m;

    printf("enter n & m: ");
    scanf("%d %d", &n, &m);

    circular(n, m);
}