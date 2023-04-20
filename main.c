#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.c"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define SHELL_NAME "MyShell"
#define PATH_MAX 4096
#define ENTRY_MAX 2097152

static char current_path[PATH_MAX];
static char entry[ENTRY_MAX];
static enum Bool not_set = true;

void init_shell()
{
    getcwd(current_path, sizeof(current_path));
}

void PrintPrompt()
{
    printf("%s%s:%s%s%s$ ", ANSI_COLOR_GREEN, SHELL_NAME, ANSI_COLOR_BLUE, current_path, ANSI_COLOR_RESET);
}

int main()
{
    if (not_set)
    {
        init_shell();
        PrintPrompt();
        not_set = false;
    }
    fgets(entry, ENTRY_MAX, stdin);
}