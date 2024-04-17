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
int label = 2;

// 필요한 함수 미리 정의
void init_stack();
int push(int* in_data);
int* pop();
void labeling(int x, int y, int d);

// main 함수
void main() {
    // 변수 정의
    int nx, ny, d, flag;
    int *in_data = (int*)calloc(3, sizeof(int));
    
    // stack 초기화
    init_stack();

    // 전체 배열에 대해 완전 탐색
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            // 현재 인덱스 push
            in_data[0] = i, in_data[1] = j, in_data[2] = 0;
            push(in_data);

            // 8 개의 방향을 탐색
            for (int k = 0; k < 8; k++) {
                nx = i + dx[k];
                ny = j + dy[k];
                
                // 범위 안에 존재하며 라벨링이 필요한 부분인지 체크
                if (nx >= 0 && nx < 15 && ny >= 0 && ny < 15 && input_map[nx][ny] == 1) {
                    // 라벨링
                    labeling(nx, ny, k);
                    label++;
                }

            }
            // 마지막 (i, j) 부분 pop() 해주기
            pop();
        }
    }
    
    // 출력
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            printf("%-3d", input_map[i][j]);
        }
        printf("\n");
    }

    // 메모리 할당 해제
    free(in_data);
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
    int* out_data = (int *)calloc(3, sizeof(int)); // pop()을 통해 출력할 데이터를 동적할당

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
void labeling(int r, int c, int dir) {
    int x, y, d, nx, ny;
    int *in_data, *out_data;

    // 초기 인덱스에 대한 정보 push
    in_data = (int*)calloc(3, sizeof(int));
    in_data[0] = r, in_data[1] = c, in_data[2] = dir;
    push(in_data);

    while (1) {
        // stack이 하나 남았을 때까지
        if (head->next->next == tail)
            break;

        out_data = pop();
        x = out_data[0], y = out_data[1], d = out_data[2];
        free(out_data);

        // 8 개의 방향을 탐색
        for (int i = 0; i < 8; i++) {
            nx = x + dx[(d + i) % 8];
            ny = y + dy[(d + i) % 8];
            
            // 범위 안에 존재하며 라벨링이 필요한 부분인지 체크
            if (nx >= 0 && nx < 15 && ny >= 0 && ny < 15 && input_map[nx][ny] == 1) {
                input_map[nx][ny] = label; // 현재 라벨 값을 넣어줌
                in_data[0] = nx, in_data[1] = ny, in_data[2] = (d + i) % 8;
                push(in_data); // 조건에 만족하는 부분 stack에 push (다음에 탐색하기 위해)
            }
        }
    }

    // 동적할당한 메모리 해제
    free(in_data);
}