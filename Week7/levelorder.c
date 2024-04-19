#include <stdio.h>
#include <stdlib.h>

// tree를 위한 구조체 정의 
typedef struct _dnode {
    int key;
    struct _dnode* left;
    struct _dnode* right;
}dnode;

// queue를 위한 구조체 정의
typedef struct _node {
    dnode* data;
    struct _node* prev;
    struct _node* next;
}q;

// 전역변수 선언
q* head, * tail;
dnode* root, * leaf;

// stack 관련 함수 선언
void init_queue();
int put(dnode* t);
dnode* get();

// tree 관련 함수 선언
void init_tree();
void make_tree();
void levelorder();

void main() {
    init_tree();
    make_tree();

    levelorder(root->right);
    printf("\n");
}

void init_queue() {
    head = (q *)calloc(1, sizeof(q));
    tail = (q *)calloc(1, sizeof(q));

    head->prev = head;
    head->next = tail;

    tail->prev = head;
    tail->next = tail;
}

int put(dnode* t) {
    q* temp;

    if ((temp = malloc(sizeof(q))) == NULL)
        return -1;

    temp->data = t;
    temp->next = tail;
    temp->prev = tail->prev;
    
    tail->prev->next = temp;
    tail->prev = temp;
}

dnode* get() {
    q* temp;
    dnode* t;

    if (head->next == tail)
        return NULL;

    temp = head->next;
    t = temp->data;

    head->next = temp->next;
    temp->next->prev = head;
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
    dnode** nodes = malloc(9 * sizeof(dnode*));;

    for (int i = 0; i < 9; i++) {
        dnode* new_node = (dnode*)malloc(sizeof(dnode));

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

void levelorder(dnode *t) {
    init_queue();
    put(t);

    while(1) {
        // queue가 빌 때까지 반복
        if ((t = get()) == NULL)
            break;
        
        // 현재 pop()한 값 출력
        printf("%-3c", 'A' + t->key); 

        // 왼쪽 먼저 queue에 삽입
        if (t->left != leaf)
            put(t->left);
        
        // 다음 오른쪽 queue에 삽입
        if (t->right != leaf)
            put(t->right);
    }
}