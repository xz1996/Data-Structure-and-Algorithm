# Binary Tree (二叉树)

## Some Concepts

- Full Binary Tree (满二叉树)

    国内定义：所有分支结点都有左孩子和右孩子，并且叶子结点都集中在最下层的二叉树。

    ![full binary tree in China](https://baike.baidu.com/pic/%E6%BB%A1%E4%BA%8C%E5%8F%89%E6%A0%91/7773283/0/8ad4b31c8701a18be06a847b942f07082838fe05?fr=lemma&ct=single#aid=0&pic=2cf5e0fe9925bc31b16e97ac54df8db1cb1370d7)

    国际定义：A full binary tree is a tree in which every node has either 0 or 2 children.

    ![full binary tree in the world](https://en.wikipedia.org/wiki/Binary_tree#/media/File:Full_binary.svg)

- Complete Binary Tree (完全二叉树)

    将满二叉树```从右至左、从下到上```按顺序删除结点所得到的树。完全二叉树除了最下层以外，其他结点的度必然为2，即除去最下层的完全二叉树将得到满二叉树。

## Traversal Algorithm

### PreOrder (先序遍历)

- Recursion

    steps:

    1. 访问节点；

    2. 先序遍历左子树；

    3. 先序遍历右子树。

    code

    ```C
    void preOrderRecursion(BTNode* tree)
    {
        if (tree != NULL)
        {
            printf("%d ", tree -> data);
            preOrderRecursion(tree -> lChild);
            preOrderRecursion(tree -> rChild);
        }
    }
    ```
- Non-Recursion

    steps:

    1. 循环遍历左子树，访问结点，若是有右子树，将右子树入栈；

    2. 遍历到叶子结点时，出栈，并重复步骤1；

    3. 直到栈空，完毕。

    code:
    ```C
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
    ```

### InOrder (中序遍历)

- Recursion

    steps:

    1. 中序遍历左子树；

    2. 访问结点；

    3. 中序遍历右子树。

    code:
    ```C
    if (tree != NULL)
    {
        inOrderRecursion(tree -> lChild);
        printf("%d ", tree -> data);
        inOrderRecursion(tree -> rChild);
    }
    ```

- Non-Recursion

    steps:

    1. 循环遍历左子树并将结点入栈；

    2. 若结点无左子树，出栈，访问该结点，并将该结点的右子树当做起始位置，重复步骤1；

    3. 直到栈空并且遍历指针```nodeIndex```为NULL，完毕。

    针对step3，之所以要附加上遍历指针为NULL的条件是因为当循环遍历到根节点时，将根节点pop出去后此时栈为空，若此二叉树根节点有右子树，则此时根节点的右子树并未遍历完，因此不能以栈空作为结束循环的条件。

    code:
    ```C
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
    ```

### PostOrder (后序遍历)

- Recursion

    steps:

    1. 后序遍历左子树；

    2. 后序遍历右子树；

    3. 访问结点。

    code:
    ```C
    if (tree != NULL)
    {
        postOrderRecursion(tree -> lChild);
        postOrderRecursion(tree -> rChild);
        printf("%d ", tree -> data);
    }
    ```

- Non-Recursion

    后序遍历的非递归方法需要有额外的字段来记录结点是否被访问过

### Level (层次遍历)

steps:

1. 建立一个循环队列，并将二叉树的根节点入队列；

2. 若队列不为空，出队列，访问该结点，并将该结点的左孩子和右孩子入队列；

3. 不断重复步骤2，直到队列为空。

code:

```C
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
```