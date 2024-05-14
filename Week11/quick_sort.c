#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100
#define SIZE 10

// for stack
int stack[MAX];
int top = -1;

void init_stack();
int push(int t);
int pop();

// for quick_sort
void swap(void *a, void *b, size_t size);
int intcmp(const void *a, const void *b);
void recur_quick_sort(int *a, int N);
void nonrecur_quick_sort(int *a, int N);
void gen_quick_sort(void *base, int n_elem, size_t size,
                    int (*fcmp)(const void *a, const void *b));
void random_quick_sort(int *a, int N);
void insert_sort(int *a, int N);
void insert_quick_sort(int *a, int N, int t);
void print_list(void *base, int n_elem);

void main() {
    srand(time(NULL));
    int number[SIZE];

    printf("--- Recursive ---\n");
    for (int i = 0; i < SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }
    print_list((void *)number, SIZE);
    recur_quick_sort(number, SIZE);
    print_list((void *)number, SIZE);

    printf("--- Non-recursive ---\n");
    for (int i = 0; i < SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }
    print_list((void *)number, SIZE);
    nonrecur_quick_sort(number, SIZE);
    print_list((void *)number, SIZE);

    printf("--- Generalized ---\n");
    for (int i = 0; i < SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }
    print_list((void *)number, SIZE);
    gen_quick_sort(number, SIZE, sizeof(int), intcmp);
    print_list((void *)number, SIZE);

    printf("--- Random Pivot ---\n");
    for (int i = 0; i < SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }
    print_list((void *)number, SIZE);
    random_quick_sort(number, SIZE);
    print_list((void *)number, SIZE);

    printf("--- With Insert ---\n");
    for (int i = 0; i < SIZE; i++) {
        number[i] = rand() % SIZE + 1;
    }
    print_list((void *)number, SIZE);
    insert_quick_sort(number, SIZE, 1);
    print_list((void *)number, SIZE);
}

// functions for stack
void init_stack() {
    top = -1;
}

int push(int t) {
    if (top >= MAX -1) return -1;
    
    stack[++top] = t;
    return t;
}

int pop() {
    if (top < 0) return -1;

    return stack[top--];
}

// functions for quick sort
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

void recur_quick_sort(int *a, int N) {
    int low, high; // index
    int pivot; // value

    // N > 1 일 때만 진행
    if (N <= 1) return;
    
    // divide
    pivot = a[N-1];
    low = -1, high = N-1;

    while(1) {
        while(a[++low] < pivot);
        while(a[--high] > pivot);

        // 1번 정렬 완료 시 break
        if (low >= high) break;

        // swap
        swap(&a[low], &a[high], sizeof(int));
    }

    // swap
    swap(&a[low], &a[N-1], sizeof(int));

    // sort partition
    recur_quick_sort(a, low);
    recur_quick_sort(a + low + 1, N - low - 1);
}

void nonrecur_quick_sort(int *a, int N) {
    int low, high; // 정렬을 위한 cursor
    int pivot; // pivot 값
    int left, right; // pop을 통한 각 partition의 인덱스 받아오기

    // stack 초기화 및 처음 partition 위치 push
    init_stack();
    left = 0, right = N-1;
    push(right);
    push(left);

    // stack에 값이 있을 때
    while(top >= 0) {
        left = pop();
        right = pop();

        // partition의 크기가 1보다 클 때만 진행
        if (right - left + 1 <= 1) continue;

        // divide
        pivot = a[right];
        low = left-1, high = right;

        while(1) {
            while(a[++low] < pivot);
            while(a[--high] > pivot);

            // 1번 정렬 완료 시 break
            if (low >= high) break;

            // swap
            swap(&a[low], &a[high], sizeof(int));
        }
        
        // swap
        swap(&a[low], &a[right], sizeof(int));

        // sort partition (stack에 push, 순서 중요) 
        push(right), push(low + 1); // right partition의 right, left
        push(low - 1), push(left); // left partition의 right, left
    }
}

void gen_quick_sort(void *base, int n_elem, size_t size,
                    int (*fcmp)(const void *a, const void *b)) {
    int low, high;
    int left, right;
    
    // stack 초기화 및 처음 partition 위치 push
    init_stack();
    left = 0, right = n_elem-1;
    push(right);
    push(left);

    while(top >= 0) {
        left = pop();
        right = pop();

        if (right - left + 1 <= 1) continue;

        // divide
        low = left-1; high = right;
    
        while(1) {
            do {
                low++;
            } while(fcmp((char *)base + low * size, (char *)base + right * size) < 0);

            do {
                high--;
            } while(fcmp((char *)base + high * size, (char *)base + right * size) > 0);
            
            if (low >= high) break;

            swap((char *)base + low * size, (char *)base + high * size, size);
        }

        swap((char *)base + low * size, (char *)base + right * size, size);

        // sort partition
        push(right); push(low + 1);
        push(low - 1); push(left);
    }    
}

void random_quick_sort(int *a, int N){
    int low, high;
    int p_i, p_v;
    int left, right; 

    init_stack();
    left = 0, right = N-1;
    push(right);
    push(left);

    while(top >= 0) {
        left = pop();
        right = pop();

        if (right - left + 1 <= 1) continue;

        p_i = rand() % (right - left + 1) + left;
        p_v = a[p_i];
        swap(&a[p_i], &a[right], sizeof(int));

        low = left - 1, high = right;

        while(1) {
            while(a[++low] < p_v);
            while(a[--high] > p_v);
            if (low >= high) break;

            swap(&a[low], &a[high], sizeof(int));
        }

        swap(&a[low], &a[right], sizeof(int));

        push(right), push(low + 1);
        push(low - 1), push(left);
    }
}

void insert_sort(int *a, int N) {
    int j, temp;

    for (int i = 1; i < N; i++) {
        temp = a[i];
        j = i;
        while(j > 0 && a[j-1] > temp) {
            a[j] = a[j-1];
            j--;
        }
        a[j] = temp;
    }
}

void insert_quick_sort(int *a, int N, int t){
    int low, high;
    int p_i, p_v;
    int left, right; 

    init_stack();
    left = 0, right = N-1;
    push(right);
    push(left);

    while(top >= 0) {
        left = pop();
        right = pop();

        if (right - left + 1 <= t) insert_sort(a + left, right - left + 1);
        else {
            p_i = rand() % (right - left + 1) + left;
            p_v = a[p_i];
            swap(&a[p_i], &a[right], sizeof(int));

            low = left - 1, high = right;
            while(1) {
                while(a[++low] < p_v);
                while(a[--high] > p_v);
                if (low >= high) break;

                swap(&a[low], &a[high], sizeof(int));
            }

            swap(&a[low], &a[right], sizeof(int));

            push(right), push(low + 1);
            push(low - 1), push(left);
        }
    }
}

void print_list(void *base, int n_elem) {
    for (int i = 0; i < n_elem; i++) {
        printf("%-5d", *((int*)base + i));
    }
    printf("\n");
}