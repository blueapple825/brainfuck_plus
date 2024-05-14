#include "ast.h"

AST* createAST(AstType type)
{
    AST* ast = (AST*)malloc(sizeof(AST));
    ast->type = type;
    ast->body = (AST**)malloc(0);
    ast->bodyLength = 0;

    return ast;
}

void addAstToAstBody(AST* ast, AST* node)
{
    ast->body[ast->bodyLength] = node;

    ast->bodyLength++;
    if(ast->bodyLength >= ast->realLength)
    {
        ast->realLength *= 1.5;
        ast->body = (AST**)realloc(ast->body, sizeof(AST*) * ast->realLength);
    }
}

void freeAST(AST* ast)
{
    for(int i = 0; i < ast->bodyLength; i++)
    {
        freeAST(ast->body[i]);
    }
    free(ast->body);
    free(ast);
}

AST* parse(TokenList* tokenList)
{
    AST* ast = createAST(PROGRAM);

    for(int i = 0; i < tokenList->length; i++)
    {
        switch(tokenList->list[i]->type)
        {
            case LOOP_END:
            {
                fprintf(stdout, "%s\n", "syntax error: The pairs of LOOP do not match.");
                exit(-1);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    return ast;
}
