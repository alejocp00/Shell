#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../REPL/node.h"
#include "../REPL/executor.h"

int pipes(Node *nodes)
{
    int pipefd[2];
    int pipefd2[2];
    pid_t pid;
    pid_t pid2;

    if (pipe(pipefd) == -1 || pipe(pipefd2) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid = fork();
    pid2 = fork();
    if (pid == -1 || pid2 == -1)
    {
        perror("fork");
        return 1;
    }
    /////////////HERE

    // Child process executes first command
    if (pid == 0)
    {

        close(pipefd[0]);               // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[1]);               // Close write end
        perror("command");
        return 1;
    }

    // Parent process executes second command
    else
    {

        close(pipefd[1]);              // Close unused write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin from pipe
        close(pipefd[0]);              // Close read end
        perror("command");
        return 1;
    }
    return 0;
}