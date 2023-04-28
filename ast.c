#include <stddef.h>
#include "ast.h"

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

/**
 * @brief Create the AST from the operations using the shunting yard algorithm
 *
 * @param operations The operations to create the AST
 *
 */
void *shunting_yard(DataNode *operations)
{
    /*Init variables*/
    if (!operations)
    {
        return NULL;
    }
    DataNode *operator_stack = NULL;
    DataNode *output_queue = NULL;
    Node *current_node = dequeue(operations);

    /*Loop*/
    while (current_node != NULL)
    {
        if (current_node->type != NODE_OPERATOR)
            if (output_queue == NULL)
                output_queue = new_data_node(current_node);
            else
                enqueue(output_queue, current_node);
        // The node is an operator
        else
        {
            // Empty stack
            if (operator_stack == NULL)
                operator_stack = new_data_node(current_node);
            else
            {
                // In operator precedence lower that the top of the stack. Proceed to pop all the stack
                if (current_node->val_info.precedence < operator_stack->value->val_info.precedence)
                    while (operator_stack->value != NULL)
                        enqueue(output_queue, pop(operator_stack));
                // Add the operator to the stack
                push(operator_stack, current_node);
            }
        }
        current_node = dequeue(operations);
    }
    // Copy all the output_queue to the operations queue
    for (current_node = dequeue(output_queue); current_node != NULL; current_node = dequeue(output_queue))
        enqueue(operations, current_node);
    // Copy all the operator_stack to the operations queue
    for (current_node = pop(operator_stack); current_node != NULL; current_node = pop(operator_stack))
        enqueue(operations, current_node);
}