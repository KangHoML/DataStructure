#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util_library.h"
#include "../sort_library.h"
#include "../search_library.h"


void print_list(node *base);

void bi_exampe() {
    char str[MAX] = "TOSORTALGORITHM";
    int size = 15;
    int pos, key;

    // sorting
    dn_heap_sort(str, size, sizeof(char), charcmp);
    print_char(str, size);

    // search
    key = 'S';
    pos = bi_search(&key, str, size, sizeof(char), charcmp);
    printf("index %d of value %c\n", pos, str[pos]);

    // insert
    key = 'M';
    bi_insert(&key, str, &size, sizeof(char), charcmp);
    print_char(str, size);

    // delete
    key = 'A';
    bi_delete(&key, str, &size, sizeof(char), charcmp);
    print_char(str, size);
}

void seq_example() {
    char str[MAX] = "TOSORTALGORITHM";
    int size = 15;
    int pos, key;

    print_char(str, size);

    // search
    key = 'S';
    pos = seq_search(&key, str, size, sizeof(char), charcmp);
    printf("index %d of value %c\n", pos, str[pos]);

    // insert
    key = 'M';
    seq_insert(&key, str, &size, sizeof(char));
    print_char(str, size);

    // delete
    key = 'A';
    seq_delete(&key, str, &size, sizeof(char), charcmp);
    print_char(str, size);

    // f_search
    key = 'M';
    seq_f_search(&key, str, size, sizeof(char), charcmp);
    print_char(str, size);
}

void linked_example() {
    char str[MAX] = "TOSORTALGORITHM";
    char key;
    int n_size, l_size;
    node *head, *t, *last;

    // initialize
    init(&head);
    
    // make the linked list
    last = head;
    n_size = 15, l_size = 0;
    for (int i = 0; i < n_size; i++) {
        last = linked_insert(&(str[i]), last, &l_size, sizeof(char));
    }
    print_list(head);

    // search
    key = 'S';
    t = linked_search(&key, head, charcmp);
    printf("value %c\n", *(char *)t);

    // insert
    key = 'M';
    last = linked_insert(&key, last, &l_size, sizeof(char));
    print_list(head);

    // delete
    key = 'A';
    linked_delete(&key, head, &l_size, charcmp);
    print_list(head);

    // f_search
    key = 'M';
    linked_f_search(&key, head, charcmp);
    print_list(head);
}

void main() {
    printf("--- Binary ---\n");
    bi_exampe();

    printf("\n--- Sequential ---\n");
    seq_example();

    printf("\n--- Linked ---\n");
    linked_example();
}

void print_list(node *base) {
    node *t = base->next;
    while(t != NULL) {
        printf("%c ", *(char *)(t + 1));
        t = t->next;
    }
    printf("\n");
}