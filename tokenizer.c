#include "tokenizer.h"
#include <stdio.h>

TokenList* createTokenList()
{
    TokenList* list = (TokenList*)malloc(sizeof(TokenList));
    list->list = (Token**)malloc(sizeof(Token*) * 10);
    list->length = 0;
    list->realLength = 10;

    return list;
}

void addTokenToTokenList(TokenList* list, Token* token)
{
    list->list[list->length] = token;

    list->length++;
    if(list->length >= list->realLength)
    {
        list->realLength *= 1.5;
        list->list = (Token**)realloc(list->list, sizeof(Token*) * list->realLength);
    }
}

void freeTokenList(TokenList* list)
{
    for(int i = 0; i < list->length; i++)
    {
        free(list->list[i]);
    }
    free(list->list);
    free(list);
}

TokenList* tokenize(const char* string)
{
    TokenList* tokenList = createTokenList();

    while((*string) != 0)
    {
        switch((*string))
        {
        case '>':
        case '<':
        {
            int value = 0;
            for(; (*string) == '>' || (*string) == '<'; string++)
            {
                value += (*string) == '>' ? 1 : -1;
            }

            Token* token = (Token*)malloc(sizeof(Token));
            token->type = ADD_POINTER;
            token->valueNumber = value;
            addTokenToTokenList(tokenList, token);

            break;
        }
        case '+':
        case '-':
        {
            int value = 0;
            for(; (*string) == '+' || (*string) == '-'; string++)
            {
                value += (*string) == '+' ? 1 : -1;
            }

            Token* token = (Token*)malloc(sizeof(Token));
            token->type = ADD_VALUE;
            token->valueNumber = value;
            addTokenToTokenList(tokenList, token);

            break;
        }
        case '^':
        {
            Token* token = (Token*)malloc(sizeof(Token));
            token->type = PUSH_POINTER;
            addTokenToTokenList(tokenList, token);
            string++;

            break;
        }
        case '~':
        {
            Token* token = (Token*)malloc(sizeof(Token));
            token->type = POP_POINTER;
            addTokenToTokenList(tokenList, token);
            string++;

            break;
        }
        case '.':
        {
            Token* token = (Token*)malloc(sizeof(Token));
            token->type = PRINT;
            addTokenToTokenList(tokenList, token);
            string++;

            break;
        }
        case ',':
        {
            Token* token = (Token*)malloc(sizeof(Token));
            token->type = INPUT;
            addTokenToTokenList(tokenList, token);
            string++;

            break;
        }
        case '[':
        {
            Token* token = (Token*)malloc(sizeof(Token));
            token->type = LOOP_START;
            addTokenToTokenList(tokenList, token);
            string++;

            break;
        }
        case ']':
        {
            Token* token = (Token*)malloc(sizeof(Token));
            token->type = LOOP_END;
            addTokenToTokenList(tokenList, token);
            string++;

            break;
        }
        case '*':
        {
            Token* token = (Token*)malloc(sizeof(Token));
            token->type = SET_POINTER;
            addTokenToTokenList(tokenList, token);
            string++;

            break;
        }
        case '{':
        {
            Token* token = (Token*)malloc(sizeof(Token));
            token->type = NAME;

            string++;
            int namePointer = 0;
            for(; (*string) != '}'; string++)
            {
                if((*string) >= 33 && (*string) <= 64)
                {
                    token->valueString[namePointer++] = *string;
                    if(namePointer >= 32)
                    {
                        namePointer = 32;
                        while((*string) != '}') string++;
                        break;
                    }
                }
            }
            token->valueString[namePointer] = 0;

            addTokenToTokenList(tokenList, token);

            break;
        }
        case '!':
        {
            Token* token = (Token*)malloc(sizeof(Token));
            token->type = CALL;
            addTokenToTokenList(tokenList, token);
            string++;

            break;
        }
        default:
            string++;
            break;
        }
    }

    return tokenList;
}
