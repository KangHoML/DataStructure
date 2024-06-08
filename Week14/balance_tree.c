#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

typedef struct _node {
    int key;
    struct _node *left;
    struct _node *right;
}node;

void init_tree(node **p);
node *bti_insert(int key, node *base, int *num);
void bti_sort(node *p, int *a, int *index);
node *_balance(int N, int *a, int *index);
void make_balance_tree(node *base, int *num);
void _deleteall(node *t);
node *delete_tree(node *base, int *num);
void print_tree(node *base, int level);

void main() {
    srand(time(NULL));
    int number, tree_size;
    node *base, t;

    // tree 초기화
    init_tree(&base);

    // tree 생성
    tree_size = 0;
    for (int i = 0; i < 10; i++) {
        number = rand() % 10 + 1;
        bti_insert(number, base, &tree_size);
    }

    printf("\n\n\nOriginal Tree:\n");
    print_tree(base->left, 0);
    
    // balanced tree 생성
    make_balance_tree(base, &tree_size);

    printf("\n\n\nBalanced Tree:\n");
    print_tree(base->left, 0);
}

void init_tree(node **p) {
    *p = malloc(sizeof(node));

    (*p)->key = 0;
    (*p)->left = NULL, (*p)->right = NULL;
}

node *bti_insert(int key, node *base, int *num) {
    node *p, *c;

    // 추가할 node의 위치 찾기
    p = base, c = base->left;
    while(c != NULL) {
        p = c;
        if (key < c->key) c = c->left;
        else c = c->right;
    }

    // 추가
    c = (node *)malloc(sizeof(node));
    c->key = key;
    c->left = NULL, c->right = NULL;

    // 부모 노드와 연결
    if (c->key < p->key || p == base) p->left = c;
    else p->right = c;

    // tree 크기 하나 증가
    (*num)++;

    return c;
}

void bti_sort(node *p, int *a, int *index) {
    if (p == NULL) return;

    bti_sort(p->left, a, index);
    a[(*index)++] = p->key;
    bti_sort(p->right, a, index);
}

node *_balance(int N, int *a, int *index) {
    int low, high;
    node *p;

    // 종료 조건 (divide가 끝난 경우)
    if (N <= 0) return NULL;

    // divide
    low = (N - 1) / 2; // mid 제외
    high = N - low - 1; // mid, low 제외

    // 새로운 노드 생성
    p = (node *)malloc(sizeof(node));

    // inorder traverse
    p->left = _balance(low, a, index);
    p->key = a[(*index)++];
    p->right = _balance(high, a, index);

    return p;
}

void make_balance_tree(node *base, int *num) {
    void *sorted_arr;
    int index, tree_size;
    
    // 오름차순으로 정렬
    sorted_arr = malloc((*num)*sizeof(int));
    index = 0;
    bti_sort(base, sorted_arr, &index);
    
    // tree 삭제
    tree_size = *num;
    delete_tree(base, num);
    
    // balance tree로 다시 구성
    index = 0;
    base->left = _balance(tree_size, sorted_arr, &index);
    *num = tree_size;

    free(sorted_arr);
}

// 자식 먼저 삭제해야 하므로 postorder 순서(left->right->root)
void _deleteall(node *t) {
    if (t == NULL) return;

    _deleteall(t->left);
    _deleteall(t->right);
    free(t);
}

node *delete_tree(node *base, int *num) {
    node *t = base->left;
    
    // 삭제
    _deleteall(t);

    // tree 초기화
    base->left = NULL, base->right = NULL;
    *num = 0;
    
    return base;
}

void print_tree(node *t, int level) {
    // 종료 조건
    if (t == NULL) return;

    // 출력 시에는 make와 반대로 right->root->left
    print_tree(t->right, level + 1);
    for (int i = 0; i < level; i++) {
        printf("\t");
    }
    printf("%d\n", t->key);
    print_tree(t->left, level + 1);
}