#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "builtins.h"
#include "node.c"

Node pidArray;

/**
 * @brief This method excecute the & function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int backgroundfunc(int argc, char **argv)
{
    pid_t pid;
    pid = fork(); 
    insert(pidArray, pid);//inserting the pid in the array

    if (pid == 0) { //Child process
        printf("Children process executing...\n");
        execvp("programa", NULL); // Ejecutar programa en segundo plano////////////////
    } else if (pid > 0) { // Parent process
        printf("parent process executing...\n");
        waitpid(pid, NULL, WNOHANG); // wait for child to exit
        printf("child process finished.\n");
    } else { //error ocurred
        printf("error to create child process.");
        return 1;
    }
    return 0;
}
Builtins backgroundfunc_struct = {"&", backgroundfunc};


/**
 * @brief This method excecute the jobs function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int jobs(int argc, char **argv)
{ 
     pid_t pid, pgid, mypgid;

    mypgid = getpgid(getpid());

    printf("Background processes:\n");

    // iterates over all possible process IDs
    for (pid = 1; pid <= 65535; pid++) {//65535 its the max number of process
        // obtain the group ID for the process
        pgid = getpgid(pid);

        // if the pid its different from the group id, then its a background process
        if (pgid != mypgid) {
            printf("PID: %d\n", pid);
        }
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
     pid_t recentProcess= getRecent(pidArray);
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