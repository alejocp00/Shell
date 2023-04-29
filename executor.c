#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "node.h"
#include "executor.h"
#include "ast.h"

char *search_path(char *file)
{
    char *PATH = getenv("PATH");

    /*Auxiliar starting path*/
    char *p = PATH;

    /*Auxiliar path for loop*/
    char *p2;

    /*If p has value, then*/
    while (p && *p)
    {

        p2 = p;

        /*Navigate to the end of the variable path*/
        while (*p2 && *p2 != ':')
        {
            p2++;
        }

        int plen = p2 - p;
        if (!plen)
        {
            plen = 1;
        }

        int file_len = strlen(file);
        char path[plen + 1 + file_len + 1];

        strncpy(path, p, p2 - p);
        path[p2 - p] = '\0';

        /*Checking if the path end is correct for the file concat*/
        if (p2[-1] != '/')
        {
            strcat(path, "/");
        }
        strcat(path, file);

        /*Getting attributes from path*/
        struct stat st;
        if (stat(path, &st) == 0)
        {
            /*Checking if the path is not a file*/
            if (!S_ISREG(st.st_mode))
            {
                errno = ENOENT;
                goto File_Not_Found;
            }

            p = malloc(strlen(path) + 1);
            if (!p)
            {
                return NULL;
            }

            strcpy(p, path);
            return p;
        }
        else /* file not found */
        {
        File_Not_Found:
            p = p2;
            if (*p2 == ':')
            {
                p++;
            }
        }
    }
    errno = ENOENT;
    return NULL;
}
int do_exec_cmd(int argc, char **argv)
{
    if (strchr(argv[0], '/'))
    {
        execv(argv[0], argv);
    }
    else
    {
        char *path = search_path(argv[0]);
        if (!path)
        {
            return 0;
        }
        execv(path, argv);
        free(path);
    }
    return 0;
}
static inline void free_argv(int argc, char **argv)
{
    if (!argc)
    {
        return;
    }
    while (argc--)
    {
        free(argv[argc]);
    }
}
int do_simple_command(Node *node)
{
    /*Init variables*/
    if (!node)
    {
        return 0;
    }
    Node *child = node->first_child;
    if (!child)
    {
        return 0;
    }

    int argc = 0;
    long max_args = 255;

    /* Keeping 1 for the terminating NULL arg */
    char *argv[max_args + 1];
    char *str;

    while (child)
    {
        /*Getting and reserving the necessary space*/
        str = child->value.str;
        argv[argc] = malloc(strlen(str) + 1);

        if (!argv[argc])
        {
            free_argv(argc, argv);
            return 0;
        }

        /*Saving the arg in argv*/
        strcpy(argv[argc], str);
        if (++argc >= max_args)
        {
            break;
        }

        /*Updating to next child*/
        child = child->next_sibling;
    }
    argv[argc] = NULL;

    pid_t child_pid = 0;
    if ((child_pid = fork()) == 0)
    {
        do_exec_cmd(argc, argv);
        fprintf(stderr, "error: failed to execute command: %s\n",
                strerror(errno));
        if (errno == ENOEXEC)
        {
            exit(126);
        }
        else if (errno == ENOENT)
        {
            exit(127);
        }
        else
        {
            exit(EXIT_FAILURE);
        }
    }
    else if (child_pid < 0)
    {
        fprintf(stderr, "error: failed to fork command: %s\n",
                strerror(errno));
        return 0;
    }
    int status = 0;
    waitpid(child_pid, &status, 0);
    free_argv(argc, argv);

    return 1;
}

/**
 * @brief Execute the AST
 *
 * @param ast The AST to execute
 * @return int Return 0 if success, 1 if fail
 */
int execute_ast(DataNode *ast)
{
    // ToDo: Implement the execution of the AST
}