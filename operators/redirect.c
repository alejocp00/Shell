#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../REPL/node.h"
#include "../REPL/executor.h"

/**
 * @brief This method excecute the > function
 *
 * @param argv
 * @return int
 */
int retofile(Node *argv, int fd_in, int fd_out)
{
  char *end_ptr = 0;
  int fd = (int)strtol(argv->ast_right_child->first_child->value.str, &end_ptr, 10); // try to convert to int the file name
  if (*(end_ptr + 1) != '\0')
  { // if the convert is not succesfull then take as a file descriptor the value of the open function
    fd = open(argv->ast_right_child->first_child->value.str, O_WRONLY | O_TRUNC | O_CREAT, 0600);
  }
  int pid = fork();
  if (pid == 0)
  {
    if (dup2(fd, STDOUT_FILENO) == -1)
    { // Redirect the output
      perror("Redirect Error");
      return 1;
    }
    if (execute_ast(argv->ast_left_child, fd_in, fd_out) == 1)
    { // Excecute the left node command
      return 1;
    }
  }
  else
  {
    waitpid(pid, NULL, 0);
  }
  return 0;
}

/**
 * @brief This method excecute the >> function
 *
 * @param argv
 * @return int
 */
int retofileap(Node *argv, int fd_in, int fd_out)
{
  char *end_ptr = 0;
  int fd = (int)strtol(argv->ast_right_child->first_child->value.str, &end_ptr, 10);
  if (*(end_ptr + 1) != '\0')
  {
    fd = open(argv->ast_right_child->first_child->value.str, O_WRONLY | O_APPEND | O_CREAT, 0600);
  }

  int pid = fork();
  if (pid == 0)
  {
    if (dup2(fd, STDOUT_FILENO) == -1)
    { // Redirect the output
      perror("Redirect Error");
      return 1;
    }
    if (execute_ast(argv->ast_left_child, fd_in, fd_out) == 1)
    { // Excecute the left node command
      return 1;
    }
  }
  else
  {
    waitpid(pid, NULL, 0);
  }
  return 0;
}

/**
 * @brief This method excecute the < function
 *
 * @param argv
 * @return int
 */
int refromfile(Node *argv, int fd_in, int fd_out)
{
  char *end_ptr = 0;
  // int fd = open(argv->right_child, O_WRONLY | O_APPEND  | O_CREAT, 0600);
  int fd = (int)strtol(argv->ast_right_child->first_child->value.str, &end_ptr, 10);
  if (*(end_ptr + 1) != '\0')
  {
    fd = open(argv->ast_right_child->first_child->value.str, O_RDONLY);
  }
  int pid = fork();
  if (pid == 0)
  {
    if (dup2(fd, STDIN_FILENO) == -1)
    { // Redirect the output
      perror("Redirect Error");
      return 1;
    }
    if (execute_ast(argv->ast_left_child, fd_in, fd_out) == 1)
    { // Excecute the left node command
      return 1;
    }
  }
  else
  {
    waitpid(pid, NULL, 0);
  }
  return 0;
}