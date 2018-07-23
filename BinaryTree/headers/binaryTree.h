#ifndef BINARY_TREE
#define BINARY_TREE

/* ------------- header reference --------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ---------------- macro define --------------- */

typedef int BT_DATA;

/* ---------------- struct declaration ------------ */

typedef struct btNode
{
    BT_DATA data;
    struct btNode* lChild;
    struct btNode* rChild;
} BTNode;

/* ------------- method declaration -------------- */

BTNode* createBTree(BT_DATA data[], int size);

BTNode* binaryTreeSearch(BTNode* tree, BT_DATA data);

bool binaryTreeInsert(BTNode** tree, BT_DATA data);

void preOrderRecursion(BTNode* tree);

void inOrderRecursion(BTNode* tree);

void postOrderRecursion(BTNode* tree);

void preOrderNonRecursion(BTNode* tree);

void inOrderNonRecursion(BTNode* tree);

void postOrderNonRecursion(BTNode* tree);

void levelTraversal(BTNode* tree);

void clearTree(BTNode* tree);

#endif // BINARY_TREE