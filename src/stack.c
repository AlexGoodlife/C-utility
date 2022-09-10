/**
 * @file stack.c
 * @author Alexandre Boavida (novaisboavida@gmail.com)
 * @brief source for functions and structs defined in stack.h
 */

#include <stdlib.h>
#include <string.h>
#include "../include/stack.h"
#include "../include/list.h"

typedef struct stack_t{
    List_node top;
    size_t size;
}*Stack;

Stack stack_create(){
    Stack result = malloc(sizeof(struct stack_t));
    if(result == NULL)
        return NULL;
    result->top = NULL;
    result->size = 0;
    return result;
}

void stack_destroy(Stack stack){
    List_node tmp = stack->top;
    while(tmp != NULL){
        tmp = list_pop(tmp);
    }
    free(stack);
}

bool stack_isEmpty(Stack stack){
    return stack->size == 0;
}

int stack_getSize(Stack stack){
    return stack->size;
}

bool stack_push(Stack stack, void *data){
    stack->top = list_append(stack->top, data);
    if(stack->top == NULL)
        return false;
    stack->size++;
    return true;
}

void* stack_pop(Stack stack){
    void* result = NULL;
    result = stack->top->data;
    stack->top = list_pop(stack->top);
    stack->size--;
    return result;
}

void *stack_peek(Stack stack){
    return stack->top->data;
}

size_t stack_export(Stack stack, void**output){
    size_t result = 0;
    List_node head = stack->top;
    while(head != NULL){
        output[result++] = head->data;
        head = head->next;
    }
    return result;
}
