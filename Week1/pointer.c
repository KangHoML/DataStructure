#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

/*
* 배열의 이름과 포인터는 서로 다름.
*/
void test(){
    int a[SIZE] = {1, 2, 3, 4, 5};
    int b[SIZE];
    int* p_a = &a;

    // b = a; error -> size가 서로 다름

    printf("sizeof(%d)\n", sizeof(a));
    printf("sizeof(%d)", sizeof(p_a));
}
