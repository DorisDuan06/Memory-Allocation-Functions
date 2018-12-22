/*
// Main File:      537malloc.c
// This File:      traverse.h
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

#ifndef _TRAVERSE_H_
#define _TRAVERSE_H_

void traverse_malloc(struct Node *node, void *ptr, size_t size);
int traverse_free(struct Node *node, void *ptr);
void traverse_memcheck(struct Node *node, void *ptr, long int length, int pass);

#endif