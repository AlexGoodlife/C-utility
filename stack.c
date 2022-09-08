#include <stdlib.h>
#include <string.h>
#include "stack.h"

typedef struct stack_t{
    void *array;
    size_t capacity;
    size_t top_index;
    size_t data_size;
}*Stack;

Stack stack_create(size_t size, size_t data_size){
    Stack result = malloc(sizeof(struct stack_t));
    result->array = malloc(data_size*size);
    result->capacity = size;
    result->data_size = data_size;
    result->top_index = -1;
    return result;
}

void stack_destroy(Stack stack){
    free(stack->array);
    free(stack);
}

int stack_isEmpty(Stack stack){
    return stack->top_index == -1;
}

int stack_isFull(Stack stack){
    return stack->top_index == stack->capacity -1;
}

void stack_push(Stack stack, void *data){
    if(!stack_isFull(stack)){
        memcpy(stack->array + (++(stack->top_index)) *stack->data_size, data, stack->data_size);
    }
}

void *stack_pop(Stack stack){
    void *result = calloc(1, stack->data_size);
    // void *result = NULL;
    if(!stack_isEmpty(stack)){
        // result = stack->array + (stack->top_index-- * stack->data_size);
        result = memcpy(result, stack->array + (stack->top_index-- * stack->data_size), stack->data_size);
        // memcpy(result, stack->array + (stack->top_index-- * stack->data_size), stack->data_size);
        // free(stack->array[stack->top_index--]);
    }
    return result;
}

void *stack_peek(Stack stack){
    void *result = NULL;
    // void *result = calloc(1, stack->data_size);
    if(!stack_isEmpty(stack)){
        result = stack->array + (stack->top_index * stack->data_size);
        // result = memcpy(result, stack->array + (stack->top_index * stack->data_size), stack->data_size);
        // memcpy(result, stack->array + (stack->top_index * stack->data_size), stack->data_size);
    }
    return result;
}