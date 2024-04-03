#include <stdio.h>

// max stack size
#define MAX 10

// global variable
int stack[MAX];
int top;

void init_stack();
int push(int t);
int pop();
void print_stack();
void print_and_pop();

void main() {
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
    print_stack(); // stack overflow

    init_stack();
    pop(); // stack underflow
}

void init_stack() {
    top = -1;
}

int push(int t) {
    if (top >= MAX-1) {
        printf("Stack Overflow !\n");
        return -1;
    }

    stack[++top] = t;
    return t;
}

int pop() {
    if (top < 0) {
        printf("Stack Underflow !\n");
        return -1;
    }

    return stack[top--];
}

void print_stack() {
    int temp = top;
    while(temp >= 0) {
        printf("%-8d", stack[temp--]);
    }
    printf("\n");
}
