#ifndef _STACK_H
#define _STACK_H

#include <stdlib.h>

typedef struct _Stack Stack;

typedef struct _Stack
{
    Stack* nextStack;
    int value;
}Stack;

Stack* createStack(int value);
Stack* pushStack(Stack* stack, int value);
Stack* popStack(Stack* stack);

void freeStack(Stack* stack);

#endif
