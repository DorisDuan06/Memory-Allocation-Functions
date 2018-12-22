#include <stdio.h>
#include "537malloc.h"

int main() {
	printf("Allocation 10 bytes of memory\n");
	char *ptr = malloc537(10);
	printf("Allocated addr : %p\n", ptr);

	printf("Reallocating for size 0 : should throw a warning, but continue\n");
	ptr = realloc537(ptr, 0);

	printf("--------------------------------------\n");
	printf("If this prints, well done!\n");
	printf("--------------------------------------\n");

	return 0;
}
