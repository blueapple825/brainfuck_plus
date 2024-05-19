#include "bfp.h"

BrainfuckPlus* setupBrainfuckPlus(Bytecode* bytecode)
{
    BrainfuckPlus* bfp = (BrainfuckPlus*)malloc(sizeof(BrainfuckPlus));
    bfp->bytecode = bytecode;
    bfp->pointerStack = createStack(0);
    bfp->memoryPointer = 0;
    bfp->codePointer = 0;

    for(int i = 0; i < 65536; i++)
    {
        bfp->memory[i] = 0;
    }

    return bfp;
}

void stepBrainfuckPlus(BrainfuckPlus* bfp)
{
    byte* code = bfp->bytecode->code;
    switch(code[bfp->codePointer])
    {
        case 0x01: // ADD_POINTER
        {
            bfp->codePointer++;
            bfp->memoryPointer += code[bfp->codePointer];
            break;
        }
        case 0x02: // SUB_POINTER
        {
            bfp->codePointer++;
            bfp->memoryPointer -= code[bfp->codePointer];
            break;
        }
        case 0x03: // PUSH_POINTER
        {
            bfp->pointerStack = pushStack(bfp->pointerStack, bfp->memoryPointer);
            break;
        }
        case 0x04: // POP_POINTER
        {
            bfp->memoryPointer = bfp->pointerStack->value;
            bfp->pointerStack = popStack(bfp->pointerStack);
            break;
        }
        case 0x05: // ADD_VALUE
        {
            bfp->codePointer++;
            bfp->memory[bfp->memoryPointer] += code[bfp->codePointer];
            break;
        }
        case 0x06: // SUB_VALUE
        {
            bfp->codePointer++;
            bfp->memory[bfp->memoryPointer] -= code[bfp->codePointer];
            break;
        }
        case 0x07: // PRINT
        {
            printf("%c", bfp->memory[bfp->memoryPointer]);
            break;
        }
        case 0x08: // INPUT
        {
            scanf("%c", &bfp->memory[bfp->memoryPointer]);
            break;
        }
    }
    bfp->codePointer++;
}

void freeBrainfuckPlus(BrainfuckPlus* bfp)
{
    freeBytecode(bfp->bytecode);
    freeStack(bfp->pointerStack);
    free(bfp);
}

void runBrainfuckPlus(const char* code)
{
    TokenList* tokenList = tokenize(code);
    Bytecode* bytecode = tokenToBytecode(tokenList);
    BrainfuckPlus* bfp = setupBrainfuckPlus(bytecode);
    freeTokenList(tokenList);

    while(bfp->codePointer <= bfp->bytecode->length)
    {
        stepBrainfuckPlus(bfp);
    }

    freeBrainfuckPlus(bfp);
}
