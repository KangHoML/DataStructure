#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util_library.h"
#include "../search_library.h"

#define SEQ 15

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

void read_txt(char *data[], int *len, char filename[]);
void print_list(node *base);

void main() {
    char *data[MAX], key;
    int idx, size;
    void *p;
    node *head, *t;

    // data 가져오기
    for(int i = 0; i < MAX; i++)
        data[i] = (char *)malloc(SEQ * sizeof(char));
        
    idx = 0;
    read_txt(data, &idx, "./words.txt");
    
    // 초기화
    init(&head);
    size = 0;

    // 리스트에 추가
    t = head;
    for (int i = 0; i <= idx; i++) {
        t = linked_insert(data[i], t, &size, sizeof(char) * SEQ);
    }
    print_list(head);

    // search
    key = 'k';
    t = head;
    while(1) {
        p = linked_search(&key, t, charcmp);
        if (p == NULL) break;

        printf("searched word : %s\n", (char *)p);
        t = (node *)p - 1;
    }
    printf("\n");

    // f_search
    key = 'k', t = head;
    while(1) {
        t = linked_f_search(&key, t, charcmp);
        if (t == NULL) break;
    }
    print_list(head);

    // delete
    key = 'k';
    t = head;
    while(1) {
        t = linked_delete(&key, t, &size, charcmp);
        if (t == NULL) break;
    }
    print_list(head);

    // free
    for (int i = 0; i < MAX; i++)
        free(data[i]);
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

void print_list(node *base) {
    node *t = base->next;

    while(t != NULL) {
        printf("%s\n", (char *)(t + 1));
        t = t->next;
    }
    printf("\n");
}