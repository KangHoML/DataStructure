#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

typedef struct _cnode {
    int key;
    struct _cnode *next;
}cnode;

// Define Head
cnode *head;

// Define all functions
void init_node();
void insert_nodes(int k);
int delete_next(cnode *current);
cnode *find_node(int key);
int find_index(int key);
void circular(int target, int interval);
void print_list(cnode *current);

// functions for test
void test1(), test2();

void main() {
    init_node();

    test1();
    // test2();
}

// Initialize circular linked list
void init_node() {
    head = (cnode *)calloc(1, sizeof(cnode));

    head->next = head;
}

// Insert nodes number of k
void insert_nodes(int k) {
    cnode *start = head;
    for (int i = 0; i < k; i++) {
        start->next = (cnode *)calloc(1, sizeof(cnode));
        start = start->next;
        start->key = i;
    }
    start->next = head;
}

// Delete nodes after current node
int delete_next(cnode *current) {
    cnode *target;
    if (current->next == head)
        return -1;
    target = current->next;
    current->next = target->next;

    free(target);
    return 1;
}

// Find and return the node by key value
cnode *find_node(int key) {
    cnode *cursor = head->next;

    while(cursor->key != key && cursor != head) {
        cursor = cursor->next;
    }

    return cursor;
}

// Find the node by key value and return index
int find_index(int key) {
    cnode *cursor = head->next;
    int index = 0;

    while(cursor->key != key && cursor != head) {
        cursor = cursor->next;
        index++;
    }

    if (cursor == head)
        return -1;
    else
        return index;
}

// Select a target with an interval
void circular(int target, int interval) {
    cnode *cursor;

    insert_nodes(target);
    print_list(head->next);

    cursor = head->next;
    while(cursor != cursor->next->next) {
        for (int i = 0; i < interval-1; i++) {
            cursor = cursor->next;

            // 현재 cursor가 head면 건너뛰기
            if (cursor == head)
                cursor = cursor->next;
        }

        // 제거 대상이 head인 경우 cursor를 head로 옮기기
        if (cursor->next == head)
            cursor = cursor->next;

        printf("%-8c", 'A' + cursor->next->key);
        delete_next(cursor);
    }
    
    // 마지막 값 제거
    printf("%-8c\n", 'A' + cursor->next->key);
    delete_next(cursor);
}

// Print out the list after the current node
void print_list(cnode *current) {
    while(current != head) {
        printf("%-8c", 'A' + current->key);
        current = current->next;
    }

    printf("\n");
}

void test1() {
    int target, interval;

    printf("Enter target & interval: ");
    scanf("%d %d", &target, &interval);

    circular(target, interval);
}

void test2() {
    insert_nodes(10);
    print_list(head->next);
    
    cnode *temp = find_node(3);
    int index = find_index(3);
    delete_next(temp);
    print_list(head->next);

}