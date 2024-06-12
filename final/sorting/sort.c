#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort_library.h"

#define SIZE 10

void main() {
    int src[SIZE+1], dst[SIZE+1];
    
    printf("--- Original ---\n");
    for (int i = 0; i < SIZE; i++) {
        src[i] = rand() % SIZE + 1;
    }
    print_int(src, SIZE);
    
    printf("--- Select ---\n");
    sort(dst, src, SIZE, sizeof(int), intcmp, select_sort);
    print_int(dst, SIZE);

    printf("--- Bubble ---\n");
    sort(dst, src, SIZE, sizeof(int), intcmp, bubble_sort);
    print_int(dst, SIZE);

    printf("--- Insert ---\n");
    sort(dst, src, SIZE, sizeof(int), intcmp, insert_sort);
    print_int(dst, SIZE);

    printf("--- Shell ---\n");
    sort(dst, src, SIZE, sizeof(int), intcmp, shell_sort);
    print_int(dst, SIZE);

    printf("--- Quick ---\n");
    sort(dst, src, SIZE, sizeof(int), intcmp, quick_sort);
    print_int(dst, SIZE);

    printf("--- Up Heap Sort ---\n");
    sort(dst, src, SIZE, sizeof(int), intcmp, up_heap_sort);
    print_int(dst, SIZE);

    printf("--- Down Heap Sort ---\n");
    sort(dst, src, SIZE, sizeof(int), intcmp, dn_heap_sort);
    print_int(dst, SIZE);
}