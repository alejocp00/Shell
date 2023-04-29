#ifndef BUILTINS_H
#define BUILTINS_H

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

#endif