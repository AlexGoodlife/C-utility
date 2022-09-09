#ifndef QUEUE_SIMPLE_H
#define QUEUE_SIMPLE_H

typedef struct queue_t *Queue;

Queue queue_create();

void queue_destroy(Queue q);

size_t queue_getSize(Queue q);

void queue_enqueue(Queue q, void* data);

void* queue_dequeue(Queue q);

size_t queue_export(Queue q, void**output);

#endif