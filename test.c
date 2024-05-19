#include <stdio.h>
#include "tokenizer.h"
#include "bytecode.h"
#include "stack.h"

void printToken(Token* token)
{
    switch(token->type)
    {
        case 0:
            printf("ADD_POINTER(>)");
            break;
        case 1:
            printf("SUB_POINTER(<)");
            break;
        case 2:
            printf("PUSH_POINTER(^)");
            break;
        case 3:
            printf("POP_POINTER(~)");
            break;
        case 4:
            printf("ADD_VALUE(+)");
            break;
        case 5:
            printf("SUB_VALUE(-)");
            break;
        case 6:
            printf("PRINT(.)");
            break;
        case 7:
            printf("INPUT(,)");
            break;
        case 8:
            printf("LOOP_START([)");
            break;
        case 9:
            printf("LOOP_END(])");
            break;
        case 10:
            printf("SET_POINTER(*)");
            break;
        case 11:
            printf("NAME");
            break;
    }

    printf(": %d | %s\n", token->valueNumber, token->valueString);
}

int main()
{
    Stack* stack = createStack(0);
    for(int i = 1; i <= 10; i++)
    {
        stack = pushStack(stack, i);
    }

    for(int i = 0; i < 10; i++)
    {
        printf("%d\n", stack->value);
        stack = popStack(stack);
    }
    printf("%d\n", stack->value);

    freeStack(stack);

    return 0;
}
