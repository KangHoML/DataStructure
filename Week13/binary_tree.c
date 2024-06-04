#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _node {
    int key;
    struct _node *left;
    struct _node *right;
}node;

// functions for binary tree search
void init_tree(node **base);
node *bti_search(int key, node *base, int *num);
node *bti_insert(int key, node *base, int *num);
node *naive_bti_delete(int key, node *base, int *num);
node *bti_delete(int key, node *base, int *num);

void main() {
    node *base, *t;
    int size = 0;
    int make_key[12] = { 5, 1, 14, 0, 3, 11, 2, 6, 12, 7, 13, 10 };
    int del_key[4] = { 2, 12, 1, 5 };

    // initialize tree
    init_tree(&base);

    // make tree
    for (int i = 0; i < 12; i++) {
        bti_insert(make_key[i], base, &size);
        printf("inserted value: %c\n", (char)(make_key[i] + 'A'));
    }

    // search tree
    t = bti_search(7, base, &size);
    printf("searched value: %c\n", (char)(t->key + 'A'));

    // delete tree
    for (int i = 0; i < 4; i++) {
        t = bti_delete(del_key[i], base, &size);
        printf("deleted key %c's parent value: %c\n", (char)(del_key[i] + 'A'), (char)(t->key + 'A'));
    }
}

void init_tree(node **base) {
    *base = (node *)malloc(sizeof(node));

    (*base)->key = -1;
    (*base)->left = NULL, (*base)->right = NULL;
}

node *bti_search(int key, node *base, int *num) {
    node *t = base->left;

    // key 위치 찾기
    while (key != t->key && t != NULL) {
        if (key < t->key) t = t->left; // down
        else t = t->right; // up
    }

    return t; // 못 찾았을 경우, NULL 반환
}

node *bti_insert(int key, node *base, int *num) {
    node *p, *c;

    // 추가할 node의 위치 찾기
    p = base, c = base->left;
    while (c != NULL) {
        p = c;
        if(key < c->key) c = c->left; // down
        else c = c->right; // up or same
    }

    // 해당 위치에 node 생성
    c = (node *)malloc(sizeof(node));
    c->key = key;
    c->left = NULL, c->right = NULL;

    // 부모의 node와 연결
    if (c->key < p->key || p == base) p->left = c;
    else p->right = c;

    // num 증가
    (*num)++;

    return c;
}

node *naive_bti_delete(int key, node *base, int *num) {
    node *del, *parent, *son, *nexth;
    
    // 초기값 설정
    parent = base;
    del = base->left;

    // 제거할 node 위치 찾기
    while (key != del->key && del != NULL)  {
        parent = del;
        if (key < del->key) del = del->left; // down
        else del = del->right; // up
    }

    // 제거할 node 없는 경우 return
    if (del == NULL) return NULL;

    // case 1
    if (del->left == NULL && del->right == NULL)
        son = NULL;
    
    // case 2
    else if (del->left != NULL && del->right != NULL) {
        nexth = del->right;

        // case 2-1. tree가 깨질 때
        if (nexth->left != NULL) {
            // 삭제하려는 값보다 큰 값 중 최소값
            while (nexth->left->left != NULL) nexth = nexth->left;
            son = nexth->left;
            
            // son이 위로 올라가므로 해당 위치 노드 제거
            nexth->left = son->right;
            
            // 삭제할 node의 child node 들과 연결
            son->left = del->left;
            son->right = del->right;
        }

        // case 2-2. tree 유지될 때
        else {
            son = nexth;
            son->left = del->left;
        }
    }

    // case 3
    else {
        if (del->left != NULL) son = del->left;
        else son = del->right;
    }

    // parent와 son 연결
    if (key < parent->key || parent == base) parent->left = son;
    else parent->right = son;

    // delete & num 감소
    free(del);
    (*num)--;

    return parent;
}

node *bti_delete(int key, node *base, int *num) {
    node *del, *parent, *son, *nexth;
    
    // 초기값 설정
    parent = base;
    del = base->left;

    // 제거할 node 위치 찾기
    while (key != del->key && del != NULL)  {
        parent = del;
        if (key < del->key) del = del->left; // down
        else del = del->right; // up
    }

    // 제거할 node 없는 경우 return
    if (del == NULL) return NULL;

    // case 1. parent와 son을 바로 이어도 tree가 깨지지 않음
    if (del->right == NULL) son = del->left;

    // case 2. right 값이 삭제하려는 값보다 큰 값 중 최소값
    else if (del->right->left == NULL) {
        son = del->right; 
        son->left = del->left; // 분리되어 있는 del->left 연결
    }

    // case 3. 모두 만족 X
    else {
        nexth = del->right;

        // 삭제하려는 값보다 큰 값 중 최소값 찾기
        while(nexth->left->left != NULL) nexth = nexth->left;
        son = nexth->left;
        
        // son 값 중복되지 않도록 삭제
        nexth->left = son->right;

        // son의 child node 새로 연결
        son->left = del->left;
        son->right = del->right;
    }


    // parent와 son 연결
    if (key < parent->key || parent == base) parent->left = son;
    else parent->right = son;

    // delete & num 감소
    free(del);
    (*num)--;

    return parent;
}