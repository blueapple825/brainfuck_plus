#include <stdio.h>
#include "tokenizer.h"
#include "bytecode.h"
#include "bfp.h"

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
    runBrainfuckPlus("++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++++++++++++++.------------.<<+++++++++++++++.>.+++.------.--------.>+.");

/*    FunctionList* funcList = createFunctionList();

    TokenList* tokenList = tokenize("++{.}[+++++]+++");
    Bytecode* bytecode = tokenToBytecode(tokenList, 0, funcList, 0);

    printf("** token list**\n");
    for(int i = 0; i < tokenList->length; i++)
    {
        printToken(tokenList->list[i]);
    }

    printf("\n** function data **\n");
    for(int i = 0; i < funcList->length; i++)
    {
        FunctionData* data = funcList->list[i];
        printf("%s: %d\n", data->name, data->startPoint);
    }

    printf("\n** bytecode **\n");
    for(int i = 0; i < bytecode->length; i++)
    {
        printf("0x%02X\n", bytecode->code[i]);
    }

    freeFunctionList(funcList);
    freeTokenList(tokenList);
    freeBytecode(bytecode);*/

    return 0;
}
