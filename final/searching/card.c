#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../search_library.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

typedef struct _card{
    int no;
    char name[20];
}card;

int cardcmp(const void *a, const void *b);
void print_card(void *base, int n_elem);

void main() {
    card table[MAX], key;
    int c, t, n_item;
    n_item = 0;

    printf("\nCard Manager");
    printf("\n---------------------");
    printf("\n1. Input name card");
    printf("\n2. Delete name card");
    printf("\n3. Search name card");
    printf("\n4. F_Search name card");
    printf("\n5. Show list");
    printf("\n6. Program end ...");

    do {
        printf("\n: selection operation -> ");
        scanf("%d", &c);

        switch(c) {
            case 1:
                printf("input no: ");
                scanf("%d", &(key.no));
                printf("input name: ");
                scanf("%s", key.name);

                seq_insert(&key, table, &n_item, sizeof(card));
                break;

            case 2:
                printf("input no: ");
                scanf("%d", &(key.no));

                seq_delete(&key, table, &n_item, sizeof(card), cardcmp);
                break;

            case 3:
                printf("input no: ");
                scanf("%d", &(key.no));

                if((t = seq_search(&key, table, n_item, sizeof(card), cardcmp)) >= 0) {
                    printf("searched id: %d / searched name: %s\n", (table[t]).no, (table[t]).name);
                }
                break;

            case 4:
                printf("input no: ");
                scanf("%d", &(key.no));

                seq_f_search(&key, table, n_item, sizeof(card), cardcmp);
                if(t > -1) {
                    printf("searched id: %d / searched name: %s\n", (table[0]).no, (table[0]).name);
                }
                break;
            
            case 5:
                print_card(table, n_item);
                break;
            
            default:
                break;
        }
    } while(c != 6);
}

int cardcmp(const void *a, const void *b) {
    return ((card *)a)->no - ((card *)b)->no;
}

void print_card(void *base, int n_elem) {
    for (int i = 0; i < n_elem; i++) {
        printf("%d : %s\n", ((card *)base + i)->no, ((card *)base + i)->name);
    }
}