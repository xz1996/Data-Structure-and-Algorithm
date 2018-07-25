#include "stack.h"

bool init_stack(linked_stack** stack)
{
    *stack = (linked_stack *)malloc(sizeof(linked_stack));
    if (*stack == NULL)
    {
        printf("malloc error!\n");
        return false;
    }
    else
    {
        (*stack) -> size = 0;
        (*stack) -> next = NULL;
        return true;
    }
}

bool push(linked_stack* stack, stack_type value)
{
    if (stack == NULL)
        return false;

    stackItem *node = NULL;
    node = (stackItem *)malloc(sizeof(stackItem));
    if (node == NULL)
    {
        printf("malloc node error!\n");
        return false;
    }
    node -> value = value;
    node -> next = stack -> next;
    stack -> next = node;
    ++(stack -> size);
    return true;
}

stack_type pop(linked_stack* stack)
{
    if (stack == NULL || stack -> next == NULL)
        return (stack_type)NULL;
    else
    {
        stackItem* popItem = stack -> next;
        stack_type popValue = popItem -> value;
        stack -> next = popItem -> next;
        free(popItem);
        --(stack -> size);
        return popValue;
    }
}

stack_type getTop(linked_stack* stack)
{
    stackItem* topItem = stack -> next;
    if (stack == NULL || topItem == NULL)
        return NULL;
    else
        return topItem -> value;
}

void clear(linked_stack* stack)
{
    while(pop(stack) != (stack_type)NULL);
}

bool isEmptyStack(linked_stack* stack)
{
    if (stack == NULL || stack -> next == NULL)
        return true;
    else
        return false;
}