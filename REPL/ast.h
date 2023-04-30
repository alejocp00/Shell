#ifndef AST_H
#define AST_H
#include <stdlib.h>
#include "node.h"

/**
 * @brief Data structure for the data node. This node will be used in a linked list based implementation of a queue, or a stack.
 *
 */
typedef struct data_node
{
    Node *value;
    struct data_node *next;
} DataNode;

/**
 * @brief Create a new data node object
 *
 * @param value The value of the node
 * @return DataNode* The new node
 */
DataNode *new_data_node(Node *value);

#pragma region Stack methods

/**
 * @brief Add a new node to the stack
 *
 * @param stack The stack
 * @param value The value of the node
 */
void push(DataNode *stack, Node *value);

/**
 * @brief Remove the first node of the queue
 *
 * @param queue The queue
 * @return Node* The value of the node
 */
Node *pop(DataNode **stack);

#pragma endregion

#pragma region Queue methods

/**
 * @brief Push a new node to the queue
 *
 * @param queue The queue
 * @param value The value of the node
 */
void enqueue(DataNode *queue, Node *value);

/**
 * @brief Pop the first node of the stack
 *
 * @param stack The stack
 * @return Node* The value of the node
 */
Node *dequeue(DataNode **queue);

#pragma endregion

/**
 * @brief Create the AST from the operations using the shunting yard algorithm
 *
 * @param operations The operations to create the AST
 *
 */
void *shunting_yard(DataNode *operations);

Node *build_ast(DataNode *shunting_yard_result);

#endif