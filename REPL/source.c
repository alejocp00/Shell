#include <errno.h>
#include <stdlib.h>
#include "scanner.h"

char get_next_char(Source *source)
{
    /*Verify if there is a source value or in_text value*/
    if (!source || !source->in_text)
    {
        errno = ENODATA;
        return 0;
    }

    /*Verify if it has been initialized*/
    if (source->position == INIT_SRC_POS)
    {
        source->position = -1;
    }
    /*Verify if it's the end of the source text*/
    if (++source->position >= source->size)
    {
        source->position = source->size;
        return EOF;
    }

    return source->in_text[source->position];
}

char peek_next_char(Source *source)
{
    /*Verify if there is a source value or a in_text value*/
    if (!source || !source->in_text)
    {
        errno = ENODATA;
        return ERRCHAR;
    }

    /*position of the next char*/
    long pos = source->position;

    /*Verify is it has been initialized*/
    if (pos == INIT_SRC_POS)
    {
        pos = -1;
    }

    pos++;

    /*Verify if it's the end of the file*/
    if (pos == source->size)
    {
        return EOF;
    }

    return source->in_text[pos];
}

void unget_char(Source *source)
{
    if (source->position < 0)
        return;
    source->position--;
}

void skip_blanks(Source *source)
{
    /*Verify if there is a source value or a in_text value*/
    if (!source || !source->in_text)
        return;

    char aux;

    while ((aux = peek_next_char(source)) != EOF && (aux == ' ' || aux == '\t'))
    {
        get_next_char(source);
    }
}
