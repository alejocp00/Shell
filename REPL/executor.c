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
#include "../auxiliars/structs.h"
#include "../operators/operators.h"
#include "../built-ins/builtins.h"

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

/**
 * @brief Do a simple command
 *
 * @param node  The node of the AST to execute
 * @param fd_in  The file descriptor of the input
 * @param fd_out  The file descriptor of the output
 * @return int  Return 0 if success, 1 if fail
 */
int do_simple_command(Node *node, int fd_in, int fd_out)
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
    char *argv[max_args + 1];

    int have_args = get_params(child, &argc, argv);
    if (!have_args)
        return 0;

    pid_t child_pid = 0;
    int status = 0;

    for (int i = 0; i < builtins_count - 3; i++)
    {
        if (strcmp(argv[0], builtins_array[i].builtin_name) == 0)
        {
            if (fd_in != -1)
                close(fd_in);
            if (fd_out != -1)
                close(fd_out);

            return builtins_array[0].function(argc, argv);
        }
    }
    if ((child_pid = fork()) == 0)
    {

        if (fd_in != -1)
        {
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }

        if (fd_out != -1)
        {
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }

        for (int i = builtins_count - 3; i < builtins_count; i++)
        {
            if (strcmp(node->first_child->value.str, builtins_array[i].builtin_name) == 0)
            {
                return builtins_array[i].function(argc, argv);
            }
        }

        return do_exec_cmd(argc, argv);
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
    else
    {
        if (fd_in != -1)
        {
            close(fd_in);
        }
        if (fd_out != -1)
        {
            close(fd_out);
        }
        do
        {
            waitpid(child_pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    // waitpid(child_pid, &status, 0);
    free_argv(argc, argv);

    return 1;
}

int get_params(Node *child, int *argc, char **argv)
{
    /* Keeping 1 for the terminating NULL arg */
    char *str;
    long max_args = 255;

    while (child)
    {
        /*Getting and reserving the necessary space*/
        str = child->value.str;
        argv[*argc] = malloc(strlen(str) + 1);

        if (!argv[*argc])
        {
            free_argv(*argc, argv);
            return 0;
        }

        /*Saving the arg in argv*/
        strcpy(argv[*argc], str);
        if (++*argc >= max_args)
        {
            break;
        }

        /*Updating to next child*/
        child = child->next_sibling;
    }
    argv[*argc] = NULL;
    return 1;
}

int execute_ast(Node *ast, int fd_in, int fd_out)
{
    /*Init variables*/
    if (!ast)
    {
        return 0;
    }

    if (ast->type == NODE_COMMAND)
    {
        return do_simple_command(ast, fd_in, fd_out);
    }

    if (ast->type == NODE_OPERATOR)
    {
        if (strcmp(ast->value.str, "&") == 0)
        {
            /*Background*/
            return background_func(ast);
        }
        else if (strcmp(ast->value.str, ";") == 0)
        {
            /*Sequential*/
            return union_func(ast);
        }
        else if (strcmp(ast->value.str, "&&"))
        {
            /*And*/
            return and_func(ast);
        }
        else if (strcmp(ast->value.str, "||") == 0)
        {
            /*Or*/
            return or_func(ast);
        }
        else if (strcmp(ast->value.str, ">") == 0)
        {
            /*Output*/
            return retofile(ast);
        }
        else if (strcmp(ast->value.str, ">>") == 0)
        {
            /*Append*/
            return retofileap(ast);
        }
        else if (strcmp(ast->value.str, "|") == 0)
        {
            /*Pipe*/
            return pipes(ast);
        }
        else if (strcmp(ast->value.str, "<") == 0)
        {
            /*Input*/
            return refromfile(ast);
        }
        else
        {
            return 0;
        }
    }

    return 1;
}

/* ToDo:
 * - El flujo para ejecutar va a ser interno, y las redirecciones van a ser con indicadores.
 * - Las funciones de redirección van a indicar si hay o no, y siempre se pasa al método los fd de entrada y salida.
 * - Las lógicas mandan a ejecutar con evaluación del estado resultante
 */