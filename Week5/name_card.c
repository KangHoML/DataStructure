#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#define NAME_SIZE 20
#define CORP_SIZE 30
#define TEL_SIZE 20
#define REC_SIZE (NAME_SIZE + CORP_SIZE + TEL_SIZE)

// Struct
typedef struct _card{
    char name[NAME_SIZE];
    char corp[CORP_SIZE];
    char tel[TEL_SIZE];
    struct _card *next;
}card;

// Define head & tail
card *head, *tail;

// Define all functions
void init_card();
void input_card();
int delete_card(char *name);
card *search_card(char *name);
void save_card(char *root);
void load_card(char *root);
void print_header();
void print_card(card *t);
int select_menu();
void input(), delete(), search(), load(), save(), show();
void (*fptr[6])() = {input, delete, search, load, save, show};

void main() {
    int i;
    init_card();

    while((i = select_menu()) != 7) {
        fptr[i-1]();
    }

    printf("\n7. Program Ends ... \n");

}

void init_card() {
    head = (card *)calloc(1, sizeof(card));
    tail = (card *)calloc(1, sizeof(card));

    head->next = tail;
    tail->next = tail;
}

void input_card() {
    card *temp = (card *)calloc(1, sizeof(card));

    printf("Input namecard");
    printf("\nInput name: ");
    fgets(temp->name, sizeof(temp->name), stdin);

    printf("\nInput corporation: ");
    fgets(temp->corp, sizeof(temp->corp), stdin);

    printf("\nInput telephone: ");
    fgets(temp->tel, sizeof(temp->tel), stdin);

    temp->next = head->next;
    head->next = temp;
}

int delete_card(char *name) {
    card *prev, *cursor;
    
    cursor = head->next;
    while(strcmp(name, cursor->name) != 0 && cursor != tail) {
        prev = cursor;
        cursor = cursor->next;
    }
    
    if (cursor == tail)
        return -1;
    
    prev->next = cursor->next;
    free(cursor);
    
    return 1;
}

card *search_card(char *name) {
    card *cursor;

    cursor = head->next;
    while(strcmp(name, cursor->name) != 0 && cursor != tail) {
        cursor = cursor->next;
    }

    if (cursor == tail)
        return NULL;
    else
        return cursor;
}

void save_card(char* root) {
    FILE *fp;
    card* cursor = head->next;

    if ((fp = fopen(root, "wb")) == NULL)
        printf("failed to open file");
        
    while(cursor != tail) {
        fwrite(cursor, REC_SIZE, 1, fp);
        cursor = cursor->next;
    }

    fclose(fp);
}

void load_card(char* root) {
    FILE *fp;
    card *temp, *cursor;

    // list 비워주기
    cursor = head->next;
    while (cursor != tail) {
        temp = cursor;
        cursor = cursor->next;
        free(temp);
    }
    head->next = tail;

    // load
    if ((fp = fopen(root, "rb")) == NULL)
        printf("failed to open file");
    
    while(1) {
        temp = (card *)calloc(1, sizeof(card));

        // 파일의 끝에 도달 시 메모리 해제 및 break
        if (fread(temp, REC_SIZE, 1, fp) == 0) {
            free(temp);
            break;
        }

        temp->next = head->next;
        head->next = temp;
    }

    fclose(fp);
}

void print_header() {
    printf("\n%-20s %-30s %-20s", "Name", "Corporation", "Tel");
    printf("\n-------------------- ------------------------------ --------------------");
}

void print_card(card *t) {
    printf("\n%-20.*s %-30.*s %-20.*s",
           (int)strcspn(t->name, "\n"), t->name,
           (int)strcspn(t->corp, "\n"), t->corp,
           (int)strcspn(t->tel, "\n"), t->tel);
}

int select_menu() {
    int j;
    char s[10];

    printf("\nName Card Manager");
    printf("\n---------------------");
    printf("\n1. Input name card");
    printf("\n2. Delete name card");
    printf("\n3. Search name card");
    printf("\n4. Load name card");
    printf("\n5. Save name card");
    printf("\n6. Show list");
    printf("\n7. Program end ...");

    do {
        printf("\n: selection operation -> ");
        j = atoi(fgets(s, sizeof(s), stdin));
    }while(j < 0 || j > 7);

    return j;
}

void input() {
    input_card();
}

void delete() {
    char name[NAME_SIZE];
    printf("\nInput name to delete -> ");
    fgets(name, sizeof(name), stdin);

    if (delete_card(name) == -1)
        printf("\nCan't find the name");
}

void search() {
    char name[NAME_SIZE];
    card *temp;

    printf("\nInput name to search -> ");
    fgets(name, sizeof(name), stdin);

    if ((temp = search_card(name)) == NULL) {
        printf("\nCan't find the name");
        return;
    }

    print_header();
    print_card(temp);
}

void load() {
    char *root = "NameCard.dat";
    load_card(root);
}

void save() {
    char *root = "NameCard.dat";
    save_card(root);
}

void show() {
    card *temp;

    temp = head->next;
    print_header();
    
    while(temp != tail) {
        print_card(temp);
        temp = temp->next;
    }
}