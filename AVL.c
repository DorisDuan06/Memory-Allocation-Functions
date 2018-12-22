/*
// Main File:      537malloc.c
// This File:      AVL.c
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
#include "537malloc.h"
#include "AVL.h"

// A utility function to get height of the tree 
int height(struct Node *N) { 
    if (N == NULL) 
        return 0; 
    return N->height; 
}

/* Helper function that allocates a new node with the given addr and NULL left and right pointers. */
struct Node *create(int *addr, size_t size) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->addr = addr;
    node->len = size;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // new node is initially added at leaf
    node->flag = 1;
    return node;
}

// Right rotate subtree with root y
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right; 

    x->right = y;
    y->left = T2;

    // Update heights
    y->height = (height(y->left) > height(y->right))? height(y->left) : height(y->right) + 1;
    x->height = (height(x->left) > height(x->right))? height(x->left) : height(x->right) + 1;

    return x;
}
  
// Left rotate subtree with root x
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    // Update heights
    x->height = (height(x->left) > height(x->right))? height(x->left) : height(x->right) + 1;
    y->height = (height(y->left) > height(y->right))? height(y->left) : height(y->right) + 1;

    return y;
}

// Get Balance factor of node N
int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
  
struct Node *addNode(struct Node* node, void *addr, size_t size) {
    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
        return create(addr, size);

    if (addr < node->addr)
        node->left  = addNode(node->left, addr, size);
    else if (addr > node->addr)
        node->right = addNode(node->right, addr, size);
    else // Equal addrs not allowed
        return node;

    /* 2. Update height of this ancestor node */
    node->height = (height(node->left) > height(node->right))? height(node->left) : height(node->right) + 1;

    /* 3. Get the balance factor of this ancestor node to check whether this node became unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && addr < node->left->addr)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && addr > node->right->addr)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && addr > node->left->addr) {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && addr < node->right->addr) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

/* Given a non-empty binary search tree, return the node with minimum addr value found in that tree. Note that the entire tree does not need to be searched. */
struct Node *minValueNode(struct Node* node) {
    struct Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Recursive function to delete a node with given addr from subtree with given root. It returns root of the modified subtree.
struct Node *deleteNode(struct Node* root, void *addr) {
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL)
        return root;

    // If the addr to be deleted is smaller than the root's addr, then it lies in left subtree
    if (addr < root->addr)
        root->left = deleteNode(root->left, addr);

    // If the addr to be deleted is greater than the root's addr, then it lies in right subtree
    else if(addr > root->addr)
        root->right = deleteNode(root->right, addr);

    // if addr is same as root's addr, then This is the node to be deleted
    else {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) ) {
            struct Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of the non-empty child
            free(temp);
        }
        else {
            // node with two children: Get the inorder successor (smallest in the right subtree)
            struct Node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->addr = temp->addr;
            
            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->addr);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
      return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = (height(root->left) > height(root->right))? height(root->left) : height(root->right) + 1;

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
