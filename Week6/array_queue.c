#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int queue[MAX];
int front, rear;

void init_queue();
int put(int key);
int get();
void clear_queue();
void print_queue();

void main() {
    int k;
    init_queue();
    
    put(3);
    put(6);
    put(9);
    put(1);
    put(6);
    put(3);
    print_queue();

    get();
    print_queue();

    put(4);
    put(8);
    put(7);
    put(2);
    put(0); // queue overflow
    print_queue();

    init_queue();
    get(); // queue underflow
}

void init_queue() {
    front = 0;
    rear = 0;
}

// rear부터 넣기
int put(int key) {
    if (((rear+1) % MAX) == front) {
        printf("Queue Overflow !\n");
        return -1;
    }

    queue[rear] = key;
    rear = ++rear% MAX;

    return key;
}

// front부터 꺼내기
int get() {
    int key;

    if (front == rear) {
        printf("Queue Underflow !\n");
        return -1;
    }

    key = queue[front];
    front = ++front % MAX;

    return key;
}

// 실제로는 값이 들어있지만 커서를 옮겨 없는 것처럼 동작
void clear_queue() {
    front = rear;    
}

void print_queue() {
    // 나머지를 통해 front와 rear가 같기 전까지 전부 출력
    for (int k = front; k != rear; k = ++k % MAX) {
        printf("%-6d", queue[k]);
    }
    printf("\n");
}


