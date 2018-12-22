/*
// Main File:      537malloc.c
// This File:      537malloc.h
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

#ifndef _537MALLOC_H_
#define _537MALLOC_H_

void *malloc537(size_t size);
void free537(void *ptr);
void *realloc537(void *ptr, size_t size);
void memcheck537(void *ptr, size_t size);

#endif