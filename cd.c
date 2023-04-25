#include <unistd.h>
#include "builtins.h"

int cd(int argc, char **argv)
{
    return chdir(argv);
}
Builtins cd_struct = {"cd", cd};