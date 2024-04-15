#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 20

// 전역 변수 정의 (linked_list로 구현하는 경우 node로만 바꿔주기)
int stack[MAX_SIZE];
int top;

// 필요한 함수
void init_stack();
int push(int key);
int pop();
int get_stack_top();
int is_op(int key);
int precedence(int op);
void postfix(char *dst, char *src);

void main() {
    char src[] = "(1*(2+3/4)+5)/6+7";
    char dst[20];

    postfix(dst, src);
    printf("%s\n", dst);
}

void init_stack() {
    top = -1;
}

int push(int key) {
    if (top >= MAX_SIZE-1)
        return -1;

    stack[++top] = key;
    return 1;
}

int pop() {
    if (top < 0)
        return -1;

    return stack[top--];
}

int get_stack_top() {
    return (top < 0) ? -1 : stack[top];
}

int is_op(int key) {
    return (key == '+' || key == '-' || key == '*' || key == '/');
}

int precedence(int op) {
    if (op == '(')
        return 0;
    else if (op == '+' || op == '-')
        return 1;
    else if (op == '/' || op == '*')
        return 2;
    else
        return 3;
}

void postfix(char *dst, char *src) {
    char c;
    init_stack();

    while(*src) {
        // 스택에 넣어주기
        if (*src == '(') {
            push(*src);
            src++;
        }

        // 스택에서 '('를 만나기 전까지 모두 pop() 후 '(' 제거
        else if (*src == ')') {
            while(get_stack_top() != '(') {
                *dst++ = pop();
            }
            pop();
            src++;
        }

        // operation일 때는 입력되는 연산자보다 우선 순위가 높은 연산자들 pop()
        else if (is_op(*src)) {
            while ((top >= 0) && (precedence(get_stack_top()) >= precedence(*src)))
                *dst++ = pop();
            push(*src); // 이후 push()
            src++;
        }

        // 주어진 입력 범위 넣어주기 (연속된 입력을 고려하여 do-while 사용)
        else if (*src >= '0' && *src <= '9') {
            do {
                *dst++ = *src++;
            }while(*src >= '0' && *src <= '9');
        }

        // 이상한 값이면 그냥 넘기기
        else {
            src++;
        }
    }

    // 남은 스택 비워주기
    while(top >= 0)
        *dst++ = pop();

    // NULL 값 넣어주기
    *dst = 0;
}

