#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "537malloc.h"

int main() {
	void *ptr;
        void *newptr;
	void *tempptr;

	ptr = malloc537(4096);
	uint64_t temp = (uint64_t) ptr;
	printf("malloc537, Address : %p, [%p], [%p]\n", ptr, ptr+4096, (int *)temp);
	printf("free537, Address : %p\n", ptr);
	free537(ptr);
	
	tempptr = malloc(1024);
	printf("malloc, Address : %p\n", tempptr);

	newptr = malloc537(1024);
	printf("malloc537, Address : %p, [%p]\n", newptr, newptr+1024);
	assert((uint64_t)(newptr+1024) < (temp+4096) );
	assert((uint64_t)(newptr) > (temp) );
	
	printf("free537, Address : %p\n", newptr);
	free537(newptr);
	printf("free, Address : %p\n", tempptr);
	free(tempptr);
	printf("If this prints, well done!!\n\nNext line[Double free] should be an error:\n");
	free537((void*)temp);
}
