#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int (*FCMP)(const void *a, const void *b);

// util
void swap(void *a, void *b, size_t size);
void print_list(void *base, int n_elem);
int charcmp(const void *a, const void *b);

// heap sort
void gen_down_heap(void *base, int n_heap, int p, size_t size, FCMP fcmp);
void gen_heap_sort(void *base, int n_elem, size_t size, FCMP fcmp);

// search
int bi_search(int key, int *a, int N);
int bi_insert(int key, int *a, int *N);
int bi_delete(int key, int *a, int *N);
int bi_estimation_search(int key, int *a, int N);
int gen_bi_search(void *key, void *base, int n_elem, size_t size, FCMP fcmp);
int gen_bi_insert(void *key, void *base, int *n_elem, size_t size, FCMP fcmp);
int gen_bi_delete(void *key, void *base, int *n_elem, size_t size, FCMP fcmp);

// define
#define MAX 100
#define BASE(i) ((char *)base + (i) * size)

void main() {
    char str[MAX] = "TOSORTALGORITHM";
    int size = 15;
    int pos, key;

    // sorting
    print_list(str, size);
    gen_heap_sort(str, size, sizeof(char), charcmp);
    print_list(str, size);

    // search
    key = 'S';
    pos = gen_bi_search(&key, str, size, sizeof(char), charcmp);
    printf("index %d of value %c\n", pos, str[pos]);

    // insert
    key = 'Z';
    pos = gen_bi_insert(&key, str, &size, sizeof(char), charcmp);
    print_list(str, size);

    // delete
    key = 'A';
    pos = gen_bi_delete(&key, str, &size, sizeof(char), charcmp);
    print_list(str, size);
}

// util function
void swap(void *a, void *b, size_t size) {
    void *tmp = malloc(size);

    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);

    free(tmp);
}

void print_list(void *base, int n_elem) {
    for (int i = 0; i < n_elem; i++) {
        printf("%c", *((char*)base + i));
    }
    printf("\n");
}

int charcmp(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

void gen_down_heap(void *base, int n_heap, int p, size_t size, FCMP fcmp) {
    int child;
    void *value = malloc(size);

    memcpy(value, BASE(p), size);

    while(p <= (n_heap - 2) / 2) {
        child = p * 2 + 1;

        if (child + 1 < n_heap && fcmp(BASE(child), BASE(child + 1)) < 0) child++;

        if (fcmp(value, BASE(child)) >= 0) break;

        memcpy(BASE(p), BASE(child), size);

        p = child;
    }

    memcpy(BASE(p), value, size);
    free(value);
}

void gen_heap_sort(void *base, int n_elem, size_t size, FCMP fcmp) {
    int n_heap;
    
    for(int i = (n_elem - 2) / 2 ; i >= 0 ; i--) {
        gen_down_heap(base, n_elem, i, size, fcmp);
    }
    
    n_heap = n_elem;
    while(n_heap > 1) {
        swap(BASE(0), BASE(n_heap - 1), size);
        gen_down_heap(base, --n_heap, 0, size, fcmp);
    }
}

// functions for search
int bi_search(int key, int *a, int N) {
    int left, right, mid;
    left = 0, right = N - 1;
    
    while(right >= left) {
        // mid 찾기
        mid = (right + left) / 2;

        // search
        if (key == a[mid]) return mid;
        else if (key > a[mid]) left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}

int bi_insert(int key, int *a, int *N) {
    int pos = 0;

    // key 위치 찾기 (정렬 상태 유지하기 위해)
    while(key > a[pos] && pos < *N) {
        pos++;
    }

    // 나머지 값 한 칸씩 뒤로
    for (int i = *N ; i > pos ; i--) {
        a[i] = a[i-1];
    }
    
    // 찾은 위치에 넣기
    a[pos] = key;

    // 배열 크기 증가
    (*N)++;

    return pos;
}

int bi_delete(int key, int *a, int *N) {
    int pos;
    
    // 배열에 값이 없을 때 delete 불가
    if (*N <= 0) return -1;

    // 찾고자 하는 값이 없을 때 delete 불가
    pos = bi_search(key, a, *N);
    if (pos < 0) return -1;

    // 삭제하는 경우 한 칸씩 앞으로
    for (int i = pos + 1 ; i < *N ; i++) {
        a[i-1] = a[i];
    }

    // 배열 크기 하나 감소
    (*N)--;

    return pos;
}

int bi_estimation_search(int key, int *a, int N) {
    int left, right, mid;
    left = 0, right = N - 1;

    while(right >= left) {
        // 비율을 통해 mid 위치 estimation
        mid = left + (float)(right - left) * (key - a[left]) / (a[right] - a[left]) ;

        // search
        if (key == a[mid]) return mid;
        else if (key > a[mid]) left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}

int gen_bi_search(void *key, void *base, int n_elem, size_t size, FCMP fcmp) {
    int left, right, mid;
    left = 0, right = n_elem - 1;

    while(right >= left) {
        // mid 찾기
        mid = (right + left) / 2;

        // search
        if (fcmp(key, BASE(mid)) == 0) return mid;
        else if (fcmp(key, BASE(mid)) > 0) left = mid + 1;
        else right = mid - 1;
    }
}

int gen_bi_insert(void *key, void *base, int *n_elem, size_t size, FCMP fcmp) {
    int pos = 0;

    while(fcmp(key, BASE(pos)) > 0 && pos < *n_elem) {
        pos++;
    }

    for (int i = *n_elem ; i > pos ; i--) {
        memcpy(BASE(i), BASE(i-1), size);
    }

    memcpy(BASE(pos), key, size);

    (*n_elem)++;

    return pos;
}

int gen_bi_delete(void *key, void *base, int *n_elem, size_t size, FCMP fcmp) {
    int pos;

    if (*n_elem <= 0) return -1;

    pos = gen_bi_search(key, base, *n_elem, size, fcmp);
    if (pos < 0) return -1;

    for (int i = pos + 1 ; i < *n_elem ; i++) {
        memcpy(BASE(i-1), BASE(i), size);
    }

    (*n_elem)--;

    return pos;
}
