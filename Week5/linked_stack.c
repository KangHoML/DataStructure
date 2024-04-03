#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

// Structure
typedef struct _node {
    int key;
    struct _node *next;
}node;

// global variables
node *head, *tail;

// Define all functions
void init_stack();
int push(int key);
int pop();
void clear();
void print_stack();
void example();
void calc();

void main() {
    // example();
    calc();
}

void init_stack() {
    head = (node *)calloc(1, sizeof(node));
    tail = (node *)calloc(1, sizeof(node));

    head->next = tail;
    tail->next = tail;
}

int push(int key) {
    node *temp;

    if((temp = (node *)malloc(sizeof(node))) == NULL) {
        printf("Out of Memory !\n");
        return -1;
    }

    temp->key = key;
    temp->next = head->next;
    head->next = temp;

    return key;
}

int pop() {
    node *temp;
    int key;

    if (head->next == tail){
        printf("Stack Underflow !\n");
        return -1;
    }

    temp = head->next;
    key = temp->key;

    head->next = temp->next;
    free(temp);

    return key;
}

void clear() {
    node *target, *cursor;

    cursor = head->next;
    while(cursor != tail) {
        target = cursor;
        cursor = cursor->next;
        free(target);
    }

    head->next = tail;
}

void print_stack() {
    node *cursor = head->next;

    while(cursor != tail) {
        printf("%-6d", cursor->key);
        cursor = cursor->next;
    }
    printf("\n");
}

void example() {
    int k;
    init_stack();

    push(3);
    push(6);
    push(9);
    push(1);
    push(6);
    push(3);
    print_stack();

    pop();
    print_stack();

    push(4);
    push(8);
    push(7);
    push(2);
    push(0);
    print_stack();

    init_stack();
    pop(); // stack underflow

}

void calc() {
    char equation[30];
    int i = 0;
    int operator;

    printf("input equation: ");
    scanf("%s", equation);

    init_stack();
    clear();

    while(equation[i] != '\0') {
        if (equation[i] >= 'A' && equation[i] <= 'Z') {
            printf("%c", equation[i]);
        }
        else if ((equation[i] == '+') || (equation[i] == '-') || (equation[i] == '*') || (equation[i] == '/')){
            push(equation[i]);
        }

        if (equation[i] == ')') {
            printf("%c", pop());
        }
        i++;
    }

    // 남은 stack 비워주기
    while(head->next != tail)
        printf("%c", pop());


    printf("\n");
}