#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10

void swap(void *a, void *b, size_t size);
int intcmp(const void *a, const void *b);
void up_heap(int *a, int heap_size);
void down_heap(int *a, int heap_size, int parent);
void insert(int *a, int *heap_size, int value);
int extract(int *a, int *heap_size);
void up_heap_sort(int *a, int N);
void down_heap_sort(int *a, int N);
void gen_insert(void *a, int *heap_size, void *b, size_t size,
                 int (*fcmp)(const void *a, const void *b));
void gen_extract(void *a, int *heap_size, void *b, size_t size,
                 int (*fcmp)(const void *a, const void *b));
void gen_heap_sort(void *base, int n_elem, size_t size,
                    int (*fcmp)(const void *a, const void *b));
void print_list(void *base, int n_elem);

void main() {
    srand(time(NULL));
    int number[SIZE + 1];
    number[0] = 0;

    printf("--- Top-down ---\n");
    for (int i = 1; i <= SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }
    print_list((void *)number, SIZE);
    up_heap_sort(number, SIZE);
    print_list((void *)number, SIZE);

    printf("--- Bottom-up ---\n");
    for (int i = 1; i <= SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }
    print_list((void *)number, SIZE);
    down_heap_sort(number, SIZE);
    print_list((void *)number, SIZE);

    printf("--- Generalized ---\n");
    for (int i = 0; i < SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }
    print_list((void *)number, SIZE);
    gen_heap_sort(number, SIZE, sizeof(int), intcmp);
    print_list((void *)number, SIZE);

}

// functions for heap sort
void swap(void *a, void *b, size_t size) {
    void *temp = malloc(size);

    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    
    free(temp);
}

int intcmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void up_heap(int *a, int heap_size) {
    int v, i;
    v = a[heap_size], i = heap_size;
    a[0] = __INT_MAX__;

    // leaf 노드 값 < parent node 이 될 때까지 업데이트
    while(a[i/2] <= v) {
        a[i] = a[i/2];
        i /= 2;
    }
    a[i] = v;
}

void down_heap(int *a, int heap_size, int parent) {
    int v, child;
    v = a[parent];

    while(parent <= heap_size / 2) {
        child = parent * 2;

        // left_child < right_child 인 경우
        if (child < heap_size && a[child] < a[child + 1]) child++;
        
        // root node에 있던 값이 더 큰 경우
        if (v >= a[child]) break;

        // 교환 및 parent node 업데이트
        a[parent] = a[child];
        parent = child;
    }

    // 현재 위치에 넣기
    a[parent] = v;
}

void insert(int *a, int *heap_size, int value) {
    a[++(*heap_size)] = value;
    up_heap(a, *heap_size);
}

int extract(int *a, int *heap_size) {
    int value = a[1]; // root node 값

    a[1] = a[(*heap_size)--]; // leaf node 값 root node로 옮기기
    down_heap(a, *heap_size, 1);

    return value;
}

void up_heap_sort(int *a, int N) {
    int heap_size = 0;
    
    for (int i = 1; i <= N; i++) {
        insert(a, &heap_size, a[i]);
    }

    for (int i = heap_size; i > 0; i--) {
        a[i] = extract(a, &heap_size);
    }
}

void down_heap_sort(int *a, int N) {
    int heap_size, value;

    // heap 구성
    for (int i = N / 2; i > 0; i--) {
        down_heap(a, N, i);
    }

    heap_size = N;
    while(heap_size > 1) {
        swap(&a[1], &a[heap_size], sizeof(int)); // 처음과 마지막 노드 교체
        
       down_heap(a, --heap_size, 1);
    }
}

void gen_insert(void *a, int *heap_size, void *b, size_t size,
                int (*fcmp)(const void *a, const void *b)) {
    int i;

    // leaf 노드에 값 추가
    (*heap_size)++;
    memcpy((char *)a + (*heap_size) * size, b, size); // a[*heap_size] = b;
    
    // up heap 구현
    i = *heap_size;
    while(i > 1 && fcmp((char *)a + (i / 2) * size, b) <= 0) {
        memcpy((char *)a + i * size, (char *)a + (i/2) * size, size);
        i /= 2;
    }
    memcpy((char *)a + i * size, b, size);
}

void gen_extract(void *a, int *heap_size, void *b, size_t size,
                int (*fcmp)(const void *a, const void *b)) {
    int child, parent;

    // root 노드 값
    memcpy(b, (char *)a + size, size); // b = a[1]
    
    // leaf node 값 -> root node
    memcpy((char *)a + size, (char *)a + (*heap_size) *size, size);
    (*heap_size)--;

    // down heap 구현
    parent = 1;
    
    void *v = malloc(size);
    memcpy(v, (char *)a + parent * size, size);
    
    while(parent <= *heap_size / 2) {
        child = parent * 2;

        // left_child < right_child 인 경우
        if (child < *heap_size && fcmp((char *)a + child * size, (char *)a + (child + 1) * size) < 0)
            child++;
        
        // v >= a[child] 인 경우
        if (fcmp(v, (char *)a + child * size) >= 0) break;

        // 교환 및 parent 업데이트
        memcpy((char *)a + parent * size, (char *)a + child * size, size);
        parent = child;
    }
    memcpy((char *)a + parent * size, v, size);
    free(v);
}

void gen_heap_sort(void *base, int n_elem, size_t size,
                    int (*fcmp)(const void *a, const void *b)) {
    int heap_size = 0;
    void *value = malloc(size);

    for (int i = 1; i <= n_elem; i++) {
        memcpy(value, (char *)base + i * size, size);
        gen_insert(base, &heap_size, value, size, fcmp);
    }

    for (int i = heap_size; i > 0; i--) {    
        gen_extract(base, &heap_size, value, size, fcmp);
        memcpy((char*)base + i * size, value, size);
    }

    free(value);
}

void print_list(void *base, int n_elem) {
    for (int i = 1; i <= n_elem; i++) {
        printf("%-5d", *((int*)base + i));
    }
    printf("\n");
}