#ifndef _BYTECODE_H
#define _BYTECODE_H

#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

typedef struct _Bytecode Bytecode;

typedef struct _Bytecode
{
    char* code;
    int length;
    int realLength;
}Bytecode;

void tokenToBytecode(TokenList* tokenList);

#endif
