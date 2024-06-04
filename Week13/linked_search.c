#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

// define
#define LEN     5
#define MAX     100
#define SEQ     15

// typedef
typedef struct _node { struct _node *next; }node;
typedef int (*FCMP)(const void *, const void *);

// generalized functions for search
void init_list(node **p);
void *gen_search(void *key, node *base, int *num, size_t size, FCMP fcmp, int *pos);
void *gen_insert(void *key, node *base, int *num, size_t size, FCMP fcmp);
void *gen_delete(void *key, node *base, int *num, size_t size, FCMP fcmp);
void *gen_f_search(void *key, node *base, int *num, size_t size, FCMP fcmp);

// util functions
void swap(void *a, void *b, size_t size);
int intcmp(const void *a, const void *b);
int charcmp(const void *a, const void *b);
void print_list(node *base, int is_str);
void read_txt(char *data[], int *len, char filename[]);

void example1() {
    int key, pos;
    int size = 0;
    int data[LEN] = { 3, 1, 9, 7, 5 };
    void *p;
    node *t, *head;

    // init list
    init_list(&t);
    head = t;

    // data를 linked list로 변환
    for (int i = 0; i < LEN; i++) {
        t = gen_insert(&(data[i]), t, &size, sizeof(int), intcmp);
    }

    // linked list 출력
    print_list(head, 0);

    // search
    key = 9, pos = 0;
    p = gen_search(&key, head, &size, sizeof(int), intcmp, &pos);
    
    if (p != NULL) {
        printf("index: %d value: %d\n", pos, *(int *)p);
    }

    // insert
    key = 6;
    gen_insert(&key, head, &size, sizeof(int), intcmp);
    print_list(head, 0);

    // delete
    key = 7;
    p = gen_delete(&key, head, &size, sizeof(int), intcmp);
    if (p != NULL)
        print_list(head, 0);

    // f_search
    key = 3;
    p = gen_f_search(&key, head, &size, sizeof(int), intcmp);
    if (p != NULL)
        print_list(head, 0);
}

void example2() {
    char *data[MAX], key;
    int len, size, pos;
    void *p;
    node *t, *head;
    
    // memory allocation for data
    for(int i = 0; i < MAX; i++)
        data[i] = (char *)malloc(SEQ * sizeof(char));

    // read txt file
    len = 0;
    read_txt(data, &len, "./words.txt");

    // init linked list
    init_list(&t);
    head = t;

    // make linked list with data
    size = 0;
    for (int i = 0; i < len; i++) {
        t = gen_insert(data[i], t, &size, sizeof(char) * SEQ, charcmp);
    }
    
    // print linked list
    print_list(head, 1);

    // search
    key = 'k', pos = -1;
    t = head;
    while (1) {
        p = gen_search(&key, t, &size, sizeof(char), charcmp, &pos);

        if (p == NULL) break;

        printf("index: %d, value: %s\n", pos, (char*)p);
        t = (node *)p - 1;
    }
    printf("\n");

    // delete
    key = 'k';
    t = head;
    
    while (1) {
        p = gen_delete(&key, t, &size, sizeof(char), charcmp);
        if (p == NULL) break;
        t = (node *)p;
    }

    print_list(head, 1);

    // free
    for (int i = 0; i < MAX; i++)
        free(data[i]);

}

void main() {
    example1();
    // example2();
}

// generalized functions for search
void init_list(node **p) {
    (*p) = (node *)malloc(sizeof(node));
    (*p)->next = NULL;
}

void *gen_search(void *key, node *base, int *num, size_t size, FCMP fcmp, int *pos) {
    node *t = base->next;
    (*pos)++; // next 한 번 해주므로 한 번 더 더해주기

    while(t != NULL && fcmp(t + 1, key) != 0) {
        (*pos)++;
        t = t->next;
    }

    return (t == NULL ? NULL : t + 1);
}

void *gen_insert(void *key, node *base, int *num, size_t size, FCMP fcmp) {
    node *t = (node *)malloc(sizeof(node) + size);
    memcpy(t + 1, key, size);
    
    t->next = base->next;
    base->next = t;

    (*num)++;
    return t;
}

void *gen_delete(void *key, node *base, int *num, size_t size, FCMP fcmp) {
    node *t, *p;
    
    p = base, t = base->next;
    while(t != NULL && fcmp(t + 1, key) != 0) {
        p = t;
        t = t->next;
    }

    if (t == NULL) return NULL;
    
    p->next = t->next;
    free(t);

    (*num)--;

    return p;
}

void *gen_f_search(void *key, node *base, int *num, size_t size, FCMP fcmp) {
    node *t, *s;
    
    t = base->next;
    while(t != NULL && fcmp(t + 1, key) != 0) t = t->next;

    if (t == NULL) return NULL;

    s = base->next;
    swap(s + 1, t + 1, size);
    
    return t;
}

// util functions
void swap(void *a, void *b, size_t size) {
    void *t = malloc(size);

    memcpy(t, a, size);
    memcpy(a, b, size);
    memcpy(b, t, size);

    free(t);
}

int intcmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int charcmp(const void *a, const void * b) {
    return *(char *)a - *(char *)b;
}

void print_list(node *base, int is_str) {
    node *t = base->next;
    
    while(t != NULL) {
        if (is_str == 0)
            printf("%-5d", *(int *)(t + 1));
        else
            printf("%s\n", (char *)(t + 1));

        t = t->next;
    }
        
    printf("\n");
}

void read_txt(char *data[], int *len, char filename[]) {
    FILE *fp;
    
    fp = fopen(filename, "r");
    if (fp == NULL) return;

    while(fscanf(fp, "%s\n", data[(*len)]) != EOF) {
        (*len)++;
    }
    
    fclose(fp);
}