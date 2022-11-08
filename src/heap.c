/**
 * @file heap.c
 * @author Alexandre Boavida (novaisboavida@gmail.com)
 * @brief source code for heap.h
 * @date 2022-09-15
 *  
 */

#include <stdlib.h>
#include <string.h>
#include "../include/heap.h"
#include "../include/algorithm.h"

typedef struct heap_t{
    void* array;
    size_t array_size;
    size_t capacity;
    size_t data_size;
    int (*cmp)(const void*, const void*);
    bool max_heap;
}*Heap;

Heap heap_create(size_t data_size, bool max_heap, int (*cmp)(const void*, const void*)){
    Heap result = malloc(sizeof(struct heap_t));
    if(result == NULL)
        return NULL;
    result->capacity = 10;
    result->array = calloc(result->capacity,data_size);
    if(result->array == NULL)
        return NULL;
    result->array_size = 0;
    result->data_size = data_size;
    result->cmp = cmp;
    result->max_heap = max_heap;
    return result;
}

void heap_destroy(Heap *heap){
    free((*heap)->array);
    (*heap)->array = NULL;
    free(*heap);
}

void heapmax_heapify_up(Heap heap, size_t i){
    if(heap->array_size > 1){
    
        size_t largest = i;
        size_t left = 2*i + 1;
        size_t right = 2*i + 2;
        
        if(left < heap->array_size && heap->cmp((heap->array + heap->data_size*left), (heap->array + heap->data_size*largest))>0){
            largest = left;
        }
        if(right < heap->array_size && heap->cmp((heap->array + heap->data_size*right), (heap->array + heap->data_size*largest))>0){
            largest = right;
        }
        if(largest != i){
            swap(heap->array + (heap->data_size*i), heap->array + (heap->data_size*largest),heap->data_size);
            heapmax_heapify_up(heap, largest);
        }
    }
}

void heapmax_heapify_down(Heap heap, size_t i){
    if(heap->array_size > 1){
        size_t parent = (i-1) / 2;
        if(heap->cmp(heap->array + i*heap->data_size, heap->array + parent*heap->data_size) > 0){
            swap(heap->array + i*heap->data_size, heap->array + parent*heap->data_size,heap->data_size);
            heapmax_heapify_down(heap, parent);
        }
    }
}

void heapmin_heapify_up(Heap heap, size_t i){
    if(heap->array_size > 1){
        size_t smallest = i;
        size_t left = 2*i + 1;
        size_t right = 2*i + 2;
        
        if(left < heap->array_size && heap->cmp((heap->array + heap->data_size*left), (heap->array + heap->data_size*smallest))<0){
            smallest = left;
        }
        if(right < heap->array_size && heap->cmp((heap->array + heap->data_size*right), (heap->array + heap->data_size*smallest))<0){
            smallest= right;
        }
        if(smallest != i){
            swap(heap->array + (heap->data_size*i), heap->array + (heap->data_size*smallest),heap->data_size);
            heapmin_heapify_up(heap, smallest);
        }
    }
}

void heapmin_heapify_down(Heap heap, size_t i){
    if(heap->array_size > 1){
        size_t parent = (i-1) / 2;
        if(heap->cmp(heap->array + i*heap->data_size, heap->array + parent*heap->data_size) < 0){
            swap(heap->array + i*heap->data_size, heap->array + parent*heap->data_size,heap->data_size);
            heapmin_heapify_down(heap, parent);
        }
    }
}

void heap_push(Heap heap, void* data){
    ++heap->array_size;
    if(heap->array_size == heap->capacity){
        heap->capacity += heap->array_size >> 1;
        heap->array = realloc(heap->array, heap->capacity*heap->data_size);
    }
    memcpy(heap->array + ((heap->array_size-1)*heap->data_size), data, heap->data_size);
    
    if(heap->max_heap){
        heapmax_heapify_down(heap, heap->array_size-1);
    }
    else{
        heapmin_heapify_down(heap, heap->array_size-1);
    }
}

void heap_pop(Heap heap){
    if(heap->array_size > 0){
        void* last= heap->array + (heap->data_size*(heap->array_size-1));
        if(heap->array_size > 1)
            memcpy(heap->array, last, heap->data_size);
        heap->array_size--;
        if(heap->array_size < heap->capacity/4){
            heap->capacity = heap->capacity/2;
            heap->array = realloc(heap->array, heap->capacity*heap->data_size);
        }
        if(heap->max_heap){
            heapmax_heapify_up(heap, 0);
        }
        else{
            heapmin_heapify_up(heap,0);
        }
    }
}

void* heap_peek(Heap heap){
    if(heap->array_size > 0)
        return heap->array;
    else
        return NULL;
}

void* heap_peekpop(Heap heap){
    void* result = malloc(sizeof(heap->data_size));
    if(result == NULL)
        return NULL;
    memcpy(result, heap->array, heap->data_size);
    heap_pop(heap);
    return result;
}

size_t heap_getSize(Heap heap){
    return heap->array_size;
}

