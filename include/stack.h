/**
 * @file stack.h
 * @author Alexandre Boavida (novaisboavida@gmail.com)
 * @brief struct declaration and function prototypes refering to the Stack struct

 * @date 2022-09-09
 *  
 */
#ifndef STACK_SIMPLE_H
#define STACK_SIMPLE_H

#include <stdbool.h>


/**
 * @brief Stack struct, stores elements in LIFO order,holds size of the stack and top element pointer
 * 
 */
typedef struct stack_t *Stack;

/**
 * @brief Creates and allocates memory for a generic Stack, can hold all datatypes
 * 
 * @return created stack or NULL if not enough memory
 */
Stack stack_create();

/**
 * @brief Destroys created stack and frees memory, DOES NOT free memory held by the stack, only the stack itself
 * 
 * @param stack The stack to destroy, passed by reference
 */
void stack_destroy(Stack *stack);

/**
 * @brief Checks if the stack is empty
 * 
 * @param stack stack struct to check if empty
 * @return true if empty, false otherwise
 */
bool stack_isEmpty(Stack stack);

/**
 * @brief Returns the number of elements held by the stack
 * 
 * @param stack stack struct to get number of elements from
 * @return int number of elements in stack
 */
int stack_getSize(Stack stack);

/**
 * @brief Pushes element into the top of the stack
 * 
 * @param stack Stack struct which to push elements into
 * @param data data to be pushed into stack
 * @return true if successful, false if unsuccessful (Ran out of memory)
 */
bool stack_push(Stack stack, void *data);

/**
 * @brief Pops element from top of the stack
 * 
 * @param stack Stack struct which to pop elements from
 * @return void* data held by popped element
 */
void *stack_pop(Stack stack);

/**
 * @brief returns data of the top element of the stack without popping it
 * 
 * @param stack Stack struct which to peek
 * @return void* data held by top element
 */
void *stack_peek(Stack stack);

/**
 * @brief Exports stack data to output array,
 * output array must be casted, example:
 *  size_t size = stack_export(some_stack, (void**)some_array);
 * 
 * @param stack Stack which to export data from
 * @param output output array to store data into
 * @return size_t size(length) of final output array
 */
size_t stack_export(Stack stack, void**output);

typedef struct s_iterator *Stack_iterator;

Stack_iterator stack_iterator_create(Stack st);

void stack_iterator_destroy(Stack_iterator* it);

bool stack_hasNext(Stack_iterator it);

void* stack_next(Stack_iterator it);

void* stack_iterate(Stack_iterator it);

#endif