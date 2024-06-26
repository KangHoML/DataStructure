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
    {0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

// 방향
int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

// stack을 위한 linked list 구조체 정의
typedef struct _node {
    int data[3]; // 데이터를 직접적으로 저장하기 위해 배열로 저장
    struct _node* next;
}node;

// 전역변수 정의
node* head, * tail;
int label = 1;

// 필요한 함수 미리 정의
void init_stack();
int push(int* in_data);
int* pop();
void labeling(int x, int y);

// main 함수
void main() {
    // stack 초기화
    init_stack();

    // 전체 배열에 대해 완전 탐색
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            labeling(i, j);
        }
    }

    // 출력
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            printf("%-3d", input_map[i][j]);
        }
        printf("\n");
    }
}

// stack 초기화
void init_stack() {
    head = (node*)calloc(1, sizeof(node));
    tail = (node*)calloc(1, sizeof(node));

    head->next = tail;
    tail->next = tail;
}

// [x, y, dir] 정보를 받아 stack에 저장
int push(int* in_data) {
    node* temp;

    if ((temp = (node*)malloc(sizeof(node))) == NULL)
        return -1;

    temp->data[0] = in_data[0];
    temp->data[1] = in_data[1];
    temp->data[2] = in_data[2];

    temp->next = head->next;
    head->next = temp;

    return 1;
}

// stack에 저장된 [x, y, dir] 정보를 꺼내 반환
int* pop() {
    node* temp;
    int* out_data = (int*)calloc(3, sizeof(int)); // pop()을 통해 출력할 데이터를 동적할당

    if (head->next == tail)
        return NULL;

    temp = head->next;
    out_data[0] = temp->data[0];
    out_data[1] = temp->data[1];
    out_data[2] = temp->data[2];

    head->next = temp->next;
    free(temp); // 비워주기

    return out_data;
}

// 각 구역 라벨링
void labeling(int r, int c) {
    int x, y, d, nx, ny, flag;
    int* in_data = (int *)calloc(3, sizeof(int));
    node* cursor;

    in_data[0] = r, in_data[1] = c, in_data[2] = 0;
    push(in_data);
    cursor = head->next;

    while (cursor != tail) {
        cursor = head->next;
        x = cursor->data[0], y = cursor->data[1], d = cursor->data[2];
        flag = 0;

        // 8 개의 방향을 탐색
        for (int i = 0; i < 8; i++) {
            nx = x + dx[(d + i) % 8];
            ny = y + dy[(d + i) % 8];

            // 범위 안에 존재하며 라벨링이 필요한 부분인지 체크
            if (nx >= 0 && nx < 15 && ny >= 0 && ny < 15 && input_map[nx][ny] == 1) {
                if (cursor->next == tail)
                    label++;

                input_map[nx][ny] = label; // 현재 라벨 값을 넣어줌
                in_data[0] = nx, in_data[1] = ny, in_data[2] = (d + i) % 8;
                push(in_data);

                flag = 1;
                break;
            }
        }

        // 더 이상 탐색할 게 없을 때 pop
        if (flag == 0)
            pop();
    }

    // 동적할당한 메모리 해제
    free(in_data);
}