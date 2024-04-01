#include <stdio.h>
#include <stdlib.h>

void swap(void* a, void* b, int size_t);

void main() {
	int i1 = 3, i2 = 9;
	printf("i1: %d, i2: %d\n", i1, i2);
	
	swap(&i1, &i2, sizeof(int));
	printf("i1: %d, i2: %d\n", i1, i2);
}

void swap(void* a, void* b, int size_t) {
	void* t;
	t = malloc(size_t);

	memcpy(t, a, size_t);
	memcpy(a, b, size_t);
	memcpy(b, t, size_t);

	free(t); // memory 할당 해제
}