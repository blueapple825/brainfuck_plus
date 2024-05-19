#include <stdio.h>
#include "bytecode.h"

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
    Bytecode* bytecode = createBytecode("test");
    addByte(bytecode, '1');
    addByte(bytecode, '2');
    addByte(bytecode, '3');
    addByte(bytecode, '4');
    addByte(bytecode, '5');
    addByte(bytecode, '6');
    addByte(bytecode, '7');
    addByte(bytecode, '8');
    addByte(bytecode, '9');
    addByte(bytecode, 'A');
    addByte(bytecode, 'B');
    addByte(bytecode, 'C');
    addByte(bytecode, 'D');
    addByte(bytecode, 'E');
    addByte(bytecode, 'F');

    printf("%s\n", bytecode->code);
    printf("%d %d\n", bytecode->length, bytecode->realLength);

    return 0;
}
