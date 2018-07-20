#include "binaryTree.h"

int main()
{
    int node[] = {4, 2, 5, 1, 3, 6};
    int size = 6;

    BTNode* tree = createBTree(node, size);
    printf("preOrder:\n");
    preOrderRecursion(tree);

    printf("\ninOrder:\n");
    inOrderRecursion(tree);

    printf("\npostOrder:\n");
    postOrderRecursion(tree);

    printf("\nlevel traversal:\n");
    levelTraversal(tree);
}