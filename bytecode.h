#ifndef _BYTECODE_H
#define _BYTECODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "type.h"

typedef struct _FunctionData FunctionData;
typedef struct _FunctionList FunctionList;

typedef struct _Bytecode Bytecode;

typedef struct _FunctionData
{
    char name[33];
    unsigned int startPoint;
}FunctionData;

typedef struct _FunctionList
{
    FunctionData** list;
    int length;
    int realLength;
}FunctionList;

typedef struct _Bytecode
{
    byte* code;
    int length;
    int realLength;
    int tokenCount;
}Bytecode;

FunctionList* createFunctionList();
void addFunctionData(FunctionList* list, char name[33], int startPoint);

void freeFunctionList(FunctionList* list);

Bytecode* createBytecode(const byte* code);
void setBytecode(Bytecode* bytecode, const byte* code);
void addBytecode(Bytecode* bytecode, const byte* code);
void addByte(Bytecode* bytecode, byte code);

void freeBytecode(Bytecode* bytecode);

Bytecode* tokenToBytecode(TokenList* tokenList, int startPoint, FunctionList* funcList, int offset);

#endif
