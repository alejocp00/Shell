#ifndef UTILS_H
#define UTILS_H

#include "node.h"

/**
 * @brief Data structure for the data node. This node will be used in a linked list based implementation of a queue, or a stack.
 *
 */
typedef struct data_node
{
    Node *value;
    DataNode *next;
} DataNode;

/**
 * @brief Create a new data node object
 *
 * @param value The value of the node
 * @return DataNode* The new node
 */
DataNode *new_data_node(Node *value);

#pragma region Queue methods

/**
 * @brief Add a new node to the queue
 *
 * @param queue The queue
 * @param value The value of the node
 */
void push(DataNode *queue, Node *value);

/**
 * @brief Remove the first node of the queue
 *
 * @param queue The queue
 * @return Node* The value of the node
 */
Node *pop(DataNode *queue);

#pragma endregion

#pragma region Stack methods

/**
 * @brief Push a new node to the stack
 *
 * @param stack The stack
 * @param value The value of the node
 */
void enqueue(DataNode *stack, Node *value);

/**
 * @brief Pop the first node of the stack
 *
 * @param stack The stack
 * @return Node* The value of the node
 */
Node *dequeue(DataNode *stack);

#pragma endregion

#endif