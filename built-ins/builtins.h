#ifndef BUILTINS_H
#define BUILTINS_H
#include<stdio.h>

/*Structure for helping manage the builtins*/
typedef struct builtins
{
    /*builting's name*/
    char *builtin_name;

    /*function*/
    int (*function)(int argc, char **argv);
}Builtins;

/*Array as storage of all the builtins*/
extern Builtins builtins[];

/*Amount of builtins*/
int builtins_count;

/*Help function*/
int help(int argc, char **argv);

int print_file_text(FILE *file);

/*History function*/
int history(int argc, char **argv);

/*Add to the history the indicated command*/
int add_to_history(char *command);

/*Again function*/
int again(int argc, char **argv);

/*cd function*/
int cd(int argc, char **argv);

#endif