#include <stdio.h>
#include <stdlib.h>

#define MAX 100

extern int stack[MAX];
extern int top;

void init_stack();
int push(int t);
int pop();