#ifndef STACK
#define STACK

/* ---------------- headers -------------------- */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* ---------------- macro define --------------- */
#define stack_type int


/* ---------------- struct declaration ------------ */

typedef struct stackItem
{
    stack_type value;
    struct stackItem *next;
} stackItem;

typedef struct stack
{
    int size;
    struct stackItem *next;
} linked_stack;

/* ----------------- method declaration ------------ */
bool init_stack(linked_stack **stack);

bool push(linked_stack *stack, stack_type value);

stack_type pop(linked_stack *stack);

void clear(linked_stack *stack);

#endif // STACK
