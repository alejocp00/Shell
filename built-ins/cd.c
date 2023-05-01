#include <unistd.h>
#include "../built-ins/builtins.h"

int cd(int argc, char **argv)
{
    return chdir(argv[0]);
}
