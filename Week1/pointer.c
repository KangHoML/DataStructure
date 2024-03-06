#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

/*
* 배열의 이름과 포인터는 서로 다름.
*/
void test(){
    int a[SIZE] = {1, 2, 3, 4, 5};
    int b[SIZE];
    int* p_a = a;

    // b = a; error -> 배열의 이름은 시작 주소가 아님

    printf("sizeof(%d)\n", sizeof(a));
    printf("sizeof(%d)\n", sizeof(p_a));
}
