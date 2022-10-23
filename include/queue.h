/**
 * @file queue.h
 * @author Alexandre Boavida (novaisboavida@gmail.com)
 * @brief struct declaration and function prototypes refering to the Queue struct

 * @date 2022-09-09
 * 
 */
#ifndef QUEUE_SIMPLE_H
#define QUEUE_SIMPLE_H

#include <stdbool.h>


/**
 * @brief Queue struct, stores elements in FIFO order,holds size of the queue and head and tail pointers for its elements
 * 
 */
typedef struct queue_t *Queue;

/**
 * @brief Creates and allocates memory for a generic queue, can hold all data types
 * 
 * @return created queue, or NULL if not enough memory
 */
Queue queue_create();

/**
 * @brief Frees all memory allocated by the queue, DOES NOT free the data held by the queue, only the queue itself
 * 
 * @param q The queue to destroy passed by reference
 */
void queue_destroy(Queue* q);


/**
 * @brief Returns size of the queue
 * 
 * @param q the queue, which to get the size from 
 * @return size_t number of elemnts in the queue
 */
size_t queue_getSize(Queue q);

/**
 * @brief Enqueues data into the queue 
 * 
 * @param q queue which to enqueue element in
 * @param data element data to enqueue
 * @return true if successful, false if unsuccessful (ran out of memory)
 */
bool queue_enqueue(Queue q, void* data);

/**
 * @brief Dequeues last element in queue and returns its pointer
 * 
 * @param q queue which to dequeue
 * @return void* data of element dequeued
 */
void* queue_dequeue(Queue q);

/**
 * @brief Exports queue data to output array,
 * output array must be casted, example:
 *  size_t size = queue_export(some_queue, (void**)some_array);
 * 
 * @param q queue to export data from
 * @param output output array to store data in
 * @return size_t size(length) of final output array
 */
size_t queue_export(Queue q, void**output);

typedef struct q_iterator *Queue_iterator;

Queue_iterator queue_iterator_create(Queue q);

void queue_iterator_destroy(Queue_iterator* it);

bool queue_hasNext(Queue_iterator it);

void* queue_next(Queue_iterator it);

void* queue_iterate(Queue_iterator it);

#endif