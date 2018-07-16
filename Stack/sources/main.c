#include "stack.h"

int main()
{
    linked_stack *stack = NULL;
    if (init_stack(&stack))
    {
        for (int i = 0; i < 5 ; i++)
        {
            if (push(stack, i))
                printf("push successfully: %d!\n", i);
        }
        printf("after push, the stack size is %d.\n", stack -> size);
        for (int i = 0; i < 5 ; i++)
        {
            printf("pop : %d.\n", pop(stack));
        }
        printf("after pop, the stack size is %d. \n", stack -> size);
    }

    return 0;
}