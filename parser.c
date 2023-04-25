#include <unistd.h>
#include "parser.h"

Node *parse_simple_command(Token *token)
{

    /*Checking if input is not corrupt*/
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
        /*If the node stars whit an \n, it's the end of the token*/
        if (token->text[0] == '\n' || token->text[0] == '#')
        {
            free_token(token);
            break;
        }

        /*Creating the new node*/
        Node *word = new_node(NODE_VAR);
        if (!word)
        {
            free_node(cmd);
            free_token(token);
            return NULL;
        }

        /*Setting the value of the node*/
        set_node_val(word, token->text);
        add_child(cmd, word);
        free_token(token);
    } while ((token = tokenize(src)) != &EOF_token);
    return cmd;
}