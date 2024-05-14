#ifndef _AST_H
#define _AST_H

#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

typedef enum _AstType
{
    PROGRAM,
    SUBROUTINE,
    LOOP,
    COMMAND,
}AstType;

typedef struct _AST AST;

typedef struct _AST
{
    AstType type;
    int value;
    AST** body;
    int bodyLength;
    int realLength;
}AST;

AST* createAST(AstType type);
void addAstToAstBody(AST* ast, AST* node);
void freeAST(AST* ast);

AST* parse(TokenList* tokenList);

#endif
