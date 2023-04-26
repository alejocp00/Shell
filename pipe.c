#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "builtins.h"

int pipe(int argc, char **argv)
{
    int pipefd[2];
    pid_t pid;

    char *cmd1[] = {"ls", "-l", NULL};
    char *cmd2[] = {"grep", "foo", NULL};

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    // Child process executes first command
    if (pid == 0) {
       
        close(pipefd[0]); // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[1]); // Close write end
        execvp(cmd1[0], cmd1);
        perror("execvp");
        return 1;
    } 
    
    // Parent process executes second command
    else {
        
        close(pipefd[1]); // Close unused write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin from pipe
        close(pipefd[0]); // Close read end
        execvp(cmd2[0], cmd2);
        perror("execvp");
        return 1;
    }
    return 0;   
}
Builtins pipe_struct = {"|", pipe};