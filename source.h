#ifndef SOURCE_H
#define SOURCE_H

#define INIT_SRC_POS (-2)
#define EOF (-1)
#define ERRCHAR (0)

/*This structure will help us to manage the text easy*/
typedef struct source
{
    /*input text*/
    char *in_text;
    /*size of the input text*/
    long size;
    /*position of the actual char in the source text*/
    long position;
} Source;

/*It returns the next char and points to the next char*/
char get_next_char(Source *source);

/*It returns the next char but it keeps pointing at the actual char*/
char peek_next_char(Source *source);

/*unget the actual char to the input source*/
void unget_char(Source *source);

/*Skip white spaces and tabs*/
void skip_blanks(Source *source);

#endif