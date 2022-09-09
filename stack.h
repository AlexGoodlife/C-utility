#ifndef STACK_SIMPLE_H
#define STACK_SIMPLE_H

typedef struct stack_t *Stack;

Stack stack_create();

void stack_destroy(Stack stack);

int stack_isEmpty(Stack stack);

int stack_getSize(Stack stack);

void stack_push(Stack stack, void *data);

void *stack_pop(Stack stack);

void *stack_peek(Stack stack);

#endif