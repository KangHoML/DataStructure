#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int key;
    struct _node *next;
}node;

node *head, *tail;

void init_list() {
    head = (node*)calloc(1, sizeof(node));
    tail = (node*)calloc(1, sizeof(node));

    head->next = tail;
    tail->next = tail;
}

node *insert_next(int k, node *t) {
    node *temp = (node *)calloc(1, sizeof(node));

    temp->key = k;
    temp->next = t->next;
    t->next = temp;

    return temp;
}

int delete_next(node *t) {
    node *temp;

    // check the current node
    if (t->next == tail)
        return 0;

    temp = t->next;
    t->next = t->next->next;

    free(temp); // free the allocated memory
    return 1;
}

node *find_node(int k) {
    node* temp;

    temp = head->next;
    while(temp->key != k && temp != tail)
        temp = temp->next;
    
    return temp; // if temp is tail, fail to find a given key value
}

// insert t before k
node* insert_node(int t, int k) {
    node *s, *p, *r;
    p = head;
    s = p->next;

    while(s->key != k && s != tail) {
        p = p->next;
        s = p->next;
    }

    if(s != tail) {
        r = (node *)calloc(1, sizeof(node));
        r->key = t;
        p->next = r;
        r->next = s;
    }

    return r;
}

int delete_node(int k) {
    node *s, *p;
    p = head; // previous node of s
    s = p->next;

    while(s->key != k && s != tail) {
        p = p->next;
        s = p->next;
    }

    // check the current node and free the allocated memory
    if (s != tail) {
        p->next = s->next;
        free(s);
        return 1;
    }
    else
        return 0;
}

node *ordered_insert(int k) {
    node *s, *p, *r;
    p = head;
    s = p->next;

    while(s->key <= k && s != tail) {
        p = p->next;
        s = s->next;
    }

    r = (node *)calloc(1, sizeof(node));
    r->key = k;
    p->next = r;
    r->next = s;
    
    return r;
}

node *delete_all() {
    node *s, *t;
    t = head->next;

    while(t != tail) {
        s = t;
        t = t->next;
        free(s);
    }

    head->next = tail;
    return head;
}

void print_list(node *t) {
    while(t != tail) {
        printf("%-8d", t->key);
        t = t->next;
    }
    printf("\n");
}

int find_pos(int k) {
    node* temp;
    int cnt = 0;

    temp = head->next;
    while(temp->key != k && temp != tail) {
        temp = temp->next;
        cnt += 1;
    }
        
    return cnt; // if temp is tail, fail to find a given key value
}

void main() {
    node *t;

    init_list();
    ordered_insert(9);
    ordered_insert(3);
    ordered_insert(5);
    ordered_insert(1);
    ordered_insert(7);

    t = head->next;
    printf("position of 5: %d\n", find_pos(5));
    print_list(t);
    
    node* temp = find_node(5);
    insert_next(6, temp);
    print_list(t);
    
    delete_node(5);
    print_list(t);
    
    delete_all();
}