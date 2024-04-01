#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warninig(disable: 4996)

#define NAME_SIZE 21
#define CORP_SIZE 31
#define TEL_SIZE 16
#define REC_SIZE (NAME_SIZE + CORP_SIZE + TEL_SIZE)

typedef struct _card{
    char name[NAME_SIZE];
    char corp[CORP_SIZE];
    char tel[TEL_SIZE];
    struct _card *next;
}card;

card *head, *tail;

void init_card() {
    head = (card *)calloc(1, sizeof(card));
    tail = (card *)calloc(1, sizeof(card));
    
    head->next = tail;
    tail->next = tail;
}

// 입력을 통해 name card를 linked list에 추가
void input_card() {
    card *t = (card *)calloc(1, sizeof(card));

    printf("\nInput name card menu");
    printf("\nInput name: ");
    fgets(t->name, sizeof(t->name), stdin);

    printf("\nInput corporation: ");
    fgets(t->corp, sizeof(t->corp), stdin);

    printf("\nInput telephone number: ");
    fgets(t->tel, sizeof(t->tel), stdin);

    // 나중에 입력한게 제일 앞에 있도록
    t->next = head->next;
    head->next = t;
}

// 이름을 통해 linked list에서 해당 node 삭제
int delete_card(char *s) {
    card *t, *p;
    p = head;
    t = p->next;

    while(strcmp(s, t->name) != 0 && t != tail) {
        p = p->next;
        t = p->next;
    }

    if (t == tail)
        return 0;

    p->next = t->next;
    free(t);
    return 1;
}

// 이름을 통해 linked list에서 해당 node 찾기
card* search_card(char *s) {
    card *t, *p;
    p = head;
    t = p->next;

    while(strcmp(s, t->name) != 0 && t != tail) {
        t = t->next;
    }

    if (t == tail)
        return NULL;
    else
        return t;
}

// 파일 위치 s를 받아 binary 파일로 저장
void save_card(char *s) {
    FILE *fp = fopen(s, "wb");
    card *t;

    t = head->next;
    while(t != tail) {
        fwrite(t, REC_SIZE, 1, fp);
        t = t->next;
    }

    fclose(fp);
}

// 파일 위치 s를 받아 binary 파일로 로드
void load_card(char *s) {
    FILE *fp = fopen(s, "rb");
    card *t, *u;

    // 현재 있는 linked list 내부의 데이터를 다 지우기 (delete_all 함수와 동일)
    t = head->next;
    while(t != tail) {
        u = t;
        t = t->next;
        free(u);
    }
    head->next = tail;

    while(1) {
        t = (card *)calloc(1, sizeof(card));

        // 더 이상 읽을게 없으면 t를 free 해준 뒤 break
        if(!fread(t, REC_SIZE, 1, fp)) {
            free(t);
            break;
        }

        t->next = head->next;
        head->next = t;
    }

    fclose(fp);
}

void print_header() {
    printf("\nName                  "
            "Corporation           "
            "Telephone             ");
    
    printf("\n--------------------- "
            "--------------------- "
            "--------------------- ");
}

void print_card(card *t) {
    printf("\n%-20s    %-20s    %-20s", t->name, t->corp, t->tel);
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

void main() {
    char *fname = "NameCard.dat";
    char name[NAME_SIZE];
    int i;
    card *t;

    init_card();

    while((i = select_menu()) != 7) {
        switch(i) {
            case 1:
                input_card();
                break;
            
            case 2:
                printf("\nInput name to delete -> ");
                fgets(name, sizeof(name), stdin);

                if(!delete_card(name))
                    printf("\nCan't find the name...");
                
                break;
            
            case 3:
                printf("\nInput name to search -> ");
                fgets(name, sizeof(name), stdin);

                t = search_card(name);
                
                if (t == NULL)
                    break;
                
                print_header();
                print_card(t);
                break;
            
            case 4:
                load_card(fname);
                break;
            
            case 5:
                save_card(fname);
                break;
            
            case 6:
                t = head->next;
                print_header();
                
                while(t != tail) {
                    print_card(t);
                    t = t->next;
                }
                break;
        }
    }
    printf("\n7. Program ends ...\n");

}