#ifndef TOKEN_H
#define TOKEN_H
#include "source.h"

/*struct token will help us tokenizing*/
struct token
{
    Source *source;
    char *text;
    long text_size;
};

/*Definining an alias for struct token*/
typedef struct token Token;

/*Extern token that indicates EOF*/
extern Token EOF_token;

/*This will retrieve next input token*/
Token *tokenize(Source *source);

/*Liberate the memory used by a Token*/
void free_T(Token token);

#endif