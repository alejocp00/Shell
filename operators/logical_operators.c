#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "builtins.h"
#include "node.h"
#include "list.h"



/**
 * @brief This method excecute the || function
 *
 * @param argv
 * @return int
 */

int or_func(Node *argv){

    if(execute_ast(argv->ast_left_child)==0){ // Excecute the left node command
        return 0;
    }
    else {
        if(execute_ast(argv->ast_right_child)==0){ // Excecute the right node command
            return 0;
        }
    }
    return 1;
}


/**
 * @brief This method excecute the && function
 *
 * @param argv
 * @return int
 */

int and_func(Node *argv){
   
        if(execute_ast(argv->ast_left_child)==1){ // Excecute the left node command
            return 1;
        }
    else {
        if(execute_ast(argv->ast_right_child)==1){ // Excecute the right node command
            return 1;
        }
    }
    return 0;
}

/**
 * @brief This method excecute the ; function
 *
 * @param argv
 * @return int
 */

int semicolon_func(Node *argv){
    execute_ast(argv->ast_left_child);// Excecute the left node command
    execute_ast(argv->ast_right_child);// Excecute the right node command
    return 0;
}

