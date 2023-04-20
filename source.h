#ifndef SOURCE_H
#define SOURCE_H

/*This structure will help us to manage the text easy*/
struct source
{
    char *in_text; //input text
    long size; //size of the input text
    long position; //position of the actual char in the source text
};


/*Functions*/
char point_next_char(source nsource); //It returns the next char and points to the next char
char get_char(source source); //It returns the next char but it keeps poiting at the actual char
void skip_blanks(source source); //Skip white spaces, tabs.
void unget_char(source source); //unget the actual char to the input source

#endif