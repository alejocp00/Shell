#ifndef TOKEN_H
#define TOKEN_H
#include "source.h"

/*struct token will help us tokenizing*/
typedef struct token
{
    Source *source;
    char *text;
    long text_size;
} Token;

/*Extern token that indicates EOF*/
extern Token EOF_token;

/**
 * @brief This will retrieve next input token
 *
 * @param source The source of the input
 * @return Token* The next token
 */
Token *tokenize(Source *source);

/**
 * @brief Liberate the memory used by a Token
 *
 * @param token The token to free
 */
void free_token(Token *token);

#endif
