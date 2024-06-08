#include <string.h>
#include "bt_library.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

typedef struct _wcount {
    int count;
    char word[20];
}wcount;

node *head;
const char delim[] = " \t\r\n,.-:";

int wcount_cmp(const void *a, const void *b);
void print_wcount(void *t);

void main() {
    int num;
    char str[256], *tok;
    wcount wc, *wcp;
    FILE *fp;

    // initialize
    init_tree(&head);
    num = 0;

    // open text file
    fp = fopen("./test.txt", "r");
    
    // read file
    while(fgets(str, 256, fp) != NULL) {
        // tokenize
        tok = strtok(str, delim);
        while(tok) {
            strcpy(wc.word, tok);
            wcp = (wcount *)bt_search(&wc, head, &num, sizeof(wcount), wcount_cmp);

            // tree 안에 없을 경우
            if (wcp == NULL) {
                wc.count = 1;
                bt_insert(&wc, head, &num, sizeof(wcount), wcount_cmp);
            }

            // tree 안에 있을 경우
            else
                (wcp->count)++;
            
            // 다음 토큰 가져오기
            tok = strtok(NULL, delim);
        }

        // tree 출력
        printf("\n\nOriginal Tree:\n");
        print_tree(head->left, print_wcount, 0);
        
        printf("\n\nBalanced Tree:\n");
        balancify(head, &num, sizeof(wcount));
        print_tree(head->left, print_wcount, 0);
    }

    fclose(fp);
}

int wcount_cmp(const void *a, const void *b) {
    return strcmp(((wcount *)a)->word, ((wcount *)b)->word);
}

void print_wcount(void *t) {
    printf("%s : %d\n", ((wcount *)t)->word, ((wcount *)t)->count);
}