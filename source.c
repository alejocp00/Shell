#include <errno.h>
#include "source.h"

char point_next_char(Source *source)
{
    if(!source || !source->in_text) /*Verify if there is a source value or in_text value*/
    {
        errno = ENODATA; 
        return 0;
    }
    
    if (source->position == INITIAL_S_POSITION) /*Verify if it has been initializaded*/
    {
        source->position = -1;
    }
    if(source->position == source->size) /*Verify if it's the end of the source text*/
    {
        return EOF;
    }
    source->position++;
    return source->in_text[source->position];
}

char get_char(Source *source)
{
    if(!source || !source->in_text) /*Verify if there is a source value or a in_text value */
    {
        return 0;
    }
    if(source->position == INITIAL_S_POSITION) /*Verify if it has been initializaded*/
    {
        source->position = -1;
    }

    long pos = source->position + 1; /*position of the next char*/
      
    if(pos == source->size) /*verify if it's the end of the file*/
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
    if(!source || !source->in_text) return; /*Verify if there is a source value or a in_text value*/
    
    char aux;

    while((aux = get_char(source)) != EOF && (aux == ' ' || aux == ' \t')) 
    {
        point_next_char(source);
    }
}


