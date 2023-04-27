#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "executor.h"

void print_prompt()
{
    printf("%s%s:%s%s%s$ ", ANSI_COLOR_GREEN, SHELL_NAME, ANSI_COLOR_BLUE, current_path, ANSI_COLOR_RESET);
}

int parse_and_execute(Source *src)
{
    /*Skipping starting blanks*/
    skip_blanks(src);

    Token *tok = tokenize(src);
    if (tok == &EOF_token)
    {
        return 0;
    }

    /*If the token is valid, parse the token in to a Node*/
    while (tok && tok != &EOF_token)
    {
        Node *cmd = parse_simple_command(tok);
        if (!cmd)
        {
            break;
        }

        /*Execute the command*/
        do_simple_command(cmd);

        free_node(cmd);
        tok = tokenize(src);
    }
    return 1;
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