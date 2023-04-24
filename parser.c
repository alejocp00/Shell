#include <unistd.h>
#include "shell.h"
#include "parser.h"
#include "scanner.h"
#include "node.h"
#include "source.h"

Node *parse_simple_command(Token *token)
{
    if (!token)
    {
        return NULL;
    }

    Node *cmd = new_node(NODE_COMMAND);
    if (!cmd)
    {
        free_token(token);
        return NULL;
    }

    Source *src = token->source;

    do
    {
        if (token->text[0] == '\n')
        {
            free_token(token);
            break;
        }
        Node *word = new_node(NODE_VAR);
        if (!word)
        {
            free_node_tree(cmd);
            free_token(token);
            return NULL;
        }
        set_node_val_str(word, token->text);
        add_child_node(cmd, word);
        free_token(token);
    } while ((token = tokenize(src)) != &EOF_token);
    return cmd;
}