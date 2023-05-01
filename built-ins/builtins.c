#include "builtins.h"

Builtins builtins_array[] =
    {
        {"cd", cd},
        {"fg", fg},
        {"again", again},
        {"true", true_b},
        {"false", false_b},
        {"exit", exit_b},
        {"help", help},
        {"jobs", jobs},
        {"history", history},
};