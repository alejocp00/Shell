#ifndef OPERATORS_H
#define OPERATORS_H
#include "../auxiliars/list.h"

extern list *background_process;

void update_background();

int background_func(Node *argv, int fd_in, int fd_out);

int or_func(Node *argv, int fd_in, int fd_out);

int and_func(Node *argv, int fd_in, int fd_out);

int semicolon_func(Node *argv, int fd_in, int fd_out);

int pipes(Node *nodes, int fd_in, int fd_out);

int retofile(Node *argv, int fd_in, int fd_out);

int retofileap(Node *argv, int fd_in, int fd_out);

int refromfile(Node *argv, int fd_in, int fd_out);

#endif