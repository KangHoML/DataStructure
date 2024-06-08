#include "bt_library.h"
#include <string.h>
int _index;

// tree 초기화
void init_tree(node **p) {
    *p = (node *)malloc(sizeof(node));

    (*p)->left = NULL, (*p)->right = NULL;
}

// tree에서 node 찾기
void *bt_search(void *key, node *base, int *num, size_t size, FCMP fcmp) {
    node *c;
    
    // 추가할 node 위치 찾기
    c = base->left;
    while(c != NULL && fcmp(key, c + 1) != 0) {
        if (fcmp(key, c + 1) < 0) c = c->left;
        else c = c->right;
    }
    
    // 반환
    if (c == NULL) return NULL;
    else return c + 1;
}

void *bt_insert(void *key, node *base, int *num, size_t size, FCMP fcmp) {
    node *p, *c;
    
    // 추가할 node 위치 찾기
    p = base, c = base->left;
    while(c != NULL) {
        p = c;
        if (fcmp(key, c + 1) < 0) c = c->left;
        else c = c->right;
    }

    // node 생성
    c = (node *)malloc(sizeof(node) + size);
    if (c == NULL) return NULL; // 예외처리
    memcpy(c + 1, key, size);
    c->left = NULL, c->right = NULL;

    // parent node와 연결
    if (fcmp(c + 1, p + 1) < 0 || p == base) p->left = c;
    else p->right = c;

    // tree 크기 증가
    (*num)++;
    
    return c;
}

void *bt_delete(void *key, node *base, int *num, size_t size, FCMP fcmp){
    node *del, *parent, *child, *nexth;

    // 삭제할 위치 찾기
    parent = base, del = base->left;
    while(del != NULL && fcmp(key, del + 1) != 0) {
        parent = del;
        if (fcmp(key, del + 1) < 0) del = del->left;
        else del = del->right;
    }

    // 못 찾았을 경우 NULL 반환
    if (del == NULL) return NULL;

    // case 1.
    if (del->right == NULL) child = del->left;

    // case 2.
    else if (del->right->left == NULL) {
        child = del->right;
        child->left = del->left;
    }

    // case 3.
    else {
        nexth = del->right;
        
        while(nexth->left->left != NULL) nexth = nexth->left;
        child = nexth->left;

        nexth->left = child->right;
        child->left = del->left;
        child->right = del->right;
    }

    // parent와 연결
    if (fcmp(child + 1, parent + 1) < 0 || parent == base) parent->left = child;
    else parent->right = child;

    // 삭제 및 free
    free(del);
    (*num)--;
    
    return parent;
}

void _deleteall(node *t) {
    // 종료 조건
    if (t == NULL) return;

    // child부터 순서대로 제거 (left -> right -> root)
    _deleteall(t->left);
    _deleteall(t->right);
    free(t);
}

void *delete_tree(node *base, int *num) {
    _deleteall(base->left);
    base->left = NULL, base->right = NULL;
    *num = 0;

    return base;
}

void _sort(node *p, void *a, size_t size) {
    // 종료 조건
    if (p == NULL) return;

    // 오름차순 정렬 (left->root->right)
    _sort(p->left, a, size);
    memcpy((char *)a + (_index++) * size, p + 1, size);
    _sort(p->right, a, size);
}

node *_balance(int n, void *a, size_t size) {
    int low, high;
    node *t;

    // 종료 조건
    if (n <= 0) return NULL;

    low = (n - 1) / 2;
    high = n - low - 1;

    // node 생성
    t = (node *)malloc(sizeof(node) + size);

    // inorder traverse
    t->left = _balance(low, a, size);
    memcpy(t + 1, (char *)a + (_index++) * size, size);
    t->right = _balance(high, a, size);

    return t;
}

void balancify(node *base, int *num, size_t size) {
    void *sorted_arr = malloc((*num) * size);
    int tree_size;

    // sorting
    _index = 0;
    _sort(base->left, sorted_arr, size);

    // delete original tree
    tree_size = *num;
    delete_tree(base, num);

    // rebuild the tree balanced
    _index = 0;
    base->left = _balance(tree_size, sorted_arr, size);
    *num = tree_size;

    free(sorted_arr);
}

void print_tree(node *t, void(*fptr)(void *), int level) {
    if (t == NULL) return;

    // print할때는 inorder의 역순 (right -> root ->left)
    print_tree(t->right, fptr, level + 1);
    
    for (int i = 0; i < level; i++) printf("\t");
    fptr(t + 1);

    print_tree(t->left, fptr, level + 1);
}