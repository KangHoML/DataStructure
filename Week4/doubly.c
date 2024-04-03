#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

// Struct
typedef struct _dnode {
    int key;
    struct _dnode *prev;
    struct _dnode *next;
}dnode;

// Define Head & Tail
dnode *head, *tail;

// Define all functions
void init_node();
dnode *insert_prev(int key, dnode *target);
int delete_given_dnode(dnode *target);
dnode *find_dnode(int key);
int find_index(int key);
dnode *insert_node(int t, int k);
int delete_dnode_key(int key);
dnode *insert_ordered(int key, int reverse);
void delete_all();
void print_list(dnode *current);

void main() {
    srand(time(NULL));
    init_node();

    for (int i = 0; i < 6; i++) {
        int random = rand() % 6 + 1;
        insert_ordered(random, 0);
    }
    print_list(head->next);

    delete_all();
    for (int i = 0; i < 6; i++) {
        int random = rand() % 6 + 1;
        insert_ordered(random, 1);
    }
    print_list(head->next);

    delete_all();
    insert_prev(1, tail);
    insert_node(1, 3);
    print_list(head->next);

    int index = find_index(3);
    printf("index: %d\n", index);

    delete_dnode_key(3);
    print_list(head->next);
}

void init_node() {
    head = (dnode *)calloc(1, sizeof(dnode));
    tail = (dnode *)calloc(1, sizeof(dnode));

    head->prev = head;
    head->next = tail;

    tail->prev = head;
    tail->next = tail;
}

// insert node value key before the target node
dnode *insert_prev(int key, dnode *target) {
    // target node가 head면 넣을 수 없음
    if (target == head)
        return NULL;
    
    // 새로운 방 생성
    dnode* temp = (dnode *)calloc(1, sizeof(dnode));
    
    // 방에 값 넣어주기
    temp->key = key;
    temp->prev = target->prev;
    temp->next = target;

    // 이전 방과 현재 방, 현재 방과 다음 방 이어주기
    target->prev->next = temp;
    target->prev = temp;

    return temp;
}

int delete_given_dnode(dnode *target) {
    if (target != head && target != tail) {
        target->prev->next = target->next;
        target->next->prev = target->prev;
        
        free(target);
        return 1;
    }
    else
        return -1;
}

dnode *find_dnode(int key) {
    dnode *cursor = head->next;

    while(cursor->key != key && cursor != tail) {
        cursor = cursor->next;
    } 

    return cursor;
}

int find_index(int key) {
    dnode *cursor = head->next;
    int index = 0;

    while(cursor->key != key && cursor != tail) {
        cursor = cursor->next;
        index++;
    }
    
    if (cursor != tail)
        return index;
    else
        return -1;
}

// Insert the node value k before the node value t
dnode *insert_node(int t, int k) {
    dnode* cursor = find_dnode(t);
    dnode* temp = NULL;
    
    if (cursor != tail)
        temp = insert_prev(k, cursor);
    
    return temp;
}

// Delete the node value key
int delete_dnode_key(int key) {
    dnode* cursor = find_dnode(key);
    return delete_given_dnode(cursor);
}

// Insert the node sorted
dnode *insert_ordered(int key, int reverse) {
    dnode *cursor;

    cursor = head->next;
    if (reverse == 0) {
        while(cursor->key <= key && cursor != tail)
            cursor = cursor->next;
    }
    else {
        while(cursor->key >= key && cursor != tail)
            cursor = cursor->next;
    }

    return insert_prev(key, cursor);
}

void delete_all() {
    dnode *temp, *cursor;

    cursor = head->next;
    while(cursor != tail) {
        temp = cursor;
        free(temp);
        cursor = cursor->next;
    }

    head->next = tail;
    tail->prev = head;
}

void print_list(dnode *current) {
    dnode *cursor = head->next;

    while(cursor != tail) {
        printf("%-8d", cursor->key);
        cursor = cursor->next;
    }
    printf("\n");
}
