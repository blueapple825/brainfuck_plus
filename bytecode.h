#ifndef _BYTECODE_H
#define _BYTECODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "type.h"

typedef struct _SubroutineData SubroutineData;
typedef struct _SubroutineList SubroutineList;

typedef struct _Bytecode Bytecode;

typedef struct _SubroutineData
{
    char name[33];
    unsigned int startPoint;
}SubroutineData;

typedef struct _SubroutineList
{
    SubroutineData** list;
    int length;
    int realLength;
}SubroutineList;

typedef struct _Bytecode
{
    byte* code;
    int length;
    int realLength;
    int tokenCount;
}Bytecode;

SubroutineList* createSubroutineList();
void addSubroutineData(SubroutineList* list, char name[33], int startPoint);

void freeSubroutineList(SubroutineList* list);

Bytecode* createBytecode(const byte* code);
void setBytecode(Bytecode* bytecode, const byte* code);
void addBytecode(Bytecode* bytecode, Bytecode* newCode);
void addByte(Bytecode* bytecode, byte code);

void freeBytecode(Bytecode* bytecode);

Bytecode* tokenToBytecode(TokenList* tokenList, int startPoint, SubroutineList* funcList, int offset);

#endif
