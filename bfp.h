#ifndef _BRAINFUCK_PLUS_H
#define _BRAINFUCK_PLUS_H

#include "bytecode.h"
#include "type.h"

typedef struct _BrainfuckPlus BrainfuckPlus;

typedef struct _BrainfuckPlus
{
    Bytecode* bytecode;
    byte memory[65536];
    unsigned short memoryPointer;
    unsigned int codePointer;
}BrainfuckPlus;

#endif
