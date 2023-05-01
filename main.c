#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./auxiliars/structs.h"
#include "./REPL/shell.h"

char *current_path = NULL;

int main(int argc, char **argv)
{
    current_path = getcwd(current_path, 1024);
    char *cmd;
    do
    {
        print_prompt();

        /*READ*/
        cmd = read_cmd();
        if (!cmd)
        {
            exit(EXIT_SUCCESS);
        }
        if (cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
        {
            free(cmd);
            continue;
        }

        /*EVAL-PRINT*/
        Source src;
        src.in_text = cmd;
        src.size = strlen(cmd);
        src.position = INIT_SRC_POS;
        parse_and_execute(&src);
        free(cmd);

        /*LOOP*/
    } while (1);
    exit(EXIT_SUCCESS);
}