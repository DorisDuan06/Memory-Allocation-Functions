/*
// Main File:      537malloc.c
// This File:      537malloc.c
//
// Author:         Yanjia Duan
// Email:          duan35@wisc.edu
// CS Login:       yanjia
//
// Author:         Zexing Li
// Email:          zli674@wisc.edu
// CS Login:       zexing
//
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "537malloc.h"
#include "AVL.h"
#include "traverse.h"

void *malloc537(size_t size) {
    if (size == 0)
        printf("Warning: Malloc zero size!\n");
    void *ptr = (void *)malloc(size);
    if (ptr == NULL) {
        printf("Error: Malloc fail!\n");
        exit (-1);
    }
    traverse_malloc(root, ptr, size);
    
    return ptr;
}

// check_free = 0: allocated, 1: not allocated, 2: not first byte in free, 3: not first byte in allocated, 4: double free
void free537(void *ptr) {
    int check_free = traverse_free(root, ptr);
    if (check_free == 1 || check_free == 2) {
        printf("Error: Freeing a memory that has not been allocated with malloc537()!\n");
        exit (-1);
    }
    if (check_free == 3) {
        printf("Error: Freeing a memory that has is not the first byte of the range!\n");
        exit (-1);
    }
    if (check_free == 4) {
        printf("Error: Freeing a memory that has was previously freed!\n");
        exit (-1);
    }
    free(ptr);
}

// status = 0: allocated, 1: not allocated, 2: not first byte in free, 3: not first byte in allocated, 4: double free
void *realloc537(void *ptr, size_t size) {
    if (ptr == NULL)
        ptr = malloc537(size);
    else if (size == 0) {
        printf("Warning: Realloc zero size!\n");
        free537(ptr);
    }
    else {
        int status = traverse_free(root, ptr);  // get the free status
        if (status == 3)  // if ptr is already freed
            ptr = malloc537(size);
        else if (status == 0) {  // if ptr is allocated
            root = deleteNode(root, ptr);
            ptr = realloc(ptr, size);
            root = addNode(root, ptr, size);
        }
    }
    return ptr;
}

void memcheck537(void *ptr, size_t size) {
    traverse_memcheck(root, ptr, (long)size, 0);
}