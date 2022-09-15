/**
 * @file queue.c
 * @author Alexandre Boavida (novaisboavida@gmail.com)
 * @brief source for functions and structs defined in queue.h
 */

#include <stdlib.h>
#include "../include/queue.h"
#include "../include/list.h"

typedef struct queue_t{
    List_node head;
    List_node tail;
    size_t size;
}*Queue;

Queue queue_create(){
    Queue result = malloc(sizeof(struct queue_t));
    if(result == NULL)
        return NULL;
    result->head = NULL;
    result->tail = NULL;
    result->size = 0;
    return result;
}

void queue_destroy(Queue* q){
    List_node tmp = (*q)->head;
    while(tmp != NULL){
        tmp = list_pop(tmp);
    }
    free(*q);
    *q = NULL;
}

size_t queue_getSize(Queue q){
    return q->size;
}

bool queue_enqueue(Queue q, void* data){
    List_node add = list_nodeCreate(data);
    if(add == NULL)
        return false;
    if(q->tail != NULL)
        q->tail->next = add;
    q->tail = add;
    if(q->head == NULL)
        q->head = add;
    q->size++;
    return true;
}

void* queue_dequeue(Queue q){
    void* result = NULL;
    List_node temp = q->head;

    result = q->head->data;
    q->head = q->head->next;
    q->size--;
    free(temp);
    if(q->size == 0)
        q->tail = NULL;
    return result;
}

size_t queue_export(Queue q, void**output){
    size_t result = 0;
    List_node head = q->head;
    while(head != NULL){
        output[result++] = head->data;
        head = head->next;
    }
    return result;
}