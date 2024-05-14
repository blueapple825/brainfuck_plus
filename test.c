#include <stdio.h>
#include "tokenizer.h"

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
    TokenList* tokenList = tokenize(">>>>]>");
    printToken(tokenList->list[1]);

    printf("test\n");

    freeTokenList(tokenList);

    return 0;
}
