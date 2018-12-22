#include <stdio.h>
#include "537malloc.h"

#define SIZE 1000

int main() {
	int size = sizeof(int) * SIZE;
	int *ptr = malloc537(size);
	printf("Allocated %d bytes @ %p\n", size, ptr);

	printf("Freeing at %p + mid : Should fail - Invalid address!\n", ptr);
	free537(ptr + (size / 2));

	printf("--------------------------------------\n");
	printf("This statement should not be printed!\n");
	printf("--------------------------------------\n");

	return 0;
}
