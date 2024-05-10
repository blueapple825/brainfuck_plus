#ifndef _TOKENIZER_H
#define  _TOKENIZER_H

#include <stdlib.h>

typedef enum _TokenType TokenType;

typedef enum _TokenType
{
    ADD_POINTER,
    PUSH_POINTER,
    POP_POINTER,
    ADD_VALUE,
    PRINT,
    INPUT,
    LOOP_START,
    LOOP_END,
    SET_POINTER,
    NAME,
    CALL
}TokenType;

typedef struct _Token Token;
typedef struct _TokenList TokenList;

typedef struct _Token
{
    TokenType type;
    int valueNumber;
    char valueString[33];
}Token;

typedef struct _TokenList
{
    Token** list;
    int length;
    int realLength;
}TokenList;

TokenList* createTokenList();
void addTokenToTokenList(TokenList* list, Token* token);
void freeTokenList(TokenList* list);

TokenList* tokenize(const char* string);

#endif
