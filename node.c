#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "node.h"

/*Create a new node of the type indicated*/
Node *new_node(Node_Type type)
{
    /*Reserve the memory for the node*/
    Node *node = malloc(sizeof(Node));

    if (!node)
        return NULL;

    /*Initializing the node structure*/
    memset(node, 0, sizeof(Node));
    node->type = type;

    return node;
}

void add_child(Node *parent, Node *child)
{
    /*Verify if there is a parent and a child value*/
    if (!parent || !child)
        return;

    /*Verify if the parent already has a child*/
    if (!parent->first_child)
    {
        /*First child will be child*/
        parent->first_child = child;
    }
    else
    {
        Node *sibling = parent->first_child;

        /*Looking for the last child*/
        while (sibling->next_sibling)
        {
            sibling = sibling->next_sibling;
        }

        sibling->next_sibling = child;
        child->previous_sibling = sibling;
    }

    parent->c_children++;
}
