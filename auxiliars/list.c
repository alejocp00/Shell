#include "list.h"

list *NewList()
{
    list *newList = (list *)(malloc(sizeof(list)));
    newList->first = NULL;
    newList->last = NULL;
    newList->size = 0;

    return newList;
}

void PushEnd(list *linkedList, void *element)
{
    // Nuevo nodo que se va a annadir al final de la lista
    Node_list *newNode = (Node_list *)(malloc(sizeof(Node_list)));
    newNode->next = NULL;
    newNode->value = element;

    // Si la lista esta vacia el nodo pasa a ser primero y ultimo elemento de la lista
    if (linkedList->size == 0)
    {
        linkedList->first = newNode;
        linkedList->last = newNode;
        linkedList->first->previous = NULL;
    }
    else // Si la lista no esta vacia
    {
        newNode->previous = linkedList->last;
        linkedList->last->next = newNode;
        linkedList->last = newNode;
    }
    linkedList->size++;
}

void PushBeg(list *linkedList, void *element)
{
    // Nuevo nodo que se va a annadir al inicio de la lista
    Node_list *newNode = (Node_list *)(malloc(sizeof(Node_list)));
    newNode->value = element;
    linkedList->first->previous = NULL;

    // Si la lista esta vacia
    if (linkedList->size == 0)
    {
        linkedList->first = newNode;
        linkedList->last = newNode;
        newNode->next = NULL;
    }
    else
    {
        linkedList->first->previous = newNode;
        newNode->next = linkedList->first;
        linkedList->first = newNode;
    }
    linkedList->size++;
}

void DeleteEnd(list *linkedList)
{
    if (linkedList->size == 0)
    {
        return;
    }

    Node_list *nodeRemoved = linkedList->last;

    if (linkedList->size == 1)
    {
        linkedList->first = NULL;
        linkedList->last = NULL;
    }
    else
    {
        linkedList->last = linkedList->last->previous;
        linkedList->last->next = NULL;
    }
    nodeRemoved->next = NULL;
    nodeRemoved->previous = NULL;
    free(nodeRemoved);
    linkedList->size--;
}

void DeleteBeg(list *linkedList)
{

    if (linkedList->size == 0)
    {
        return;
    }

    Node_list *nodeRemoved = linkedList->first;

    if (linkedList->size == 1)
    {
        linkedList->first = NULL;
        linkedList->last = NULL;
    }
    else
    {
        linkedList->first = linkedList->first->next;
        linkedList->first->previous = NULL;
    }

    nodeRemoved->next = NULL;
    nodeRemoved->previous = NULL;
    free(nodeRemoved);
    linkedList->size--;
}

void *GetValue(list *linkedList, int index)
{
    if (linkedList->size == 0 || index < 0 || index >= linkedList->size)
    {
        return NULL;
    }

    if (index == 0)
        return linkedList->first->value;

    if (index == linkedList->size - 1)
        return linkedList->last->value;

    Node_list *currentNode = linkedList->first;

    int i = 0;

    while (i < index)
    {
        currentNode = currentNode->next;
        i++;
    }
    return currentNode->value;
}

void DeleteValue(list *linkedList, int index)
{
    if (linkedList->size == 0 || index < 0 || index >= linkedList->size)
    {
        return;
    }

    if (index == 0)
    {
        DeleteBeg(linkedList);
        return;
    }

    if (index == linkedList->size - 1)
    {
        DeleteEnd(linkedList);
        return;
    }

    Node_list *currentNode = linkedList->first;

    if (linkedList->size == 1)
    {
        linkedList->first = NULL;
        linkedList->last = NULL;
    }
    else
    {
        int i = 0;

        while (i < index)
        {
            currentNode = currentNode->next;
            i++;
        }

        currentNode->previous->next = currentNode->next;
        currentNode->next->previous = currentNode->previous;
    }

    currentNode->next = NULL;
    currentNode->previous = NULL;
    free(currentNode);
    linkedList->size--;
}

void DeleteList(list *linkedList)
{
    while (linkedList->size > 0)
    {
        DeleteBeg(linkedList);
    }
    free(linkedList);
}