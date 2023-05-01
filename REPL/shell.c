#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "ast.h"
#include "executor.h"
#include "../built-ins/builtins.h"
#include "../auxiliars/structs.h"

void print_prompt()
{
    printf("%s%s:%s%s%s$ ", ANSI_COLOR_GREEN, SHELL_NAME, ANSI_COLOR_BLUE, current_path, ANSI_COLOR_RESET);
}

int parse_and_execute(Source *src)
{
    /*Skipping starting blanks*/
    skip_blanks(src);

    /*Check for again*/
    bool again = true;
    char *again_str = "again";
    for (int i = 0; i < 5; i++)
    {
        if (again_str[i] != src->in_text[i])
        {
            again = false;
        }
    }

    /*Adding the command to the history*/
    if (!again)
        add_to_history(src->in_text);

    Token *tok = tokenize(src);
    if (tok == &EOF_token)
    {
        return 0;
    }

    DataNode *pre_ast = NULL;

    /*If the token is valid, parse the token into a Node*/
    while (tok && tok != &EOF_token)
    {
        Node *cmd = parse_simple_command(tok);
        if (!cmd)
        {
            break;
        }
        if (!pre_ast)
            pre_ast = new_data_node(cmd);
        else
            enqueue(pre_ast, cmd);
        tok = tokenize(src);
    }

    // ToDo: Free ast, and ast nodes.

    shunting_yard(pre_ast);
    Node *ast = build_ast(pre_ast);

    int status = execute_ast(ast, -1, -1);
    free_ast(ast);
    return status;
}

char *read_cmd(void)
{
    char buf[1024];
    char *ptr = NULL;
    char ptrlen = 0;

    while (fgets(buf, 1024, stdin))
    {
        int buflen = strlen(buf);

        if (!ptr)
        {
            ptr = malloc(buflen + 1);
        }
        else
        {
            char *ptr2 = realloc(ptr, ptrlen + buflen + 1);

            if (ptr2)
            {
                ptr = ptr2;
            }
            else
            {
                free(ptr);
                ptr = NULL;
            }
        }

        if (!ptr)
        {
            fprintf(stderr, "error: failed to alloc buffer: %s\n",
                    strerror(errno));
            return NULL;
        }

        strcpy(ptr + ptrlen, buf);

        if (buf[buflen - 1] == '\n')
        {
            if (buflen == 1 || buf[buflen - 2] != '\\')
            {
                return ptr;
            }

            ptr[ptrlen + buflen - 2] = '\0';
            buflen -= 2;
        }

        ptrlen += buflen;
    }

    return ptr;
}

int init_history_size()
{
    int read_size = 1030;

    /*count of the lines*/
    int count = 0;

    /*max lines of history that it will showed*/
    int max_lines = 10;

    /*stores the string of each line to read*/
    char text_string[read_size];

    FILE *file = fopen("./history/history.txt", "r");

    /*puts the cursor at the beginning of the file*/
    rewind(file);

    while (fgets(text_string, 1030, file))
    {
        count++;
    }
    fclose(file);
    return count;
}