#ifndef HEAP_SIMPLE_H
#define HEAP_SIMPLE_H

#include <stdbool.h>
#include "../include/algorithm.h"

typedef struct heap_t *Heap;

Heap heap_create(size_t data_size, bool max_heap, int (*cmp)(const void*, const void*));

void heap_destroy(Heap *heap);

void heap_pop(Heap heap);

void* heap_peek(Heap heap);

void heap_push(Heap heap, void* data);

void* heap_peekpop(Heap heap);

#endif