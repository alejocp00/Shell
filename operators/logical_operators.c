#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../built-ins/builtins.h"
#include "../REPL/node.h"
#include "../auxiliars/list.h"
#include "../REPL/executor.h"
#include "operators.h"

/**
 * @brief This method excecute the || function
 *
 * @param argv
 * @return int
 */

int or_func(Node *argv, int fd_in, int fd_out)
{

    if (execute_ast(argv->ast_left_child, fd_in, fd_out) == 0)
    { // Excecute the left node command
        return 0;
    }
    else
    {
        if (execute_ast(argv->ast_right_child, fd_in, fd_out) == 0)
        { // Excecute the right node command
            return 0;
        }
    }
    return 1;
}

/**
 * @brief This method excecute the && function
 *
 * @param argv
 * @return int
 */

int and_func(Node *argv, int fd_in, int fd_out)
{

    if (execute_ast(argv->ast_left_child, fd_in, fd_out) == 1)
    { // Excecute the left node command
        return 1;
    }
    else
    {
        if (execute_ast(argv->ast_right_child, fd_in, fd_out) == 1)
        { // Excecute the right node command
            return 1;
        }
    }
    return 0;
}

/**
 * @brief This method excecute the ; function
 *
 * @param argv
 * @return int
 */

int semicolon_func(Node *argv, int fd_in, int fd_out)
{
    execute_ast(argv->ast_left_child, fd_in, fd_out);  // Excecute the left node command
    execute_ast(argv->ast_right_child, fd_in, fd_out); // Excecute the right node command
    return 0;
}
