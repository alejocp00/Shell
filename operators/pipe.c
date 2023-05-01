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
    int status1= execute_ast(nodes->ast_left_child,pipefd[0],pipefd2[1]);
    int status2= execute_ast(nodes->ast_right_child,pipefd2[0],pipefd[1]);

    if(status1==0&&status2==0)
    {
    return 0;
    }
    else{return 1;}
}