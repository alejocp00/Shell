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
void push(DataNode **stack, Node *value)
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

    DataNode *aux = *stack;
    *stack = node;
    (*stack)->next = aux;
}

/**
 * @brief Remove the first node of the stack
 *
 * @param stack The stack
 * @return Node* The value of the node
 */
Node *pop(DataNode **stack)
{
    if ((*stack) == NULL || (*stack)->value == NULL)
    {
        return NULL;
    }
    Node *value = (*stack)->value;
    DataNode *aux = *stack;
    *stack = (*stack)->next;
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
Node *dequeue(DataNode **queue)
{
    if ((*queue) == NULL || (*queue)->value == NULL)
    {
        return NULL;
    }
    Node *value = (*queue)->value;
    DataNode *aux = *queue;
    *queue = (*queue)->next;
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
    Node *current_node = dequeue(&operations);

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
                        enqueue(output_queue, pop(&operator_stack));
                // Add the operator to the stack
                push(&operator_stack, current_node);
            }
        }
        current_node = dequeue(&operations);
    }
    // Copy all the output_queue to the operations queue
    for (current_node = dequeue(&output_queue); current_node != NULL; current_node = dequeue(&output_queue))
        if (!operations)
            operations = new_data_node(current_node);
        else
            enqueue(operations, current_node);
    // Copy all the operator_stack to the operations queue
    for (current_node = pop(&operator_stack); current_node != NULL; current_node = pop(&operator_stack))
        if (!operations)
            operations = new_data_node(current_node);
        else
            enqueue(operations, current_node);
}

/**
 * @brief Build the AST from the shunting yard result
 *
 * @param shunting_yard_result The shunting yard result
 * @return Node* The root of the AST
 */
Node *build_ast(DataNode *shunting_yard_result)
{
    // Take the first node of shunting_yard_result
    // if the node is a command, it will go to the command stack
    // if the node is an operator, check if the command stack has 2 elements, then add the top element as the right child and the second top element as the left child, then add the operator as the parent, then add the parent to the command stack
    // if the node is an operator, and are only 1 element in the command stack, add the top of the operator stack as the right child, and the top of the command stack as the left child, then add the operator as the parent, then add the parent to the command stack
    // if the node is an operator, and are no elements in the command stack, add the top of the operator stack as the right child, and the top of the operator stack as the left child, then add the operator as the parent, then add the parent to the command stack
    // the algorithm ends when the shunting_yard_result is empty
    // The stack will be DataNode *command_stack and DataNode *operator_stack

    DataNode *command_stack = NULL;
    DataNode *operator_stack = NULL;
    Node *current_node = dequeue(&shunting_yard_result);

    int command_stack_size = 0;
    int operator_stack_size = 0;

    while (current_node != NULL)
    {
        // Command case
        if (current_node->type == NODE_COMMAND)
        {
            if (command_stack_size == 0)
            {
                command_stack = new_data_node(current_node);
                command_stack_size++;
            }
            else
            {
                push(&command_stack, current_node);
                command_stack_size++;
            }
        }
        // Operator case
        else
        {

            if (command_stack_size >= 2)
            {
                Node *right_child = pop(&command_stack);
                Node *left_child = pop(&command_stack);

                set_tree_values(current_node, left_child, right_child);

                push(&operator_stack, current_node);
                command_stack_size--;
                command_stack_size--;
                operator_stack_size++;
            }
            else if (command_stack_size == 1)
            {
                Node *right_child = pop(&command_stack);
                Node *left_child = pop(&operator_stack);

                set_tree_values(current_node, left_child, right_child);

                push(&operator_stack, current_node);
            }
            else
            {
                Node *right_child = pop(&operator_stack);
                Node *left_child = pop(&operator_stack);

                set_tree_values(current_node, left_child, right_child);

                push(&operator_stack, current_node);
                command_stack_size--;
            }
        }
        current_node = dequeue(&shunting_yard_result);
    }
    if (operator_stack_size == 0)
        return pop(&command_stack);
    return pop(&operator_stack);
}

/**
 * @brief Free the AST
 *
 * @param ast The AST
 */
void free_ast(Node *ast)
{
    if (!ast)
    {
        return;
    }
    if (ast->first_child)
    {
        free_ast(ast->first_child);
    }
    if (ast->next_sibling)
    {
        free_ast(ast->next_sibling);
    }
    if (ast->ast_right_child)
    {
        free_ast(ast->ast_right_child);
    }
    if (ast->ast_left_child)
    {
        free_ast(ast->ast_left_child);
    }
    free(ast);
}