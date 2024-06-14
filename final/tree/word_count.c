#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bt_library.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

typedef struct _wcount {
    int count;
    char word[20];
} wcount;

node *head;
const char delim[] = " \t\r\n,.-:";

int wcmp(const void *a, const void *b);
void print_wc(void *a);

void main() {
    int t_size;
    char str[256], *tok;
    wcount wc, *wcp;
    FILE *fp;

    init_tree(&head);
    t_size = 0;

    fp = fopen("./test.txt", "r");

    while(fgets(str, 256, fp) != NULL) {
        tok = strtok(str, delim);
        
        while(tok) {
            strcpy(wc.word, tok);
            
            wcp = (wcount *)bt_search(&wc, head, wcmp);
            if (wcp == NULL) {
                wc.count = 1;
                bt_insert(&wc, head, &t_size, sizeof(wcount), wcmp);
            }
            else 
                (wcp->count)++;
            
            tok = strtok(NULL, delim);
        }
    }

    printf("\n\nOriginal Tree:\n");
    print_tree(head->left, print_wc, 0);

    printf("\n\nBalanced Tree:\n");
    balancify(head, &t_size, sizeof(wcount));
    print_tree(head->left, print_wc, 0);

    fclose(fp);
}

int wcmp(const void *a, const void *b) {
    return strcmp(((wcount *)a)->word, ((wcount *)b)->word);
}

void print_wc(void *a) {
    printf("%s : %d\n", ((wcount *)a)->word, ((wcount *)a)->count);
}

