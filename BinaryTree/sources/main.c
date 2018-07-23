#include "binaryTree.h"

int main()
{
    int node[] = {4, 2, 5, 1, 3, 6};
    int size = 6;
    BTNode* tree = createBTree(node, size);

    printf("------------------ Recursion ------------------\n\n");
    // Recursion.
    printf("preOrderRecursion:\n");
    preOrderRecursion(tree);
    printf("\n");

    printf("inOrderRecursion:\n");
    inOrderRecursion(tree);
    printf("\n");

    printf("postOrderRecursion:\n");
    postOrderRecursion(tree);
    printf("\n");

    printf("----------------- Non-Recursion ----------------\n\n");
    // Non-recursion.
    printf("preOrderNonRecursion:\n");
    preOrderNonRecursion(tree);
    printf("\n");

    printf("inOrderNonRecursion:\n");
    inOrderNonRecursion(tree);
    printf("\n");

    printf("level traversal:\n");
    levelTraversal(tree);
    printf("\n");

    clearTree(tree);
}