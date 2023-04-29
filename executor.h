#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "node.h"

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
int do_simple_command(Node *node);

/**
 * @brief Execute the AST
 *
 */
int execute_ast(DataNode *ast);

#endif