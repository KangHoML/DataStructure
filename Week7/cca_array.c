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

int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int label = 1;

void init_stack();
int push(int* in_data);
int *pop();
void labeling(int x, int y);

void main() {
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            init_stack();
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

#define MAX 100
int* stack[MAX];
int top;

void init_stack() {
    top = -1;
}

int push(int *in_data) {
    if (top >= MAX-1)
        return -1;

    stack[++top] = in_data;
    return 1;
}

int *pop() {
    if (top < 0)
        return NULL;

    return stack[top--];
}

void labeling(int r, int c) {
    int x, y, d, nx, ny, flag;
    int *in_data, *out_data;
    
    in_data = (int *)calloc(3, sizeof(int));
    in_data[0] = r, in_data[1] = c, in_data[2] = 0;
    push(in_data);

    while(top > -1) {
        out_data = stack[top];
        x = out_data[0], y = out_data[1], d = out_data[2];
        flag = 0;
        
        for (int i = 0; i < 8; i++) {
            nx = x + dx[(d+i)%8];
            ny = y + dy[(d+i)%8];

            if (nx >= 0 && nx < 15 && ny >= 0 && ny < 15 && input_map[nx][ny] == 1) {
                if (x == r && y == c)
                    label++;
                input_map[nx][ny] = label;
                
                in_data = (int *)calloc(3, sizeof(int));
                in_data[0] = nx, in_data[1] = ny, in_data[2] = (d+i) % 8;
                push(in_data);

                flag = 1;
                break;
            }
        }

        if (flag == 0)
            pop();
    }

    free(in_data);
}