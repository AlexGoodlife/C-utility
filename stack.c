#include <stdlib.h>
#include <string.h>
#include "stack.h"

typedef struct s_node{
    void* data;
    struct s_node *next;
}*Stack_node;

typedef struct stack_t{
    struct s_node *top;
    size_t size;
}*Stack;


Stack_node snode_create(void *data){
    Stack_node result = malloc(sizeof(struct s_node));
    result->data = data;
    result->next = NULL;
    return result;
}

Stack stack_create(){
    Stack result = malloc(sizeof(struct stack_t));
    result->top = NULL;
    result->size = 0;
    return result;
}

void stack_destroy(Stack stack){
    Stack_node tmp = stack->top;
    while(tmp != NULL){
        Stack_node toDelete = tmp;
        tmp = tmp->next;
        free(toDelete);
    }
    free(stack);
}

int stack_isEmpty(Stack stack){
    return stack->size == 0;
}

int stack_getSize(Stack stack){
    return stack->size;
}

void stack_push(Stack stack, void *data){
    Stack_node push = snode_create(data);
    push->next = stack->top;
    stack->top = push;
    stack->size++;
}

void* stack_pop(Stack stack){
    void* result = NULL;
    result = stack->top->data;
    Stack_node next = stack->top->next;
    free(stack->top);
    stack->top = next;
    stack->size--;
    return result;
}

void *stack_peek(Stack stack){
    return stack->top->data;
}

size_t stack_export(Stack stack, void**output){
    size_t result = 0;
    Stack_node head = stack->top;
    while(head != NULL){
        output[result++] = head->data;
        head = head->next;
    }
    return result;
}
