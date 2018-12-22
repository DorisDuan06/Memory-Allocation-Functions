/*
// Main File:      537malloc.c
// This File:      traverse.c
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

// Insert the allocated node, check if there are freed nodes to delete
void traverse_malloc(struct Node *node, void *ptr, size_t size) {
    if (node != NULL) {
        if (node->addr == ptr) {
            node->flag = 1;
            node->len = size;
        }
        else if ((long)node->addr + (long)node->len < (long)ptr)
            traverse_malloc(node->right, ptr, size);
        else if ((long)node->addr > (long)ptr + (long)size)
            traverse_malloc(node->left, ptr, size);
        else if (node->addr < ptr && (long)ptr <= (long)node->addr + (long)node->len) {
            node->len = (long)ptr - (long)node->addr;
            traverse_malloc(node->right, ptr, size);
        }
        else if (ptr < node->addr && (long)node->addr < (long)ptr + (long)size) {
            root = deleteNode(root, node->addr);
            free(node->addr);
            traverse_malloc(root, ptr, size);
        }
        else if (ptr < node->addr && (long)node->addr + (long)node->len <= (long)ptr + (long)size) {
            root = deleteNode(root, node->addr);
            free(node->addr);
            traverse_malloc(root, ptr, size);
        }
    }
    else
        root = addNode(root, ptr, size);
}

// Find a node with addr = ptr, return 0: allocated, 1: not allocated, 2: not first byte in free, 3: not first byte in allocated, 4: double free
int traverse_free(struct Node *node, void *ptr) {
    int val = 1;
    if (node != NULL) {
        if (node->addr == ptr)
            if (node->flag == 1) {
                node->flag = 0;
                return 0;
            }
            else
               return 4; 
        else if (node->addr < ptr && (long)ptr < (long)node->addr + (long)node->len)
            if (node->flag == 0)
                return 2;
            else
                return 3;
        else if (node->addr < ptr)
            val = traverse_free(node->right, ptr);
        else if (node->addr > ptr)
            val = traverse_free(node->left, ptr);
    }
    return val;
}

void traverse_memcheck(struct Node *node, void *ptr, long int length, int pass) {
    if (node != NULL) {
        if (node->addr <= ptr && (long)ptr <= (long)node->addr + (long)node->len)
            if((long)ptr + length > (long)node->addr + (long)node->len) {
                printf("Error: Allocated memory not have enough size!\n");
                exit (-1);
            }
            else
                pass = 1;
        else if ((long)ptr > (long)node->addr + (long)node->len)
            traverse_memcheck(node->right, ptr, length, pass);
        else
            traverse_memcheck(node->left, ptr, length, pass);
    }
    else if (pass == 0){
        printf("Error: Given address not allocated!\n");
        exit (-1);
    }
}