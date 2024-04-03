#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Struct
typedef struct _node {
    int key;
    struct _node *next;
}node;

// Define Head & Tail
node *head, *tail;

// Define all functions
void init_node();
node *insert_next(int key, node *current);
int delete_next(node *current);
node *find_node(int key);
int find_index(int key);
node *insert_node(int t, int k);
node *insert_ordered(int key, int reverse);
int delete_node(int key);
node *delete_all();
void print_list(node *current);

// Define functions for test
void test1(), test2();

void main() {
    srand(time(NULL));
    init_node();

    test1();
    test2();
}

// Initialize simple linked list
void init_node() {
    head = (node *)calloc(1, sizeof(node));
    tail = (node *)calloc(1, sizeof(node));

    head->next = tail;
    tail->next = tail;
}

// Insert a new node after current node
node *insert_next(int key, node *current) {
    // 방 만들기
    node *target = (node *)calloc(1, sizeof(node));

    // 만든 방에 값 넣어주기
    target->key = key;
    target->next = current->next;

    // 현재 방과 이어주기
    current->next = target;

    return target;
}

// Delete the next node of current node
int delete_next(node *current) {
    node* target;

    // 다음 방이 끝 방(tail)인지 확인
    if (current->next == tail) {
        return -1;
    }

    // 제거할 방 다음 방과 현재 방을 이어주기
    target = current->next;
    current->next = target->next;

    // 방 제거(메모리 해제)
    free(target);
    return 1;
}

// Find and return the node by key value
node *find_node(int key) {
    // 처음 방부터 찾기
    node *target = head->next;

    // 방 안의 값이 key거나 끝방일 때까지 다음 방으로 이동
    while (target->key != key && target != tail) {
        target = target->next;
    }

    // 찾았을 경우 찾은 방을, 그렇지 않은 경우 tail을 반환
    return target;
}

// Find the node by key value and return index
int find_index(int key) {
    // 처음 방부터 찾기
    node *target = head->next;
    int index = 0;

    // 방 안의 값이 key거나 끝방일 때까지 다음 방으로 이동
    while (target->key != key && target != tail) {
        target = target->next;
        index++;
    }

    // 못 찾은 경우 -1, 찾은 경우 해당 인덱스 반환
    if (target == tail)
        return -1;
    else
        return index;
}

// Insert the node value k before the node value t
node *insert_node(int t, int k) {
    node *prev, *current, *target;
    
    // t 값을 가진 방 찾기
    prev = head;
    current = head->next;
    while(current->key != t && current != tail) {
        prev = current; // 이전 방
        current = current->next;
    }

    if (current != tail) {
        // 새로운 방 만들기
        target = (node *)calloc(1, sizeof(node));

        // 새로운 방에 값 넣어주기
        target->key = k;
        target->next = current;

        // 새로운 방을 찾은 방 이전 방과 이어주기
        prev->next = target;
    }

    // t 값을 가진 방이 없는 경우 tail, 있는 경우 해당 방을 반환
    return prev->next;
}

// Insert the node sorted
node *insert_ordered(int key, int reverse) {
    node *prev, *cursor;

    // key 값을 가진 방이 들어갈 위치 찾기
    prev = head;
    cursor = head->next;
    if (reverse == 0) {
        while(cursor->key <= key && cursor != tail) {
            prev = cursor;
            cursor = cursor->next;
        }
    }
    else {
        while(cursor->key >= key && cursor != tail) {
            prev = cursor;
            cursor = cursor->next;
        }

    }
    
    // 찾은 방 다음 방에 삽입
    insert_next(key, prev);

    return prev->next;
}

// Delete the node by key value
int delete_node(int key) {
    node *prev, *target;

    // key 값을 가진 방 찾기
    target = head->next;
    while(target->key != key && target != tail) {
        prev = target;
        target = target->next;
    }

    // key 값을 가진 방이 없다면 -1 반환
    if (target == tail)
        return -1;

    // 제거할 방 이전 방을 제거할 방 다음 방과 이어주기
    prev->next = target->next;
    free(target);

    return 1;
}

// Delete all node
node *delete_all(){
    node *cursor, *target;

    cursor = head->next;
    while(cursor != tail) {
        target = cursor;
        cursor = cursor->next; 
        free(target);
    }

    // 방을 제거하는 과정에서 head의 next가 끊겼으므로 이를 tail과 이어줌
    head->next = tail;
    return head;
}

// Print out the list after the current node
void print_list(node *current) {
    while(current != tail) {
        printf("%-8d", current->key);
        current = current->next;
    }
    printf("\n");
}

// test 1
void test1() {
    printf("------test1------\n");
    node *temp = head;
    for (int i = 0; i < 5; i++) {
        insert_next(i+1, temp);
        temp = temp->next;
    }
    print_list(head->next);
    
    temp = find_node(3);
    int index = find_index(3);
    if (temp == tail)
        printf("failed to find\n");
    else
        printf("index %d\n", index);

    if (delete_next(temp) == -1)
        printf("failed to delete\n");
    print_list(head->next);

    insert_node(5, 11);
    print_list(head->next);
    delete_node(2);
    print_list(head->next);

}

// test 4
void test2() {
    printf("\n------test2------\n");
    delete_all();
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
}
