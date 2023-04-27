#include "utils.h"
#include <stddef.h>

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