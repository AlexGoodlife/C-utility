/**
 * @file heap.h
 * @author alexandre Boavida (novaisboavida@gmail.com)
 * @brief function prototypes and structs relating to heaps
 * @date 2022-09-15
 * 
 */
#ifndef HEAP_SIMPLE_H
#define HEAP_SIMPLE_H

#include <stdbool.h>
#include "../include/algorithm.h"

/**
 * @brief Struct that encapsulates Heap, contains heap array, its size and type
 * 
 */
typedef struct heap_t *Heap;

/**
 * @brief Dynamically allocates heap
 * 
 * @param data_size size of data to put in the heap
 * @param max_heap boolean value to determine heap type, set to true for a max heap and false for a min heap
 * @param cmp comparison function to be used in lookup
 * @return Heap 
 */
Heap heap_create(size_t data_size, bool max_heap, int (*cmp)(const void*, const void*));

/**
 * @brief Deallocates memory used by heap
 * 
 * @param heap heap to destroy
 */
void heap_destroy(Heap *heap);

/**
 * @brief Removes element from top of heap
 * 
 * @param heap heap to pop
 */
void heap_pop(Heap heap);

/**
 * @brief returns pointer to top of heap, will get replaced if you pop afterwards so be careful
 * 
 * @param heap heap to peek
 * @return void* data at top of heap
 */
void* heap_peek(Heap heap);

/**
 * @brief Push data into heap
 * 
 * @param heap heap to push into
 * @param data data to push into heap
 */
void heap_push(Heap heap, void* data);

/**
 * @brief Dynamically allocates pointer and copies memory of top of heap into it, afterwards pops the heap. Free this pointer when done
 * 
 * @param heap heap to peek and pop
 * @return void* 
 */
void* heap_peekpop(Heap heap);

/**
 * @brief Returns size of heap
 * 
 * @param heap 
 * @return size_t 
 */
size_t heap_getSize(Heap heap);

#endif