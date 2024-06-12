#include "stack_library.h"

int stack[MAX];
int top = -1;

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