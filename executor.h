#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "node.h"
#include "ast.h"

/**
 * @brief Search the full path of the file
 *
 * @param file The file to search
 * @return char*  The full path of the file
 */
char *search_path(char *file);

/**
 * @brief Execute a command
 *
 * @param argc The number of arguments
 * @param argv The arguments
 * @return int Return 0 if success, 1 if fail
 */
int do_exec_cmd(int argc, char **argv);

/**
 * @brief Do a simple command
 *
 * @param node The node of the AST to execute
 * @return int Return 0 if success, 1 if fail
 */
int do_simple_command(Node *node, int fd_in, int fd_out);

/**
 * @brief Get the params of a node
 *
 * @param child The node
 * @param argc The number of arguments
 * @param argv The arguments
 */
void get_params(Node *child, int *argc, char **argv);

/**
 * @brief Execute the AST
 *
 * @param ast The AST
 * @param fd_in The file descriptor of the input
 * @param fd_out The file descriptor of the output
 *
 */
int execute_ast(Node *ast, int fd_in, int fd_out);

#endif