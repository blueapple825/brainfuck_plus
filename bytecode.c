#include "bytecode.h"

Bytecode* createBytecode(const byte* code)
{
    Bytecode* bytecode = (Bytecode*)malloc(sizeof(Bytecode));
    bytecode->length = strlen(code);
    bytecode->realLength = bytecode->length * 1.5;

    bytecode->code = (byte*)malloc(sizeof(byte) * bytecode->realLength);
    strcpy(bytecode->code, code);

    return bytecode;
}

void setBytecode(Bytecode* bytecode, const byte* code)
{
    bytecode->length = strlen(code);
    bytecode->realLength = bytecode->length * 1.5;

    bytecode->code = (byte*)realloc(bytecode->code, bytecode->realLength);
    strcpy(bytecode->code, code);
}

void addBytecode(Bytecode* bytecode, const byte* code)
{
    int originalLength = bytecode->length;
    bytecode->length = strlen(code);
    if(bytecode->length >= bytecode->realLength)
    {
        bytecode->realLength = bytecode->length * 1.5;
        bytecode->code = (byte*)realloc(bytecode->code, bytecode->realLength);
    }

    strcpy(bytecode->code + originalLength, code);
}

void addByte(Bytecode* bytecode, byte code)
{
    int originalLength = bytecode->length;
    bytecode->length += 1;
    if(bytecode->length >= bytecode->realLength)
    {
        bytecode->realLength = bytecode->length * 1.5;
        bytecode->code = (byte*)realloc(bytecode->code, bytecode->realLength);
    }

    bytecode->code[originalLength] = code;
    bytecode->code[originalLength + 1] = 0;
}

Bytecode* tokenToBytecode(TokenList* tokenList)
{
    Bytecode* bytecode = createBytecode("");

    for(int i = 0; i < tokenList->length; i++)
    {
        Token* token = tokenList->list[i];
        switch(token->type)
        {
        case ADD_POINTER:
            {
                addByte(bytecode, 0x01);
                addByte(bytecode, token->valueNumber);
                break;
            }
        case SUB_POINTER:
            {
                addByte(bytecode, 0x02);
                addByte(bytecode, token->valueNumber);
                break;
            }
        case PUSH_POINTER:
            {
                addByte(bytecode, 0x03);
                break;
            }
        case POP_POINTER:
            {
                addByte(bytecode, 0x04);
                break;
            }
        case ADD_VALUE:
            {
                addByte(bytecode, 0x05);
                addByte(bytecode, token->valueNumber);
                break;
            }
        case SUB_VALUE:
            {
                addByte(bytecode, 0x06);
                addByte(bytecode, token->valueNumber);
                break;
            }
        case PRINT:
            {
                addByte(bytecode, 0x07);
                break;
            }
        case INPUT:
            {
                addByte(bytecode, 0x08);
                break;
            }
        case SET_POINTER:
            {
                addByte(bytecode, 0x0C);
                break;
            }
        }
    }

    return bytecode;
}

void freeBytecode(Bytecode* bytecode)
{
    free(bytecode->code);
    free(bytecode);
}
