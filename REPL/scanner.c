#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "auxiliars/structs.h"

/*Indicates the end of the input*/
Token EOF_token = {
    .text_size = 0,
};

char *buffer = NULL;
int buf_size = 0;
int buf_index = -1;
bool read_command = true;

/*Auxiliar Functions*/

void add_to_buffer(char character)
{
    buffer[buf_index++] = character;

    /*Verify if after the increment it gets at the final of the buffer*/
    if (buf_index >= buf_size)
    {
        /*temporal char for adjusting the size*/
        char *aux = realloc(buffer, buf_size * 2);

        /*Verify if it was not posible to realloc*/
        if (!aux)
        {
            /*Throw no memory error*/
            errno = ENOMEM;
            return;
        }
        buffer = aux;
        buf_size *= 2;
    }
}

Token *create_token(char *text)
{
    /*Reserve the memory that it'll be necessary for the token*/
    Token *token = malloc(sizeof(Token));

    if (!token)
        return NULL;

    /*Initializing the structure with 0*/
    memset(token, 0, sizeof(Token));
    token->text_size = strlen(text);

    /*This char will contain the text, the size is text_size+1 because we need to save /0 which indicates the end of the string*/
    char *n_text = malloc(token->text_size + 1);

    if (!n_text)
    {
        free(token);
        return NULL;
    }

    /*Copying the string*/
    strcpy(n_text, text);
    token->text = n_text;

    return token;
}

void free_token(Token *token)
{
    if (token->text)
    {
        free(token->text);
    }
    free(token);
}

Token *tokenize(Source *source)
{
    /*Verify if there is a source, in_text and a size value*/
    if (!source || !source->in_text || !source->size)
    {
        errno = ENODATA;
        return &EOF_token;
    }

    /*Verify if there is a buffer value*/
    if (!buffer)
    {
        buf_size = 1024;
        buffer = malloc(buf_size);

        /*Verify if it was possible to reserve memory*/
        if (!buffer)
        {
            errno = ENOMEM;
            return &EOF_token;
        }
    }

    buf_index = 0;
    buffer[0] = '\0';

    /*next will be an aux char that contains the next character*/
    char next = get_next_char(source);

    bool end = false;

    if (next == ERRCHAR || next == EOF)
        return &EOF_token;

    do
    {
        bool add_next;

        /*The deciding what to do*/
        switch (next)
        {
        /*Spaces*/
        case (' '):
        case ('\t'):
            if (buf_index > 0)
                end = true;
            break;
        /*End of command*/
        case ('#'):
            unget_char(source);
            if (buf_index == 0)
                return &EOF_token;
            end = true;
            break;
        /*End of line*/
        case ('\n'):
            if (buf_index > 0)
                unget_char(source);
            else
                add_to_buffer(next);
            end = true;
            break;
        // Operators
        case ('&'):
        case ('>'):
        case ('|'):
            // Searching for the double char operators
            add_next = peek_next_char(source) == next;
        case (';'):
        case ('<'):
            // Checking if we are creating a command token instated
            if (buf_index > 0 || read_command)
            {
                unget_char(source);
                read_command = false;
                return &EOF_token;
            }
            add_to_buffer(next);
            if (add_next)
            {
                add_next = false;
                add_to_buffer(get_next_char(source));
            }
            end = true;
            break;
        default:
            if (!read_command)
            {
                read_command = true;
                unget_char(source);
                return &EOF_token;
            }
            add_to_buffer(next);
            break;
        }
        if (end)
            break;
        next = get_next_char(source);
    } while (next != EOF);

    if (buf_index == 0)
        return &EOF_token;
    if (buf_index >= buf_size)
        buf_index = buf_size - 1;

    buffer[buf_index] = '\0';

    Token *token = create_token(buffer);

    if (!token)
        return &EOF_token;

    token->source = source;
    return token;
}
