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
            while((*string) == '>' || (*string) == '<')
            {
                value += (*string) == '>' ? 1 : -1;
                string++;
            }

            TokenType tokenType = ADD_POINTER;
            if(value < 0)
            {
                tokenType = SUB_POINTER;
                value = 0 - value;
            }

            while(value != 0)
            {
                Token* token = (Token*)malloc(sizeof(Token));
                token->type = tokenType;
                if(value > 255)
                {
                    token->valueNumber = 255;
                    value -= 255;
                }
                else
                {
                    token->valueNumber = value;
                    value = 0;
                }
                addTokenToTokenList(tokenList, token);
            }

            break;
        }
        case '+':
        case '-':
        {
            int value = 0;
            while((*string) == '+' || (*string) == '-')
            {
                value += (*string) == '+' ? 1 : -1;
                string++;
            }

            TokenType tokenType = ADD_VALUE;
            if(value < 0)
            {
                tokenType = SUB_VALUE;
                value = 0 - value;
            }

            while(value != 0)
            {
                Token* token = (Token*)malloc(sizeof(Token));
                token->type = tokenType;
                if(value > 255)
                {
                    token->valueNumber = 255;
                    value -= 255;
                }
                else
                {
                    token->valueNumber = value;
                    value = 0;
                }
                addTokenToTokenList(tokenList, token);
            }

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
                        fprintf(stderr, "%s\n", "syntax error: The length of name exceeds 32 characters.");
                        exit(-1);
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
