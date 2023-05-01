#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "builtins.h"
#include "REPL/node.h"
#include "auxiliars/list.h"

list *background_process;

/**
 * @brief This method excecute the & function
 *
 * @param argc
 * @param argv
 * @return int
 */
int background_func(Node *argv)
{
    pid_t pid;
    pid = fork();

    if (pid == 0)// Child process
    { 
        // exit();
    }
    else if (pid > 0)
    {                                     // Parent process
        PushEnd(background_process, pid); // Add to the background process list
    }
    else
    { // error ocurred
        printf("error to create child process.");
        return 1;
    }
    return 0;
}

/**
 * @brief This method excecute the jobs function
 *
 * @param argc
 * @param argv
 * @return int
 */
int jobs(int argc, char **argv)
{
    pid_t pid = getpid();
    printf("Background processes:\n");

    for (int p = 1; p <= background_process->size; p++)
    { // iterates over all possible process IDs

        printf("PID=%d", GetValue(background_process, p));
    }
    return 0;
}

/**
 * @brief This method excecute the fg function
 *
 * @param argc
 * @param argv
 * @return int
 */
int fg(int argc, char **argv)
{
    int status = 1;
    int pid = (int)argv[0];
    if (pid == NULL)
    { // Do the recent process
        if (background_process->size == 0)
        {
            printf("No background process");
            return 1;
        }
        pid_t recentProcess = GetValue(background_process, background_process->size - 1);
        do
        {
            waitpid(recentProcess, &status, WUNTRACED); // wait for the process to finish
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        DeleteValue(background_process, recentProcess);
    }

    else
    {
        if (GetValue(background_process, pid) == NULL)
        { // if the process is not in the list
            printf("Process not found");
            return 1;
        }
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        DeleteValue(background_process, pid);
    }

    return 0;
}
Builtins fg_struct = {"fg", fg};

/**
 * @brief This method excecute the updating of the backgrounds process
 *
 * @param argc
 * @param argv
 * @return int
 */

void update_background()
{
    int status;

    if (background_process->size > 0)
    {
        for (int i = 0; i < background_process->size; ++i)
        {
            waitpid(GetValue(background_process, i), &status, WNOHANG);
            if (WIFEXITED(status))
            {
                printf("[%d]\tDone\t%d\n", i + 1, GetValue(background_process, i));
                DeleteValue(background_process, i);
                i = -1;
            }
        }
    }
}
