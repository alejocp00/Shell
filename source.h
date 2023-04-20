#ifndef SOURCE_H
#define SOURCE_H

#define INITIAL_S_POSITION (-2)
#define EOF (-1)

/*This structure will help us to manage the text easy*/
struct source
{
    char *in_text; //input text
    long size; //size of the input text
    long position; //position of the actual char in the source text
};

typedef struct source Source;


/*Functions*/
char point_next_char(Source *source); //It returns the next char and points to the next char
char get_char(Source *source); //It returns the next char but it keeps poiting at the actual char
void unget_char(Source *source); //unget the actual char to the input source
void skip_blanks(Source *source); //Skip white spaces, tabs.


#endif