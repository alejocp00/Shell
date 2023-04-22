#include <errno.h>
#include <stdlib.h>
#include "source.h"
#include "token.h"

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

