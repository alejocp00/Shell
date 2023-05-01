#include "builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int exit_b(int argc, char **argv)
{
    exit(EXIT_SUCCESS);
    return 0;
}