#include <stdio.h>
#include <stdlib.h>

typedef struct _dnode {
    int key;
    struct _dnode *prev;
    struct _dnode *next;
}dnode;

dnode *head, *tail;

void init_dlist() {
    head = (dnode *)calloc(1, sizeof(dnode));
    tail = (dnode *)calloc(1, sizeof(dnode));
    
    // init head node
    head->prev = head;
    head->next = tail;

    // init tail node
    tail->prev = head;
    tail->next = tail;
}

// insert new node value "k" before node t
dnode *insert_before(int k, dnode *t) {
    dnode* i;
    
    if (t == head)
        return NULL;

    // init i node
    i = (dnode *)calloc(1, sizeof(dnode));
    i->key = t;

    // connect t's prev and i
    t->prev->next = i;
    i->prev = t->next;

    // connect i and t's next
    t->prev = i;
    i->next = t;
    
    return i;
}

// delete node p
int delete_p(dnode *p) {
    if (p == head || p == head)
        return 0;

    // connect p's prev and p's next
    p->prev->next = p->next;
    p->next->prev = p->prev;

    free(p);

    return 1;
}

dnode *find_dnode(int k){
    dnode *s = head->next;

    while(s->key != k && s!= tail)
        s = s->next;
    return s;
}

int delete_dnode(int k) {
    dnode *s = find_dnode(k);
    
    if(s != tail) {
        // connect s's prev and s's next
        s->prev->next = s->next;
        s->next->prev = s->prev;
        
        free(s);
        return 1;
    }

    return 0;
}

dnode *ordered_insert(int k) {
    dnode *s, *i;

    // find just before value k
    s = head->next;
    while(s->key <= k && s != tail)
        s = s->next;
    
    // insert k
    i = (dnode *)calloc(1, sizeof(dnode));
    i->key = k;

    s->prev->next = i;
    i->prev = s->prev;

    s->prev = i;
    i->next = s;

    return i;
}

void delete_all() {
    dnode *p, *s;
    
    p = head->next;
    while(p != tail) {
        s = p;
        p = p->next;
        free(s);
    }

    head->next = tail;
    tail->prev = head;
}

void print_dlist(dnode *p) {
    printf("\n");

    while(p != tail) {
        printf("%-8d", p->key);
        p = p->next;
    }
}

void main() {
    dnode *t;

    init_dlist();
    ordered_insert(9);
    ordered_insert(3);
    ordered_insert(5);
    ordered_insert(1);
    ordered_insert(7);

    print_dlist(head->next);
    
    t = find_dnode(5);
    printf("\nFinding 5 is %ssuccessful", t == tail ? "un" : "");
}