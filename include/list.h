/**
 * @file list.h
 * @author Alexandre Boavida (novaisboavida@gmail.com)
 * @brief Definition for generic linked list struct
 * 
 * @date 2022-09-10
 *
 */

#ifndef LIST_SIMPLE_H
#define LIST_SIMPLE_H

#include <stdbool.h>

/**
 * @brief Standard singly linked list, can hold any data, declared explicitly for versatile use
 * 
 */
typedef struct node_t{
    void* data;
    struct node_t* next;
}*List_node;

/**
 * @brief Small abstraction, just returns NULL as a way to initalize an empty list, you can initialize it yourself normally
 * 
 * @return NULL
 */
List_node list_create();

/**
 * @brief Dynamically allocates a list node and returns its pointer 
 * 
 * @param data data to append to list node
 * @return List_node created or NULL if failed
 */
List_node list_nodeCreate(void *data);

/**
 * @brief Iterates through linked list and frees all memory pertaining to list nodes
 * 
 * @param head the head of the linked list to destroy
 */
void list_destroy(List_node head);

/**
 * @brief Appends value at the top of a linked list and returns its head
 * 
 * @param head the head of the linked list to append data
 * @param data data to append
 * @return Head of linked list
 */
List_node list_append(List_node head, void *data);

/**
 * @brief Pops head of linked list and frees memory popped, returning its next pointer
 * 
 * @param head head of linked list to pop
 * @return List_node new list head 
 */
List_node list_pop(List_node head);

typedef struct l_iterator *List_iterator;

List_iterator list_iterator_create(List_node head);

void list_iterator_destroy(List_iterator* it);

bool list_hasNext(List_iterator it);

void* list_next(List_iterator it);

void* list_iterate(List_iterator it);


#endif