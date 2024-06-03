#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _node {
    struct _node *next;
}node;

void print_list(node *head, size_t size);

void main() {
    node *t;
    char key;

    t = (node *)malloc(sizeof(node) + sizeof(char));
    t->next = NULL;
    
    key = 'a';
    memcpy(t + 1, &key, sizeof(char));
    
    printf("%c\n", *(char *)(t + 1));
    free(t);
}

void print_list(node *head) {
    node *cursor = head;
    
    while(cursor->next != NULL) {
        printf("%-5d", *(int *)(cursor + 1));
    }
    printf("\n");
}