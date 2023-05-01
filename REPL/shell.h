#ifndef SHELL_H
#define SHELL_H
#include <errno.h>
#include "source.h"
#include "parser.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define SHELL_NAME "MyShell"

/*The pid of the shell*/
extern int shell_pid;

/*The current path*/
extern char *current_path;

/**
 * @brief Print the prompt
 *
 */
void print_prompt();

/**
 * @brief Read a command from stdin
 *
 * @return char* The command
 */
char *read_cmd();

/**
 * @brief Parse and execute a command
 *
 * @param src The source of the input
 * @return int Return 0 if success, 1 if fail
 */
int parse_and_execute(Source *src);

#endif