#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

// stack 크기
#define MAX 100

// tree 구조체 정의
typedef struct _dnode {
    char key;
    struct _dnode *left;
    struct _dnode *right;
}node;

// queue 구조체 정체
typedef struct _queue {
    node* data;
    struct _queue *prev;
    struct _queue *next;
}q;

// stack 정의
node* stack[MAX];

// 전역 변수 정의
node *root, *leaf;
q *head, *tail;
int top;

// 스택을 위한 함수 정의
void init_stack();
int push(node* t);
node* pop();

// 큐를 위한 함수 정의
void init_queue();
int put(node* t);
node* get();

// postfix를 위한 함수
void init_tree();
int is_operator(int op);
node* make_parse_tree(char *p);

// traverse 함수
void preorder(node *t);
void inorder(node *t);
void postorder(node *t);
void levelorder(node *t);

void main() {
    char exp[256];
    while(1) {
        init_stack();
        init_queue();
        init_tree();
    
        printf("\n\nInput Postfix Expression: ");
        scanf("%s", exp);

        if (*exp == 'q')
            break;

        root->right = make_parse_tree(exp);

        printf("\nPre-order Traverse: ");
        preorder(root->right);

        printf("\nIn-order Traverse: ");
        inorder(root->right);

        printf("\nPost-order Traverse: ");
        postorder(root->right);

        printf("\nLevel-order Traverse: ");
        levelorder(root->right);
    }

}

// ------------ Stack ---------------
void init_stack() {
    top = -1;
}

int push(node *t) {
    if (top >= MAX - 1)
        return -1;
    
    stack[++top] = t;
    return 1;
}

node* pop() {
    node *t;
    if (top < 0)
        return NULL;
    
    t = stack[top--];
    return t;
}

// ------------ Queue ---------------
void init_queue() {
    head = (q *)calloc(1, sizeof(q));
    tail = (q *)calloc(1, sizeof(q));

    head->prev = head;
    head->next = tail;

    tail->prev = head;
    tail->next = tail;
}

int put(node* t) {
    q* temp;

    if ((temp = malloc(sizeof(q))) == NULL)
        return -1;

    temp->data = t;
    temp->next = tail;
    temp->prev = tail->prev;
    
    tail->prev->next = temp;
    tail->prev = temp;
}

node* get() {
    q* temp;
    node* t;

    if (head->next == tail)
        return NULL;

    temp = head->next;
    t = temp->data;

    head->next = temp->next;
    temp->next->prev = head;
    free(temp);

    return t;
}

// ------------ Tree ---------------
void init_tree() {
    root = (node *)calloc(1, sizeof(node));
    leaf = (node *)calloc(1, sizeof(node));

    root->left = leaf;
    root->right = leaf;

    leaf->left = leaf;
    leaf->right = leaf;
}

int is_operator(int op) {
    return (op == '+' || op == '-' || op == '*' || op == '/');
}

node* make_parse_tree(char* p) {
    node *t;

    while(*p) {
        // 새로운 노드 생성
        t = (node *)calloc(1, sizeof(node));
        t->key = *p;
        t->left = leaf;
        t->right = leaf;

        // 연산자라면 오른쪽 자식노드 먼저 입력
        if (is_operator(*p)) {
            t->right = pop();
            t->left = pop();
        }

        // 연산자가 아니면 스택에 그냥 넣어주고, 연산자면 위에 작업 이후 넣어주기
        push(t);
        p++;
    }

    return pop(); // root 노드 반환
}

void preorder(node* t) {
    if (t == leaf) return;
    printf("%-2c", t->key);
    preorder(t->left); // 왼쪽 탐색
    preorder(t->right); // 오른쪽 탐색
}

void inorder(node* t) {
    if (t == leaf) return;
    inorder(t->left); // 왼쪽 탐색
    printf("%-2c", t->key);
    inorder(t->right); // 오른쪽 탐색
}

void postorder(node* t) {
    if (t == leaf) return;
    inorder(t->left); // 왼쪽 탐색
    inorder(t->right); // 오른쪽 탐색
    printf("%-2c", t->key);
}

void levelorder(node *t) {
    put(t);

    while(1) {
        // queue가 빌 때까지 반복
        if ((t = get()) == NULL)
            break;
        
        // 현재 pop()한 값 출력
        printf("%-2c", t->key); 

        // 왼쪽 먼저 queue에 삽입
        if (t->left != leaf)
            put(t->left);
        
        // 다음 오른쪽 queue에 삽입
        if (t->right != leaf)
            put(t->right);
    }
}