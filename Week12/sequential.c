#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

// define
#define MAX 100
#define BASE(i) ((char *)base + (i) * size)
typedef int (*FCMP)(const void *, const void *);

// sequential search
int search(int key, int *a, int *num);
int insert(int key, int *a, int *num);
int delete(int key, int *a, int *num);
int f_search(int key, int *a, int *num);

// generalized version for search
int gen_search(void *key, void *base, int *num, size_t size, FCMP fcmp);
int gen_insert(void *key, void *base, int *num, size_t size, FCMP fcmp);
int gen_delete(void *key, void *base, int *num, size_t size, FCMP fcmp);
int gen_f_search(void *key, void *base, int *num, size_t size, FCMP fcmp);

// util function
void print_list(void *base, int n_elem);
int intcmp(const void *a, const void *b);
int cardcmp(const void *a, const void *b);

// struct
typedef struct _card{
    int no;
    char name[20];
}card;

void example1() {
    int number[MAX], key, t;
    int nitem = 10;

    for (int i = 0; i < nitem; i++) {
        number[i] = rand() % nitem + 1;
    }
    print_list(number, nitem);

    // search
    key = rand() % nitem + 1;
    printf("searched key: %d\n", key);

    t = search(key, number, &nitem);
    if (t > -1) {
        printf("searched index: %d\n", t);
    }
    
    // insert
    key = 8;
    t = insert(key, number, &nitem);
    if (t > -1) {
        printf("inserted key: %d\n", key);
        print_list(number, nitem);
    }

    // delete
    key = rand() % nitem + 1;
    printf("deleted key: %d\n", key);
    
    t = delete(key, number, &nitem);
    if (t > -1) {
        print_list(number, nitem);
    }

    // f_search
    key = rand() % nitem + 1;
    printf("searched key: %d\n", key);
    
    t = f_search(key, number, &nitem);
    if (t > -1) {
        print_list(number, nitem);
    }
}

void example2() {
    card table[MAX], key;
    int t, c;
    int nitem = 0;

    // menu
    do {
        printf("input command (1: search / 2. insert / 3. delete / 4. f_search / 5. quit): ");
        scanf("%d", &c);

        switch(c) {
            case 1:
                printf("input no: ");
                scanf("%d", &(key.no));

                t = gen_search(&key, table, &nitem, sizeof(card), cardcmp);
                if (t > -1) {
                    printf("searched id: %d / searched name: %s\n", (table[t]).no, (table[t]).name);
                }

                break;

            case 2:
                printf("input no: ");
                scanf("%d", &(key.no));
                printf("input name: ");
                scanf("%s", key.name);

                t = gen_insert(&key, table, &nitem, sizeof(card), cardcmp);
                if (t > -1) {
                    printf("inserted id: %d / inserted name: %s\n", (table[t]).no, (table[t]).name);
                }

                break;
            
            case 3:
                printf("input no: ");
                scanf("%d", &(key.no));

                t = gen_delete(&key, table, &nitem, sizeof(card), cardcmp);
                if (t > -1) {
                    printf("deleted id: %d / deleted name: %s\n", key.no, key.name);
                }

                break;

            case 4:
                printf("input no: ");
                scanf("%d", &(key.no));

                t = gen_f_search(&key, table, &nitem, sizeof(card), cardcmp);
                if (t > -1) {
                    printf("searched index: %d\n", t);
                    printf("front id: %d / front name: %s\n", (table[0]).no, (table[0]).name);
                }
                break;
        }
    } while(c < 5);
}

void main() {
    srand(time(NULL));
    // example1();
    example2();
}

// functions for sequential search
int search(int key, int *a, int *num) {
    int i = 0;
    while(a[i] != key && i < *num) i++;

    return (i < *num ? i : -1);
}

int insert(int key, int *a, int *num) {
    // 예외 처리
    if (*num >= MAX) return -1;

    a[(*num)++] = key;
    
    return *num - 1;
}

int delete(int key, int *a, int *num) {
    int p;
    p = search(key, a, num);
    
    // 예외 처리
    if (*num < 0 || p < 0) return -1;
    
    for(int j = p + 1; j < *num; j++) {
        a[j-1] = a[j];
    }
    
    (*num)--;

    return p;
}

int f_search(int key, int *a, int *num) {
    int p;
    p = search(key, a, num);

    // 예외 처리
    if (p < 0) return -1;

    for(int i = p - 1; i >= 0; i--) {
        a[i + 1] = a[i];
    }
    a[0] = key;

    return 0;
}

// functions for generalized version
int gen_search(void *key, void *base, int *num, size_t size, FCMP fcmp) {
    int i = 0;
    while(fcmp(BASE(i), key) != 0 && i < *num) i++;
    
    return (i < *num ? i : -1);
}

int gen_insert(void *key, void *base, int *num, size_t size, FCMP fcmp) {
    if (*num >= MAX) return -1;

    memcpy(BASE((*num)++), key, size);

    return *num - 1;
}

int gen_delete(void *key, void *base, int *num, size_t size, FCMP fcmp) {
    int p;
    p = gen_search(key, base, num, size, fcmp);
    
    // 예외처리
    if (*num < 0 || p < 0) return -1;

    for (int i = p + 1; i < *num; i++) {
        memcpy(BASE(i-1), BASE(i), size);
    }

    (*num)--;

    return p;
}

int gen_f_search(void *key, void *base, int *num, size_t size, FCMP fcmp) {
    int p;
    p = gen_search(key, base, num, size, fcmp);

    // 예외처리
    if (p < 0) return -1;

    for (int i = p-1; i >= 0; i--) {
        memcpy(BASE(i+1), BASE(i), size);
    }
    memcpy(BASE(0), key, size);

    return 0;
}

// util functions
void print_list(void *base, int n_elem) {
    for (int i = 0; i < n_elem; i++) {
        printf("%-5d", *((int*)base + i));
    }
    printf("\n");
}

int intcmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int cardcmp(const void *a, const void *b) {
    return(((card *)a)->no - ((card *)b)->no);
}
