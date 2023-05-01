#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signal.h>
#include "./auxiliars/structs.h"
#include "./REPL/shell.h"
#include "./operators/operators.h"
#include "auxiliars/list.h"

char *current_path = NULL;
int shell_pid;
int last_pid;
int history_size;

void ctrl_c()
{
    int current_pid = getpid();

    if (current_pid == shell_pid)
    {
        print_prompt();
        return;
    }

    if (current_pid == last_pid)
    {
        kill(current_pid, SIGKILL);
    }
    else
    {
        kill(current_pid, SIGINT);
    }

    last_pid = current_pid;

    printf("\n");
}

int main(int argc, char **argv)
{
    char *cmd;

    shell_pid = getpid();
    signal(SIGINT, ctrl_c);
    history_size = init_history_size();

    background_process = NewList();

    do
    {
        current_path = getcwd(current_path, 1024);

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

        update_background();
        /*LOOP*/
    } while (1);
    exit(EXIT_SUCCESS);
}