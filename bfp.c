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
        case 0x01: // ADD_POINTER, PADD
        {
            bfp->codePointer++;
            bfp->memoryPointer += code[bfp->codePointer];
            break;
        }
        case 0x02: // SUB_POINTER, PSUB
        {
            bfp->codePointer++;
            bfp->memoryPointer -= code[bfp->codePointer];
            break;
        }
        case 0x03: // PUSH_POINTER, PPUSH
        {
            bfp->pointerStack = pushStack(bfp->pointerStack, bfp->memoryPointer);
            break;
        }
        case 0x04: // POP_POINTER, PPOP
        {
            bfp->memoryPointer = bfp->pointerStack->value;
            bfp->pointerStack = popStack(bfp->pointerStack);
            break;
        }
        case 0x05: // ADD_VALUE, VADD
        {
            bfp->codePointer++;
            bfp->memory[bfp->memoryPointer] += code[bfp->codePointer];
            break;
        }
        case 0x06: // SUB_VALUE, VSUB
        {
            bfp->codePointer++;
            bfp->memory[bfp->memoryPointer] -= code[bfp->codePointer];
            break;
        }
        case 0x07: // PRINT, OUT
        {
            printf("%c", bfp->memory[bfp->memoryPointer]);
            break;
        }
        case 0x08: // INPUT, IN
        {
            scanf("%c", &bfp->memory[bfp->memoryPointer]);
            break;
        }
        case 0x09: // ?, ZJMP
        {
            bfp->codePointer++;

            if(bfp->memory[bfp->memoryPointer] == 0)
            {
                int jmpDist = 0;
                for(int i = 0; i < 4; i++)
                {
                    jmpDist <<= 8;
                    jmpDist += code[bfp->codePointer];
                    bfp->codePointer++;
                }

                bfp->codePointer = jmpDist;
            }
            else
            {
                bfp->codePointer += 3;
            }

            break;
        }
        case 0x0A: // ?, NZJMP
        {
            bfp->codePointer++;

            if(bfp->memory[bfp->memoryPointer] != 0)
            {
                int jmpDist = 0;
                for(int i = 0; i < 4; i++)
                {
                    jmpDist <<= 8;
                    jmpDist += code[bfp->codePointer];
                    bfp->codePointer++;
                }

                bfp->codePointer = jmpDist;
            }
            else
            {
                bfp->codePointer += 3;
            }

            break;
        }
        case 0x0B: // ?, CPUSH
        {
            bfp->codePointerStack = pushStack(bfp->codePointerStack, bfp->codePointer + 5);
            break;
        }
        case 0x0C: // ?, CPOP
        {
            bfp->codePointer = bfp->codePointerStack->value;
            bfp->codePointerStack = popStack(bfp->codePointerStack);
            break;
        }
        case 0x0D: // SET_POINTER, SPNT
        {
            bfp->memoryPointer = bfp->memory[bfp->memoryPointer];
            break;
        }
        case 0x0E: // ?, JMP
        {
            bfp->codePointer++;

            int jmpDist = 0;
            for(int i = 0; i < 4; i++)
            {
                jmpDist <<= 8;
                jmpDist += code[bfp->codePointer];
                bfp->codePointer++;
            }

            bfp->codePointer = jmpDist;

            break;
        }
    }
    bfp->codePointer++;
}

void freeBrainfuckPlus(BrainfuckPlus* bfp)
{
    freeBytecode(bfp->bytecode);
    freeStack(bfp->pointerStack);
    freeStack(bfp->codePointerStack);
    free(bfp);
}

void runBrainfuckPlus(const char* code)
{
    SubroutineList* subList = createSubroutineList();

    TokenList* tokenList = tokenize(code);
    Bytecode* bytecode = tokenToBytecode(tokenList, 0, subList, 0);
    freeSubroutineList(subList);

    BrainfuckPlus* bfp = setupBrainfuckPlus(bytecode);
    freeTokenList(tokenList);

    while(bfp->codePointer <= bfp->bytecode->length)
    {
        stepBrainfuckPlus(bfp);
    }

    freeBrainfuckPlus(bfp);
}
