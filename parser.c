#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

#pragma region Source
char point_next_char(Source *source)
{
    /*Verify if there is a source value or in_text value*/
    if(!source || !source->in_text) 
    {
        errno = ENODATA; 
        return 0;
    }
    
    /*Verify if it has been initializated*/
    if (source->position == INITIAL_S_POSITION)
    {
        source->position = -1;
    }
    /*Verify if it's the end of the source text*/
    if(source->position >= source->size)
    {
        source->position = source->size;
        return EOF;
    }
    source->position++;
    return source->in_text[source->position];
}

char get_char(Source *source)
{
    /*Verify if there is a source value or a in_text value*/
    if(!source || !source->in_text)
    {
        return 0;
    }
    /*Verify is it has been initializated*/
    if(source->position == INITIAL_S_POSITION)
    {
        source->position = -1;
    }

    /*position of the next char*/
    long pos = source->position + 1; 
    
    /*Verify if it's the end of the file*/
    if(pos == source->size) 
    {
        return EOF;
    }
    
    return source->in_text[pos];
}

void unget_char(Source *source)
{
    if(source->position < 0) return;
    source->position--;
}

void skip_blanks(Source *source)
{
    /*Verify if there is a source value or a in_text value*/
    if(!source || !source->in_text) return; 
    
    char aux;

    while((aux = get_char(source)) != EOF && (aux == ' ' || aux == '\t')) 
    {
        point_next_char(source);
    }
}

#pragma endregion

#pragma region Token 

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



#pragma endregion

