#ifndef SOURCE_H
#define SOURCE_H

#define INITIAL_S_POSITION (-2)
#define EOF (-1)

/*This structure will help us to manage the text easy*/
struct source
{
    /*input text*/
    char *in_text; 
    /*size of the input text*/
    long size;
    /*position of the actual char in the source text*/
    long position; 
};

/*defining alias for struct source*/
typedef struct source Source;

/*It returns the next char and points to the next char*/
char point_next_char(Source *source);

/*It returns the next char but it keeps pointing at the actual char*/
char get_char(Source *source);

/*unget the actual char to the input source*/
void unget_char(Source *source);

/*Skip white spaces and tabs*/
void skip_blanks(Source *source);

#endif


#ifndef TOKEN_H
#define TOKEN_H

/*struct token will help us tokenizing*/
struct token
{
    Source *source;
    char *text;
    long text_size;
};

/*Definining an alias for struct token*/
typedef struct token Token;

/*Extern token that indicates EOF*/
extern Token EOF_token;

/*This will retrieve next input token*/
Token *tokenize(Source source);

/*Liberate the memory used by a Token*/
void *free_T(Token token);
#endif