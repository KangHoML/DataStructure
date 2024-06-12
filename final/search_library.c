#include "search_library.h"

// binary search
int bi_search(void *key, void *base, int n_elem, int size, FCMP fcmp) {
    int l, r, m;
    
    l = 0, r = n_elem - 1;
    while(r >= l) {
        m = (r + l) / 2;

        if (fcmp(key, BASE(m)) == 0) return m;
        else if (fcmp(key, BASE(m)) > 0) l = m + 1;
        else r = m - 1;
        
    }

    return -1;
}

int bi_insert(void *key, void *base, int *n_elem, int size, FCMP fcmp) {
    int l, r, m;

    // key 위치 찾기
    l = 0, r = *n_elem - 1;
    while(r >= l) {
        m = (r + l) / 2;

        if (fcmp(key, BASE(m)) > 0) l = m + 1;
        else r = m - 1;
    }

    // 한 칸 씩 뒤로 옮기기
    for (int i = *n_elem; i > l; i--) {
        memcpy(BASE(i), BASE(i-1), size);
    }
    
    // insert
    memcpy(BASE(l), key, size);
    
    // 배열 크기 증가
    (*n_elem)++;

    return l;
}

int bi_delete(void *key, void *base, int *n_elem, int size, FCMP fcmp) {
    int pos;

    // 배열에 값이 없는 경우
    if (*n_elem <= 0) return -1;

    // 못 찾은 경우
    if ((pos = bi_search(key, base, *n_elem, size, fcmp)) == 1) return -1;

    for(int i = pos; i < *n_elem - 1; i++) {
        memcpy(BASE(i), BASE(i+1), size);
    }

    (*n_elem)--;
    
    return pos;
}


// sequential search
int seq_search(void *key, void *base, int n_elem, int size, FCMP fcmp) {
    int i = 0;

    while(i < n_elem && fcmp(BASE(i), key) != 0) i++;

    return (i < n_elem ? i : -1);
}

int seq_insert(void *key, void *base, int *n_elem, int size) {

    if (*n_elem >= MAX) return -1;

    memcpy(BASE((*n_elem)++), key, size);

    return *n_elem - 1;
}

int seq_delete(void *key, void *base, int *n_elem, int size, FCMP fcmp) {
    int pos;

    if (*n_elem < 1) return -1;

    if ((pos = seq_search(key, base, *n_elem, size, fcmp)) < 0) return -1;

    for (int i = pos; i < *n_elem - 1; i++) {
        memcpy(BASE(i), BASE(i+1), size);
    }

    (*n_elem)--;

    return pos;
}

int seq_f_search(void *key, void *base, int n_elem, int size, FCMP fcmp) {
    int pos;

    if ((pos = seq_search(key, base, n_elem, size, fcmp)) < 0) return -1;

    for (int i = pos; i > 0; i--) {
        memcpy(BASE(i), BASE(i-1), size);
    }
    memcpy(BASE(0), key, size);

    return pos;
}

// linked search
void init(node **p) {
    *p = (node *)malloc(sizeof(node));
    (*p)->next = NULL;
}

void *linked_search(void *key, node *base, FCMP fcmp) {
    node *t = base->next;
    
    while(t != NULL && fcmp(t + 1, key) != 0) {
        t = t->next;
    }

    return (t == NULL ? NULL : t + 1);
}

void *linked_insert(void *key, node *base, int *n_elem, int size) {
    node *t;

    // 새로운 노드 생성
    t = (node*)malloc(sizeof(node) + size);
    memcpy(t + 1, key, size);

    // 생성된 노드 head 쪽에 추가
    t->next = base->next;
    base->next = t;

    (*n_elem)++;

    return t;
}

void *linked_delete(void *key, node *base, int *n_elem, FCMP fcmp) {
    node *t, *p;

    // key 위치 찾기
    p = base, t = base->next;
    while(t != NULL && fcmp(t + 1, key) != 0) {
        p = t;
        t = t->next;
    }

    // 예외처리
    if (t == NULL) return NULL;

    // 삭제
    p->next = t->next;
    free(t);

    (*n_elem)--;

    return p;
}

void *linked_f_search(void *key, node *base, FCMP fcmp) {
    node *t, *p;

    // key 값 찾기
    p = base, t = base->next;
    while(t != NULL && fcmp(t + 1, key) != 0) {
        p = t;
        t = t->next;
    }

    // 못 찾으면 NULL 반환
    if (t == NULL) return NULL;

    // 앞으로 옮겨주기
    p->next = t->next;
    t->next = base->next;
    base->next = t;

    return t;
}