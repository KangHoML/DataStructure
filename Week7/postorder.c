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
void recur_postorder(dnode* t);
void nonrecur_postorder(dnode* t);

void main() {
    init_tree();
    make_tree();

    recur_postorder(root->right);
    printf("\n");

    nonrecur_postorder(root->right);
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

void recur_postorder(dnode* t) {
    if (t == leaf) return;
    recur_postorder(t->left);
    recur_postorder(t->right);
    printf("%-3c", 'A' + t->key);
}

void nonrecur_postorder(dnode* t) {
    dnode *last_visited;
    node* cursor;

    init_stack();
    push(t);

    // 왼쪽 맨 마지막 leaf에 도달할 때까지 stack에 push
    while (t != leaf) {
        push(t);
        t = t->left;
    }

    // 초기값 설정
    cursor = head->next;
    last_visited = NULL;

    // 탐색
    while (cursor->next != tail) {
        // 방문하였거나 오른쪽 노드가 leaf일 때
        if (cursor->data->right == leaf || cursor->data->right == last_visited) {
            t = pop();
            cursor = head->next;
            printf("%-3c", 'A' + t->key);
        }

        // 방문한 적 없을 때
        else {
            // 우측 노드로 이동
            t = cursor->data->right;

            // 가장 마지막 left까지 들어가기
            while (t->left != leaf) {
                push(t);
                t = t->left;
            }

            // 가장 마지막 right까지 들어가기
            while (t->right != leaf && t != last_visited) {
                push(t);
                t = t->right;
            }

            // 마지막 방문한 노드
            cursor = head->next; // push하기 전 부모 노드를 보기 위해
            push(t);
        }

        // 마지막 방문
        last_visited = t;
    }
}