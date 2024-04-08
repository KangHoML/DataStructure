#include <stdio.h>
#include <stdlib.h>

typedef struct _dnode {
    int key;
    struct _dnode *prev;
    struct _dnode *next;
}dnode;

dnode *head, *tail;

void init_queue();
int put(int key);
int get();
void clear_queue();
void print_queue();

void main() {
    int k;
    init_queue();
    
    put(3);
    put(6);
    put(9);
    put(1);
    put(6);
    put(3);
    print_queue();

    get();
    print_queue();

    put(4);
    put(8);
    put(7);
    put(2);
    put(0);
    print_queue();

    init_queue();
    get(); // stack underflow
}

void init_queue() {
    head = (dnode *)calloc(1, sizeof(dnode));
    tail = (dnode *)calloc(1, sizeof(dnode));

    head->prev = head;
    head->next = tail;
    tail->prev = head;
    tail->next = tail;
}

// 먼저 넣은 것이 head와 가까울 수 있도록 tail 바로 앞에 넣어주기
int put(int key) {
    dnode *temp;

    if ((temp = (dnode *)malloc(sizeof(dnode))) == NULL) {
        printf("Out of Memory !\n");
        return -1;
    }

    // 값 넣어주기
    temp->key = key;
    
    // temp와 이전 노드 연결
    temp->prev = tail->prev;
    tail->prev->next = temp;

    // temp와 tail 연결
    tail->prev = temp;
    temp->next = tail;

    return key;
}

// 먼저 넣은 것이 먼저 나올 수 있도록 head에 가까운 것부터 꺼내기
int get() {
    dnode *temp = head->next;
    int key;
    if (temp == tail) {
        printf("Queue Underflow !\n");
        return -1;
    }

    // 값 꺼내기
    key = temp->key;

    // 이전 노드와 다음 노드 이어주기
    head->next = temp->next;
    temp->next->prev = head;

    // 메모리 해제
    free(temp);

    return key;
}

// queue 비워주기
void clear_queue() {
    dnode *temp, *cursor;
    
    cursor = head->next;
    while(cursor != tail) {
        temp = cursor;
        cursor = cursor->next;
        free(temp);
    }

    head->next = tail;
    tail->prev = head;
}

// 전체 queue 출력
void print_queue() {
    dnode *cursor = head->next;
    while(cursor != tail) {
        printf("%-6d", cursor->key);
        cursor = cursor->next;
    }
    printf("\n");
}

