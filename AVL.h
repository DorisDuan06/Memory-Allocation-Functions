/*
// Main File:      537malloc.c
// This File:      AVL.h
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

#ifndef _AVL_H_
#define _AVL_H_

// An AVL tree node
struct Node { 
    void *addr;
    size_t len;
    struct Node *left;
    struct Node *right;
    int height;
    int flag;  // allocated: flag = 1, freed: flag = 0
} *root;

int height(struct Node *N);
struct Node *create(int *addr, size_t size);
struct Node *rightRotate(struct Node *y);
struct Node *leftRotate(struct Node *x);
int getBalance(struct Node *N);
struct Node *addNode(struct Node* node, void *addr, size_t size);
struct Node *minValueNode(struct Node* node);
struct Node *deleteNode(struct Node* root, void *addr);

#endif