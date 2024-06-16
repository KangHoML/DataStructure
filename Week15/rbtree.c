#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*FCMP)(const void *a, const void *b);
typedef struct _node {
    int red;
    struct _node *left;
    struct _node *right;
} node;

void init_tree(node **p);

void *rbt_rotate(void *key, node *pivot, node *base, FCMP fcmp);
void *rbt_insert(void *key, node *base, int *n_elem, int size, FCMP fcmp);

int charcmp(const void *a, const void *b);
void print_char(void *a);
void print_tree(node *t, void (*fptr)(void *), int level);

void main() {
    node *head;
    char keys[10] = {'K', 'L', 'C', 'A', 'E', 'F', 'D', 'I', 'H', 'G'};
    int tree_size;

    init_tree(&head);
    tree_size = 0;

    for (int i = 0; i < 10; i++) {
        rbt_insert(&keys[i], head, &tree_size, sizeof(char), charcmp);
        printf("\n--- %d --- \n", i+1);
        print_tree(head->left, print_char, 0);
        printf("\n");
    }
}

void init_tree(node **p) {
    *p = (node *)malloc(sizeof(node));

    (*p)->red = 0;
    (*p)->left = NULL;
    (*p)->right = NULL;
}

// key가 돌리려는 대상
void *rbt_rotate(void *key, node *pivot, node *base, FCMP fcmp) {
    node *c, *gc;

    // c 위치 찾기
    if (fcmp(key, pivot+1) < 0 || pivot == base) c = pivot->left;
    else c = pivot->right;

    // key가 left에 존재 (c를 기준으로 오른쪽으로 돌리기)
    if (fcmp(key, c+1) < 0) {
        gc = c->left;
        c->left = gc->right;
        gc->right = c;
    }

    // key가 right에 존재 (c를 기준으로 왼쪽으로 돌리기)
    else {
        gc = c->right;
        c->right = gc->left;
        gc->left = c;
    }

    // pivot과 연결
    if (fcmp(key, pivot+1) < 0 || pivot == base) pivot->left = gc;
    else pivot->right = gc;

    return gc;
}

void *rbt_insert(void *key, node *base, int *n_elem, int size, FCMP fcmp) {
    node *t, *p, *gp, *ggp;

    ggp = gp = p = base;
    t = base->left;
    while(t != NULL) {
        if (fcmp(key, t+1) == 0) return NULL;

        // red black tree 유지
        if (t->left && t->right && t->left->red && t->right->red) {
            // case 1. 자식의 색과 교체
            t->red = 1;
            t->left->red = 0, t->right->red = 0;

            if (p->red) {
                gp->red = 1;
                
                // case 2. 회전 한번 더 필요 (꺾여있으므로)
                if ((fcmp(key, gp+1) < 0) != (fcmp(key, p+1) < 0))
                    p = rbt_rotate(key, gp, base, fcmp);
                
                // case 3. 회전 필요
                t = rbt_rotate(key, ggp, base, fcmp);
                t->red = 0;
            }

            base->left->red = 0;
        }

        ggp = gp;
        gp = p;
        p = t;

        if (fcmp(key, t+1) < 0) t = t->left;
        else t = t->right;
    }

    // 새로운 노드 추가
    t = (node *)malloc(sizeof(node) + size);
    memcpy(t+1, key, size);
    t->left = NULL, t->right = NULL;
    t->red = 1;

    // 부모와 이어주기
    if (fcmp(key, p+1) < 0 || p == base) p->left = t;
    else p->right = t;

    // red black tree 위반 여부 확인
    if (p->red) {
        gp->red = 1;
        
        // case 2. 회전 한번 더 필요 (꺾여있으므로)
        if ((fcmp(key, gp+1) < 0) != (fcmp(key, p+1) < 0))
            p = rbt_rotate(key, gp, base, fcmp);
        
        // case 3. 회전 필요
        t = rbt_rotate(key, ggp, base, fcmp);
        t->red = 0;
    }
    base->left->red = 0;

    (*n_elem)++;

    return t;
}

int charcmp(const void *a, const void *b) {
    return *((char *)a) - *((char *)b);
}

void print_tree(node *t, void (*fptr)(void *), int level) {
    if (t == NULL) return;

    print_tree(t->right, fptr, level + 1);
    for (int i = 0; i < level; i++) printf("\t");
    fptr(t+1);
    print_tree(t->left, fptr, level + 1);
}

void print_char(void *a) {
    printf("%c: %d\n", *((char *)a), ((node *)a - 1)->red);
}