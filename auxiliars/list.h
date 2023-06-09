#ifndef LIST_HEAD__

#include <stdio.h>
#include <stdlib.h>

#define LIST_HEAD__

// Nodos de la lista
typedef struct node_list
{
    struct node_list *previous;
    struct node_list *next;
    void *value;
} Node_list;

// Lista
typedef struct list
{
    Node_list *first;
    Node_list *last;
    int size;

} list;

list *NewList();
// Annade un nodo al final de la lista
void PushEnd(list *linkedList, void *element);

// Annade un nodo al inicio de la lista
void PushBeg(list *linkedList, void *element);

// Elimina el ultimo nodo
void DeleteEnd(list *linkedList);

// Elimina el primer nodo
void DeleteBeg(list *linkedList);

// Elimina el nodo que se encuentra en la posicion index de la lista
void DeleteValue(list *linkedlist, int index);

// Devuelve el valor del nodo que se encuentra en la posicion index de la lista
void *GetValue(list *linkedlist, int index);

// Elimina la lista
void DeleteList(list *linkedList);
#endif