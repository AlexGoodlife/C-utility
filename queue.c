#include <stdlib.h>
#include "queue.h"

typedef struct q_node{
    void* data;
    struct q_node* next;
}*Q_node;

typedef struct queue_t{
    Q_node head;
    Q_node tail;
    size_t size;
}*Queue;

Q_node qnode_create(void *data){
    Q_node result = malloc(sizeof(struct q_node));
    result->data = data;
    result->next = NULL;
    return result;
}

Queue queue_create(){
    Queue result = malloc(sizeof(struct queue_t));
    result->head = NULL;
    result->tail = NULL;
    result->size = 0;
    return result;
}

void queue_destroy(Queue q){
    Q_node tmp = q->head;
    while(tmp != NULL){
        Q_node toDelete = tmp;
        tmp = tmp->next;
        free(toDelete);
    }
    free(q);
}

size_t queue_getSize(Queue q){
    return q->size;
}

void queue_enqueue(Queue q, void* data){
    Q_node add = qnode_create(data);
    if(q->tail != NULL)
        q->tail->next = add;
    q->tail = add;
    if(q->head == NULL)
        q->head = add;
    q->size++;
}

void* queue_dequeue(Queue q){
    void* result = NULL;
    Q_node temp = q->head;

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
    Q_node head = q->head;
    while(head != NULL){
        output[result++] = head->data;
        head = head->next;
    }
    return result;
}