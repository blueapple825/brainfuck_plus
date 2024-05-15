#ifndef _BYTECODE_H
#define _BYTECODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

typedef struct _Bytecode Bytecode;

typedef struct _Bytecode
{
    char* code;
    int length;
    int realLength;
}Bytecode;

Bytecode* createBytecode(const char* code);
void setBytecode(Bytecode* bytecode, const char* code);
void addBytecode(Bytecode* bytecode, const char* code);

void tokenToBytecode(TokenList* tokenList);

#endif
