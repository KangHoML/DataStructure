#include <stdio.h>
#include <stdlib.h>

int input_map[15][15] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0},
    {0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
    {0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0},
    {0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

// 방향
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

// stack을 위한 linked list 구조체 정의
typedef struct _node {
    int *data;
    struct _node *next;
}node;

// 전역변수 정의
node *head, *tail;
int label = 2;

// 필요한 함수 미리 정의
void init_stack();
int push(int *in_data);
int* pop();
void labeling(int x, int y);

// main 함수
void main() {
    init_stack();

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            labeling(i, j);
        }
    }

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            printf("%-3d", input_map[i][j]);
        }
        printf("\n");
    }
    
}

// stack 초기화
void init_stack() {
    head = (node *)calloc(1, sizeof(node));
    tail = (node *)calloc(1, sizeof(node));

    head->next = tail;
    tail->next = tail;
}

// [x, y, dir] 정보를 받아 stack에 저장
int push(int *in_data) {
    node *temp;
    
    if ((temp = (node *)malloc(sizeof(node))) == NULL)
        return -1;
    
    temp->data = in_data;

    temp->next = head->next; 
    head->next = temp;

    return 1;
}

// stack에 저장된 [x, y, dir] 정보를 꺼내 반환
int* pop() {
    node *temp;
    int *out_data;

    if (head->next == tail)
        return NULL;

    temp = head->next;
    out_data = temp->data;

    head->next = temp->next;

    return out_data;
}

// 각 구역 라벨링
void labeling(int x, int y) {
    int nx, ny;
    int *in_data, *out_data;
    int flag, cnt;
    node *cursor;

    cnt = 0;
    do {
        flag = 0;
        for (int d = 0; d < 8; d++) {
            nx = x + dx[d];
            ny = y + dy[d];

            if (nx < 0 || nx >= 15 || ny < 0 || ny >= 15) continue;
            if (input_map[nx][ny] == 0) continue;

            in_data[0] = x;
            in_data[1] = y;
            in_data[2] = d;

            push(in_data);
            flag = 1;
            cnt +=1;
        }

        x = nx;
        y = ny;
    } while(flag != 0);

    if (cnt == 0)
        return;

    cursor = head->next;
    while(cursor->next != tail) {
        out_data = pop();
        input_map[out_data[0]][out_data[1]] = label;
    }

    label++;
    pop();
}