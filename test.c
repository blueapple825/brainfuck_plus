#include <stdio.h>
#include "tokenizer.h"
#include "bytecode.h"

void printToken(Token* token)
{
    switch(token->type)
    {
        case 0:
            printf("ADD_POINTER(>, <)");
            break;
        case 1:
            printf("PUSH_POINTER(^)");
            break;
        case 2:
            printf("POP_POINTER(~)");
            break;
        case 3:
            printf("ADD_VALUE(+, -)");
            break;
        case 4:
            printf("PRINT(.)");
            break;
        case 5:
            printf("INPUT(,)");
            break;
        case 6:
            printf("LOOP_START([)");
            break;
        case 7:
            printf("LOOP_END(])");
            break;
        case 8:
            printf("SET_POINTER(*)");
            break;
        case 9:
            printf("NAME");
            break;
    }

    printf(": %d | %s\n", token->valueNumber, token->valueString);
}

int main()
{
    Bytecode* bytecode = createBytecode("test");
    printf("%s\b", bytecode->code);

    setBytecode(bytecode, "AAAAAAAAAAAAAAAAAA1");
    printf("%s\b", bytecode->code);

    addBytecode(bytecode, "TEST\n\nAAA!!!!!!!!!!1111111111111111111111111\na");
    printf("%s\b", bytecode->code);

    return 0;
}
