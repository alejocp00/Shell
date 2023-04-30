#include <unistd.h>
#include "builtins.h"

int cd(int argc, char **argv)
{
    return chdir(argv[0]);
}
Builtins cd_struct = {"cd", cd};