#include "bytecode.h"

FunctionList* createFunctionList()
{
    FunctionList* list = (FunctionList*)malloc(sizeof(FunctionList));
    list->list = malloc(0);
    list->length = 0;
    list->realLength = 0;

    return list;
}

void addFunctionData(FunctionList* list, char name[33], int startPoint)
{
    FunctionData* data = (FunctionData*)malloc(sizeof(FunctionData));
    strcpy(data->name, name);
    data->startPoint = startPoint;

    int originalLength = list->length;
    list->length += 1;
    if(list->length >= list->realLength)
    {
        list->realLength = list->length * 1.5;
        list->list = (FunctionData**)realloc(list->list, list->realLength);
    }

    list->list[originalLength] = data;
}

void freeFunctionList(FunctionList* list)
{
    for(int i = 0; i < list->length; i++)
    {
        free(list->list[i]);
    }
    free(list->list);
    free(list);
}

Bytecode* createBytecode(const byte* code)
{
    Bytecode* bytecode = (Bytecode*)malloc(sizeof(Bytecode));
    bytecode->length = strlen(code);
    bytecode->realLength = bytecode->length * 1.5;
    bytecode->tokenCount = 0;

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
    bytecode->length += strlen(code);
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

Bytecode* tokenToBytecode(TokenList* tokenList, int startPoint, FunctionList* funcList, int offset)
{
    Bytecode* bytecode = createBytecode("");

    for(int i = startPoint; i < tokenList->length; i++)
    {
        bytecode->tokenCount++;
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
            case LOOP_START:
            {
                Bytecode* codeBlock = tokenToBytecode(tokenList, i + 1, funcList, offset + bytecode->length);
                int jmpDist = codeBlock->length + 2;

                addByte(bytecode, 0x09);
                addByte(bytecode, (jmpDist >> 24) & 0xFF);
                addByte(bytecode, (jmpDist >> 16) & 0xFF);
                addByte(bytecode, (jmpDist >> 8) & 0xFF);
                addByte(bytecode, jmpDist & 0xFF);
                addBytecode(bytecode, codeBlock->code);

                jmpDist = -codeBlock->length - 2;

                addByte(bytecode, 0x0A);
                addByte(bytecode, (jmpDist >> 24) & 0xFF);
                addByte(bytecode, (jmpDist >> 16) & 0xFF);
                addByte(bytecode, (jmpDist >> 8) & 0xFF);
                addByte(bytecode, jmpDist & 0xFF);

                bytecode->tokenCount += codeBlock->tokenCount;
                i += codeBlock->tokenCount;

                freeBytecode(codeBlock);

                break;
            }
            case LOOP_END:
            {
                return bytecode;
            }
            case SET_POINTER:
            {
                addByte(bytecode, 0x0D);
                break;
            }
            case NAME:
            {
                char* funcName = token->valueString;

                i++;
                bytecode->tokenCount++;
                token = tokenList->list[i];
                if(token->type == LOOP_START)
                {
                    addFunctionData(funcList, funcName, offset + bytecode->length + 6);

                    Bytecode* codeBlock = tokenToBytecode(tokenList, i + 1, funcList, offset + bytecode->length);
                    addByte(codeBlock, 0x0B);
                    int jmpDist = codeBlock->length + 1;

                    addByte(bytecode, 0x0E);
                    addByte(bytecode, (jmpDist >> 24) & 0xFF);
                    addByte(bytecode, (jmpDist >> 16) & 0xFF);
                    addByte(bytecode, (jmpDist >> 8) & 0xFF);
                    addByte(bytecode, jmpDist & 0xFF);
                    addBytecode(bytecode, codeBlock->code);

                    bytecode->tokenCount += codeBlock->tokenCount;
                    i += codeBlock->tokenCount;

                    freeBytecode(codeBlock);
                }
                else
                {
                    // TODO: 예외처리
                }

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
