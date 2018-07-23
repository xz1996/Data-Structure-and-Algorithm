#include "binaryTree.h"
#include "loopQueue.h"
#include "stack.h"

BTNode* createBTree(int data[], int size)
{
    BTNode *bTree = NULL;
    for (int i = 0; i < size; i++)
    {
        binaryTreeInsert(&bTree, data[i]);
    }
    return bTree;
}

BTNode* binaryTreeSearch(BTNode* tree, int data)
{
    if (tree -> data == data)
        return tree;

    if (tree -> data < data)
        return binaryTreeSearch(tree -> rChild, data);
    else
        return binaryTreeSearch(tree -> lChild, data);
}

bool binaryTreeInsert(BTNode** tree, int data)
{
    if (*tree == NULL)
    {
       *tree = (BTNode *)malloc(sizeof(BTNode));
       (*tree) -> data = data;
       (*tree) -> lChild = NULL;
       (*tree) -> rChild = NULL;
       return true;
    }
    if ((*tree) -> data == data)
    {
        printf("the node has existed, please insert another one.\n");
        return false;
    }

    if ((*tree) -> data < data)
        return binaryTreeInsert(&((*tree) -> rChild), data);
    else
        return binaryTreeInsert(&((*tree) -> lChild), data);
}

void preOrderRecursion(BTNode* tree)
{
    if (tree != NULL)
    {
        printf("%d ", tree -> data);
        preOrderRecursion(tree -> lChild);
        preOrderRecursion(tree -> rChild);
    }
}

void inOrderRecursion(BTNode* tree)
{
    if (tree != NULL)
    {
        inOrderRecursion(tree -> lChild);
        printf("%d ", tree -> data);
        inOrderRecursion(tree -> rChild);
    }
}

void postOrderRecursion(BTNode* tree)
{
    if (tree != NULL)
    {
        postOrderRecursion(tree -> lChild);
        postOrderRecursion(tree -> rChild);
        printf("%d ", tree -> data);
    }
}

void preOrderNonRecursion(BTNode* tree)
{
    linked_stack* stack = NULL;
    if (init_stack(&stack))
    {
        push(stack, tree);
        while(!isEmptyStack(stack))
        {
            stack_type btnode = pop(stack);
            while(btnode != NULL)
            {
                printf("%d ", btnode -> data);
                if (btnode -> rChild)
                    push(stack, btnode -> rChild);

                btnode = btnode -> lChild;
            }
        }
        free(stack);
    }
}

void inOrderNonRecursion(BTNode* tree)
{
    linked_stack* stack = NULL;
    if (init_stack(&stack))
    {
        stack_type nodeIndex = tree;
        do
        {
            while (nodeIndex != NULL)
            {
                push(stack, nodeIndex);
                nodeIndex = nodeIndex -> lChild;
            }
            nodeIndex = pop(stack);
            printf("%d ", nodeIndex -> data);
            nodeIndex = nodeIndex -> rChild;
        } while ((!isEmptyStack(stack)) || (nodeIndex != NULL));
        free(stack);
    }
}

void postOrderNonRecursion(BTNode* tree)
{
    /*
        It needs extra flag field to mark that it has been visited.
    */
}

void levelTraversal(BTNode* tree)
{
    if (tree != NULL)
    {
        // Loop queue initialization.
        LoopQueue loopQ;
        loopQ.front = 0;
        loopQ.rear = 0;
        LoopQueue* loopQueue = &loopQ;

        // Enqueue the root node.
        if (!enqueue(loopQueue, tree))
            return;

        while (!isEmpty(loopQueue))
        {
            // Dequeue and visit the node.
            BTNode* node = dequeue(loopQueue);
            printf( "%d ", node -> data);

            // Enqueue if there is left child tree or right one.
            if (node -> lChild != NULL)
            {
                enqueue(loopQueue, node -> lChild);
            }
            if (node -> rChild != NULL)
            {
                enqueue(loopQueue, node -> rChild);
            }
        }
    }
}

void clearTree(BTNode* tree)
{
    if (tree != NULL)
    {
        clearTree(tree -> lChild);
        clearTree(tree -> rChild);
        free(tree);
    }
}
