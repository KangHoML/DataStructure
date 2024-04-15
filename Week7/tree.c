#include <stdio.h>
#include <stdlib.h>

// tree를 위한 구조체 정의 
typedef struct _dnode{
    int key;
    struct _dnode *left;
    struct _dnode *right;
}dnode;

// stack을 위한 구조체 정의
typedef struct _node {
    int key;
    struct _node *next;
}node;

// 전역변수 선언
node *head, *tail;
dnode *root, *leaf;

// 필요한 함수 선언
void init_stack();
void init_tree();
int push(int key);
int pop();
void preorder_traverse(dnode* t);
void inorder_traverse(dnode* t);

void main() {

}

void init_stack() {
    head = (node *)calloc(1, sizeof(node));
    tail = (node *)calloc(1, sizeof(node));

    head = tail;
    tail = tail;
}

void init_tree() {
    root = (dnode *)calloc(1, sizeof(dnode));
    leaf = (dnode *)calloc(1, sizeof(dnode));

    root->left = leaf;
    root->right = leaf;

    leaf->left = leaf;
    leaf->right = leaf;
}

int push(int key) {
    node* temp;

    if ((temp = malloc(sizeof(node))) == NULL)
        return -1;
    
    temp->next = head->next;
    temp->key = key;

    head->next = temp;
}

int pop() {
    node *temp;
    int key;

    if (head->next == tail)
        return -1;

    temp = head->next;
    key = temp->key;
    
    head->next = temp->next;
    free(temp);

    return key;
}

void preorder_traverse(dnode* t) {
    if (t != leaf) {
        printf("%d", t->key);
        preorder_traverse(t->left);
        preorder_traverse(t->right);
    }
}

void inorder_traverse(dnode* t) {
    if (t != leaf) {
        inorder_traverse(t->left);
        printf("%d", t->key);
        inorder_traverse(t->right);

    }
}