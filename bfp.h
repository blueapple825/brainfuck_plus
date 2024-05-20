#ifndef _BRAINFUCK_PLUS_H
#define _BRAINFUCK_PLUS_H

#include "bytecode.h"
#include "type.h"
#include "stack.h"

typedef struct _BrainfuckPlus BrainfuckPlus;

typedef struct _BrainfuckPlus
{
    Bytecode* bytecode;
    byte memory[65536];
    Stack* pointerStack;
    Stack* codePointerStack;
    unsigned short memoryPointer;
    unsigned int codePointer;
}BrainfuckPlus;

BrainfuckPlus* setupBrainfuckPlus(Bytecode* bytecode);

void stepBrainfuckPlus(BrainfuckPlus* brainfuckPlus);
void freeBrainfuckPlus(BrainfuckPlus* brainfuckPlus);

void runBrainfuckPlus(const char* code);

#endif
