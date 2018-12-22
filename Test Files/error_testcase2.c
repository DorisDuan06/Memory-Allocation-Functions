#include <stdio.h>
#include "537malloc.h"

#define SIZE 1000

int main() {
	int *ptr = malloc537(SIZE);
	printf("Allocated %d bytes @ %p\n", SIZE, ptr);

	printf("Freeing at %p + 5 : Should fail - Not a start address!\n", ptr);
	free537(ptr + 5);

	printf("--------------------------------------\n");
	printf("This statement should not be printed!\n");
	printf("--------------------------------------\n");

	return 0;
}
