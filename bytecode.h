#ifndef _BYTECODE_H
#define _BYTECODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "type.h"

typedef struct _Bytecode Bytecode;

typedef struct _Bytecode
{
    byte* code;
    int length;
    int realLength;
}Bytecode;

Bytecode* createBytecode(const byte* code);
void setBytecode(Bytecode* bytecode, const byte* code);
void addBytecode(Bytecode* bytecode, const byte* code);
void addByte(Bytecode* bytecode, byte code);

void freeBytecode(Bytecode* bytecode);

Bytecode* tokenToBytecode(TokenList* tokenList);

#endif
