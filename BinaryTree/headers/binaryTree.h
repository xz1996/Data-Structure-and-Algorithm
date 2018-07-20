#ifndef BINARY_TREE
#define BINARY_TREE

/* ------------- header reference --------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ---------------- struct declaration ------------ */

typedef struct btNode
{
    int data;
    struct btNode* lChild;
    struct btNode* rChild;
} BTNode;

/* ------------- method declaration -------------- */

BTNode* createBTree(int data[], int size);

BTNode* binaryTreeSearch(BTNode* tree, int data);

bool binaryTreeInsert(BTNode** tree, int data);

void preOrderRecursion(BTNode* tree);

void inOrderRecursion(BTNode* tree);

void postOrderRecursion(BTNode* tree);

void levelTraversal(BTNode* tree);

#endif // BINARY_TREE