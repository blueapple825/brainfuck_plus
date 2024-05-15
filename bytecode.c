#include "bytecode.h"

Bytecode* createBytecode(const char* code)
{
    Bytecode* bytecode = (Bytecode*)malloc(sizeof(Bytecode));
    bytecode->length = strlen(code);
    bytecode->realLength = bytecode->length * 1.5;

    bytecode->code = (char*)malloc(sizeof(char) * bytecode->realLength);
    strcpy(bytecode->code, code);

    return bytecode;
}

void setBytecode(Bytecode* bytecode, const char* code)
{
    bytecode->length = strlen(code);
    bytecode->realLength = bytecode->length * 1.5;

    bytecode->code = (char*)realloc(bytecode->code, bytecode->realLength);
    strcpy(bytecode->code, code);
}

void addBytecode(Bytecode* bytecode, const char* code)
{
    int originalLength = bytecode->length;
    bytecode->length = strlen(code);
    if(bytecode->length >= bytecode->realLength)
    {
        bytecode->realLength = bytecode->length * 1.5;
        bytecode->code = (char*)realloc(bytecode->code, bytecode->realLength);
    }

    strcpy(bytecode->code + originalLength, code);
}

void tokenToBytecode(TokenList* tokenList)
{
    // TODO: 만들기 귀찮다. 오늘 학교 끝나고 ㄱ
}
