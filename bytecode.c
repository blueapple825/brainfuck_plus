#include "bytecode.h"

SubroutineList* createSubroutineList()
{
    SubroutineList* list = (SubroutineList*)malloc(sizeof(SubroutineList));
    list->list = malloc(0);
    list->length = 0;
    list->realLength = 0;

    return list;
}

void addSubroutineData(SubroutineList* list, char name[33], int startPoint)
{
    SubroutineData* data = (SubroutineData*)malloc(sizeof(SubroutineData));
    strcpy(data->name, name);
    data->startPoint = startPoint;

    int originalLength = list->length;
    list->length += 1;
    if(list->length >= list->realLength)
    {
        list->realLength = list->length * 1.5;
        list->list = (SubroutineData**)realloc(list->list, list->realLength);
    }

    list->list[originalLength] = data;
}

void freeSubroutineList(SubroutineList* list)
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

void addBytecode(Bytecode* bytecode, Bytecode* newCode)
{
    int originalLength = bytecode->length;
    bytecode->length += newCode->length;
    if(bytecode->length >= bytecode->realLength)
    {
        bytecode->realLength = bytecode->length * 1.5;
        bytecode->code = (byte*)realloc(bytecode->code, bytecode->realLength);
    }

    for(int i = 0; i < newCode->length; i++)
    {
        bytecode->code[i + originalLength] = newCode->code[i];
    }
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

Bytecode* tokenToBytecode(TokenList* tokenList, int startPoint, SubroutineList* subList, int offset)
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
                Bytecode* codeBlock = tokenToBytecode(tokenList, i + 1, subList, offset + bytecode->length);

                int startPoint = bytecode->length + offset + 4;
                int endPoint = startPoint + codeBlock->length + 5;

                addByte(bytecode, 0x09);
                addByte(bytecode, (endPoint >> 24) & 0xFF);
                addByte(bytecode, (endPoint >> 16) & 0xFF);
                addByte(bytecode, (endPoint >> 8) & 0xFF);
                addByte(bytecode, endPoint & 0xFF);
                addBytecode(bytecode, codeBlock);

                addByte(bytecode, 0x0A);
                addByte(bytecode, (startPoint >> 24) & 0xFF);
                addByte(bytecode, (startPoint >> 16) & 0xFF);
                addByte(bytecode, (startPoint >> 8) & 0xFF);
                addByte(bytecode, startPoint & 0xFF);

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
                    addSubroutineData(subList, funcName, offset + bytecode->length + 4);

                    Bytecode* codeBlock = tokenToBytecode(tokenList, i + 1, subList, offset + bytecode->length + 5);

                    addByte(codeBlock, 0x0C);
                    int endPoint = bytecode->length + codeBlock->length + offset + 4;

                    addByte(bytecode, 0x0E);
                    addByte(bytecode, (endPoint >> 24) & 0xFF);
                    addByte(bytecode, (endPoint >> 16) & 0xFF);
                    addByte(bytecode, (endPoint >> 8) & 0xFF);
                    addByte(bytecode, endPoint & 0xFF);
                    addBytecode(bytecode, codeBlock);

                    bytecode->tokenCount += codeBlock->tokenCount;
                    i += codeBlock->tokenCount;

                    freeBytecode(codeBlock);
                }
                else
                {
                    // TODO: 오류 메시지 출력 추가
                    exit(-1);
                }

                break;
            }
            case CALL:
            {
                i++;
                bytecode->tokenCount++;
                token = tokenList->list[i];
                if(token->type == NAME)
                {
                    int jmpPoint = 0;
                    for(int j = 0; j < subList->length; j++)
                    {
                        if(strcmp(subList->list[j]->name, token->valueString) == 0)
                        {
                            jmpPoint = subList->list[j]->startPoint;
                            break;
                        }
                    }

                    if(jmpPoint == 0)
                    {
                        // TODO: 오류 메시지 출력 추가
                        exit(-1);
                    }

                    addByte(bytecode, 0x0B);
                    addByte(bytecode, 0x0E);
                    addByte(bytecode, (jmpPoint >> 24) & 0xFF);
                    addByte(bytecode, (jmpPoint >> 16) & 0xFF);
                    addByte(bytecode, (jmpPoint >> 8) & 0xFF);
                    addByte(bytecode, jmpPoint & 0xFF);
                }
                else
                {
                    // TODO: 오류 메시지 출력 추가
                    exit(-1);
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
