#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "builtins.h"
#include "node.h"
#include "list.h"


list *background_process;

/**
 * @brief This method excecute the & function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int background_func(int argc, char **argv)
{
    pid_t pid;
    pid = fork(); 
    PushEnd(background_process, pid);//inserting the pid in the array

    if (pid == 0) { //Child process
       // printf("Children process executing...\n");
        execvp("programa", NULL); // Ejecutar programa en segundo plano////////////////
    } else if (pid > 0) { // Parent process
       // printf("parent process executing...\n");
       // waitpid(pid, NULL, WNOHANG); // wait for child to exit
       // printf("child process finished.\n");
    } else { //error ocurred
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
     pid_t pid=getpid();
     //pid_t pgid= getpgid(pid);
    printf("Background processes:\n");
    // iterates over all possible process IDs
    for (int p = 1; p <= background_process->size; p++) {

        printf("PID=%d", GetValue(background_process,p));
    }
    return 0;
}
Builtins jobs_struct = {"jobs", jobs};

/**
 * @brief This method excecute the fg function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int fg(int argc, char **argv)
{
    if(argc==NULL){//Hacer que se ejecute el proceso mas reciente enviado al background///////////
     pid_t recentProcess= getRecent(background_process);
     //exec("fg", recentProcess);
     kill(recentProcess, SIGCONT);
     waitpid(recentProcess, NULL, 0);
    }
    else{
    // send SIGCONT signal to the process
    kill(argc, SIGCONT);
      // wait for the process to finish
    waitpid(argc, NULL, 0);
    }
  
}
Builtins fg_struct = {"fg", fg};

/**
 * @brief This method excecute the updating of the backgrounds process
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

void update_background(){
    int status;

    if (background_process->size > 0) {
        for (int i = 0; i < background_process->size; ++i) {
            waitpid(GetValue(background_process,i), &status, WNOHANG);
            if (WIFEXITED(status)) {
                printf("[%d]\tDone\t%d\n", i + 1, GetValue(background_process,i));
                DeleteValue(background_process, i);
                i = -1;
            }
        }
    }
}
