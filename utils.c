#include "utils.h"
#include <stddef.h>

#pragma region DataNode methods

/**
 * @brief Create a new data node object
 *
 * @param value The value of the node
 * @return DataNode* The new node
 */
DataNode *new_data_node(Node *value)
{
    DataNode *node = malloc(sizeof(DataNode));
    if (!node)
    {
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
}

#pragma endregion

#pragma region Stack methods

/**
 * @brief Add a new node to the stack
 *
 * @param stack The stack
 * @param value The value of the node
 */
void push(DataNode *stack, Node *value)
{
    DataNode *node = new_data_node(value);
    if (!node)
    {
        return;
    }
    if (!stack)
    {
        return;
    }

    DataNode *aux = stack;
    stack = node;
    stack->next = aux;
}

/**
 * @brief Remove the first node of the stack
 *
 * @param stack The stack
 * @return Node* The value of the node
 */
Node *pop(DataNode *stack)
{
    if (!stack || stack->value == NULL)
    {
        return NULL;
    }
    Node *value = stack->value;
    DataNode *aux = stack;
    stack = stack->next;
    free(aux);
    return value;
}

#pragma endregion

#pragma region Queue methods

/**
 * @brief Push a new node to the queue
 *
 * @param queue The queue
 * @param value The value of the node
 */
void enqueue(DataNode *queue, Node *value)
{
    DataNode *node = new_data_node(value);
    if (!node)
    {
        return;
    }
    if (!queue)
    {
        return;
    }

    DataNode *aux = queue;

    while (aux->next)
    {
        aux = aux->next;
    }

    aux->next = node;
}

/**
 * @brief Pop the first node of the queue
 *
 * @param queue The queue
 * @return Node* The value of the node
 */
Node *dequeue(DataNode *queue)
{
    if (!queue || queue->value == NULL)
    {
        return NULL;
    }
    Node *value = queue->value;
    DataNode *aux = queue;
    queue = queue->next;
    free(aux);
    return value;
}

#pragma endregion