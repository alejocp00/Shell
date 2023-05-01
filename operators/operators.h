#ifndef OPERATORS_H
#define OPERATORS_H

void update_background();

int background_func(Node *argv);

int or_func(Node *argv);

int and_func(Node *argv);

int semicolon_func(Node *argv);

int pipes(Node *nodes);

int retofile(Node *argv);

int retofileap(Node *argv);

int refromfile(Node *argv);

#endif