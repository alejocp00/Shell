#include <errno.h>
#include <stdlib.h>
#include "token.h"
#include "source.h"

/*Indicates the end of the input*/
Token EOF_token = {
    .text_size = 0,
};

char *buffer = NULL;
int buf_size = 0;
int buf_index = -1;

/*Auxiliar Functions*/

void add_to_buffer(char character)
{   
    /*temporal char for adjusting the size*/
    char *aux;

    /*Verify if after the increment it gets at the final of the buffer*/
    if(++buf_index >= buf_size)
    {
        aux = realloc(buffer, buf_size*2);
        /*Verify if it was not posible to realloc*/
        if(!aux)
        {
            /*Throw no memory error*/
            errno = ENOMEM;
            return;
        }
    }

    buffer = aux;
    buffer[buf_index] = character;
    buf_size*=2;
}

Token *create_token(char *text)
{
    /*Reserve the memory that it'll be necesary for the token*/
    Token *token = malloc(sizeof(Token));

    if(!token) return NULL;

    /*Initialazing the structure with 0*/
    memset(token, 0, sizeof(Token));
    token->text_size = strlen(text);

    /*This char will contain the text, the size is text_size+1 because we need to save /0 wich indicates the end of the string*/
    char *n_text = malloc(token->text_size+1);

    if(!n_text)
    {
        free(token);
        return NULL;
    }

    /*Copying the string*/
    strcpy(n_text, text);
    token->text = n_text;

    return token;
}

/* Question: No estoy segura si hay que liberar tambien source. Yo lo habia puesto pero en el tuto no esta.*/
void free_token(Token *token)
{
    if(token->text)
    {
        free(token->text);
    }
    free(token);
}

Token *tokenize(Source *source)
{   
    /*Verify if there is a source, in_text and a size value*/
    if(!source || !source->in_text || !source->size)
    {
        errno = ENODATA;
        return &EOF_token;
    }

    /*Verify if there is a buffer value*/
    if(!buffer)
    {
        buf_size = 1024;
        buffer = malloc(buf_size);

        /*Verify if it was possible to reserve memory*/
        if(!buffer)
        {
            errno = ENOMEM;
            return &EOF_token;
        }
    }

    buf_index = 0;
    buffer[0] = '\0';

    /*next will be an aux char that contains the next character*/
    char next = point_next_char(source);

    int end = 0;

    /* Fix: Necesito revisar esto bien cuando tenga cabeza para leer el codigo*/
    if(next == 0 || next == EOF) return &EOF_token;

    do
    {
        switch(next)
        {
            case(' '):
            case('\t'):
                if(buf_index > 0) end = 1;
                break;
            case('\n'):
                if(buf_index > 0) unget_char(source);
                else add_to_buffer(next);
                end = 1;
                break;
            default:
                add_to_buffer(next);
                break;
        }
        if(end) break;
    } while(next = point_next_char(source) != EOF);

    if(buf_index == 0) return &EOF_token;
    if(buf_index >= buf_size) buf_index--;

    buffer[buf_index] = '\0';

    Token *token = create_token(buffer);

    if(!token) return &EOF_token;

    token->source = source;
    return token;
}
