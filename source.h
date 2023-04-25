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

/**
 * @brief Get the next char from the input source
 *
 * @param source The input source
 * @return char The next char
 */
char get_next_char(Source *source);

/**
 * @brief Get the next char from the input source without moving the position
 *
 * @param source The input source
 * @return char The next char
 */
char peek_next_char(Source *source);

/**
 * @brief Unget the last char from the input source
 *
 * @param source The input source
 */
void unget_char(Source *source);

/**
 * @brief Skip the blanks from the input source
 *
 * @param source The input source
 */
void skip_blanks(Source *source);

#endif