#include <stdio.h>
#include <stdlib.h>

// tree를 위한 구조체 정의 
typedef struct _dnode {
    int key;
    struct _dnode* left;
    struct _dnode* right;
}dnode;

// stack을 위한 구조체 정의
typedef struct _node {
    dnode* data;
    struct _node* next;
}node;

// 전역변수 선언
node* head, * tail;
dnode* root, * leaf;

// stack 관련 함수 선언
void init_stack();
int push(dnode* t);
dnode* pop();

// tree 관련 함수 선언
void init_tree();
void make_tree();
void recur_inorder(dnode* t);
void nonrecur_inorder(dnode* t);

void main() {
    init_tree();
    make_tree();

    recur_inorder(root->right);
    printf("\n");

    nonrecur_inorder(root->right);
    printf("\n");
}

void init_stack() {
    head = (node*)calloc(1, sizeof(node));
    tail = (node*)calloc(1, sizeof(node));

    head->next = tail;
    tail->next = tail;
}

int push(dnode* t) {
    node* temp;

    if ((temp = malloc(sizeof(node))) == NULL)
        return -1;

    temp->next = head->next;
    temp->data = t;

    head->next = temp;
}

dnode* pop() {
    node* temp;
    dnode* t;

    if (head->next == tail)
        return NULL;

    temp = head->next;
    t = temp->data;

    head->next = temp->next;
    free(temp);

    return t;
}

void init_tree() {
    root = (dnode*)calloc(1, sizeof(dnode));
    leaf = (dnode*)calloc(1, sizeof(dnode));

    root->left = leaf;
    root->right = leaf;

    leaf->left = leaf;
    leaf->right = leaf;
}

void make_tree() {
    // 노드 생성
    dnode **nodes = malloc(9 * sizeof(dnode*));;

    for (int i = 0; i < 9; i++) {
        dnode *new_node = (dnode*)malloc(sizeof(dnode));
        
        new_node->key = i;
        new_node->left = leaf;
        new_node->right = leaf;
        
        nodes[i] = new_node;
    }

    // 트리 구조 설정
    root->right = nodes[0];
    
    nodes[0]->left = nodes[1];
    nodes[0]->right = nodes[2];

    nodes[1]->left = nodes[3];
    nodes[1]->right = nodes[4];

    nodes[3]->left = nodes[6];
    nodes[3]->right = nodes[7];

    nodes[2]->right = nodes[5];

    nodes[5]->right = nodes[8];
}

void recur_inorder(dnode* t) {
    if (t == leaf) return;
    recur_inorder(t->left); // 왼쪽 탐색
    printf("%-3c", 'A' + t->key); 
    recur_inorder(t->right); // 오른쪽 탐색
}

void nonrecur_inorder(dnode *t) {
    init_stack();

    // 왼쪽 맨 마지막 leaf에 도달할 때까지 stack에 push
    while(t != leaf) {
        push(t);
        t = t->left;
    }

    // stack이 빌 때까지 탐색 진행
    while(1) {
        if ((t = pop()) == NULL)
            break;

        // 현재 값 출력
        printf("%-3c", 'A' + t->key); 

        // 오른쪽 노드에 값이 있으면 왼쪽 노드에 도달할 때까지 stack에 push
        if (t->right != leaf) {
            t = t->right;
            while(t != leaf) {
                push(t);
                t = t->left;
            }
        }
    }
}