#include "stack.h"

Stack* createStack(int value)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->value = value;
    stack->nextStack = NULL;

    return stack;
}

Stack* pushStack(Stack* stack, int value)
{
    Stack* newStack = createStack(value);
    newStack->nextStack = stack;

    return newStack;
}

Stack* popStack(Stack* stack)
{
    Stack* nextStack = stack->nextStack;
    free(stack);

    return nextStack;
}

void freeStack(Stack* stack)
{
    Stack* temp;
    while(stack != NULL)
    {
        temp = stack;
        stack = stack->nextStack;
        free(temp);
    }
}
