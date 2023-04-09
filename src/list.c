/**
 * @file list.c
 * @author Alexandre Boavida (novaisboavida@gmail.com)
 * @brief source code for list.h
 * @date 2022-09-10
 * 
 */

#include <stdlib.h>

#include "../include/list.h"

List_node list_create(){
    //May seem silly but its all in the spirit of encapsulation and abstraction :)
   return NULL;
}

List_node list_nodeCreate(void *data){
    List_node result = malloc(sizeof(struct node_t));
    if(result == NULL)
        return NULL;
    result->data = data;
    result->next = NULL;
    return result;
}

void list_destroy(List_node head){
    if(head != NULL){
        List_node temp = NULL;
        while(head != NULL){
            temp = head;
            head = head->next;
            free(temp);
            temp = NULL;
        }
        free(head);
        head = NULL;
    }
}

List_node list_append(List_node head, void *data){
    List_node temp = head;
    List_node append = list_nodeCreate(data);
    if(append == NULL)
        return NULL;
    if(head == NULL)
        head = append;
    else{    
        append->next = temp;
        head = append;
    }
    return append;
}

List_node list_pop(List_node head){
    List_node result = head->next;
    free(head);
    head = NULL;
    return result; 
}

typedef struct l_iterator{
    List_node nextItem;
}*List_iterator;


List_iterator list_iterator_create(List_node head){
    List_iterator result = malloc(sizeof(struct l_iterator));
    result->nextItem = head;
    return result;
}

void list_iterator_destroy(List_iterator* it){
    free(*it);
    *it = NULL;
}

bool list_hasNext(List_iterator it){
    return it->nextItem != NULL;
}

void* list_next(List_iterator it){
    void* result = it->nextItem->data;
    it->nextItem = it->nextItem->next;
    return result;
}

void* list_iterate(List_iterator it){
    void* result = NULL;
    if(list_hasNext(it))
        result = list_next(it);
    return result;
}