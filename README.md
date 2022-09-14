# Generic data structures and algorithms

This library serves as a useful addition to any C program that might need a certain data structure or algorithm without the need to write it yourself.  
These functions and structs were made as an educational exercise but they can serve a purpose as a simple and lightweight library.

This library was made in Windows with it in consideration so performance on other OS systems is unknown

## Tools

 - [ ] Hash tables
 - [ ] Stacks
 - [ ] Linked Lists 
 - [ ] Queues 
 - [ ] Binary search Trees
 - [ ] Several algorithms like merge sort and binary search

## Installation and compilation
   To install, download the include folder and the lib folder and paste them in your C library path.  

   To compile you just have to link the libraries to your program, as an example compilation statement using gcc:  
   >gcc your_program.c -IC:\YourIncludePath -LC:\YourLibraryPath -lcutility -o executable_name

   Alternatively you can copy the source and header files and compile them with your program

## Todo
   - [ ] doubly linked list, heaps and graphs
   - [ ] More algorithms


# Example usage

## Hash table
``` C
         // PSEUDO CODE
         typedef any_struct example_t
         typedef any_key key_t

         example_t* someone;
         key_t* someone_key;

         example_t* something;
         keyt_t* something_key;

         // Write your hash and cmp functions
         size_t some_hash(const void* key, size_t table_capacity);
         int some_cmp_func(const void*key1, const void* key2);

         Hash_table table = hash_table_create(any number, some_hash, some_cmp_func);

         someone = malloc(sizeof(example_t));
         someone_key = malloc(sizeof(key_t));

         something = malloc(sizeof(example_t));
         something_key = malloc(sizeof(key_t));

         // INITIALIZE YOUR VARIABLES 
         someone.whatever = data;
         (...)

         //Set values in hash

         hash_set(table, someone, someone_key);
         hash_set(table, something, something_key);

         example_t* find_someone = hash_lookUp(someone_key);

         example_t* remove_something = hash_delete(something_key);

         // Free your pointers when you want to
         free(...)

         //Destroy table when done
         hash_table_destroy(table)
```
## Linked list
```C

         // PSEUDO CODE
         typedef any_struct example_t

         example_t* someone;

         example_t* something;

         someone = malloc(sizeof(example_t));

         something = malloc(sizeof(example_t));

         // INITIALIZE YOUR VARIABLES 
         someone.whatever = data;
         (...)

         List_node list = List_create();
         //ALTERNATIVELY

         List_node list = NULL;

         list = list_append(list, someone);
         list = list_append(list, something);

         // USE THE LINKED LIST HOWEVER YOU WANT ITS EXPLICIT

         list = list_pop(list);

         // Free your pointers when you want to
         free(...)

         //Destroy list when done
         list_destroy(list)
```
## Stack
```C
         //Pseudo code
         typedef any_struct example_t

         example_t * array[size] = {example_t*, (...)};

         //Create your stack
         Stack stack = stack_create();

         // Push elements and pop elements
         stack_push(stack,array[index]);
         stack_push(stack,array[other_index]);

         example_t* popped = stack_pop(stack);

         example_t* peek = stack_peek(stack);

         //Free your pointers when done

         free(...)

         //Destroy the stack
         stack_destroy(stack);
```
## Queue
```C
         //Pseudo code
         typedef any_struct example_t

         example_t * array [size] = {example_t*, (...)};

         //Create your queue
         Queue q= queue_create();

         // Enqueue and dequeue elements
         queue_enqueue(q, array[index]);
         queue_enqueue(q, array[other_index]);

         example_t* dequeued = queue_dequeue(stack);

         //Free your pointers when done

         free(...)

         //Destroy the queue
         queue_destroy(q);
```
## Binary search tree
```C
         // PSEUDO CODE
         typedef any_struct example_t
         typedef any_key key_t

         example_t* someone;
         key_t* someone_key;

         example_t* something;
         keyt_t* something_key;

         // Write your cmp functions
         int some_cmp_func(const void*key1, const void* key2);

         BS_tree tree = bst_create(some_cmp_func);

         someone = malloc(sizeof(example_t));
         someone_key = malloc(sizeof(key_t));

         something = malloc(sizeof(example_t));
         something_key = malloc(sizeof(key_t));

         // INITIALIZE YOUR VARIABLES 
         someone.whatever = data;
         (...)

         bst_insert(tree, someone, someone_key);
         bst_insert(tree, something, something_key);

         example_t* lookup = bst_lookup(someone_key);

         //Do whatever you want

         // Free your pointers when you want to
         free(...)

         //Destroy tree when done
         tree_destroy(tree)
```
## Algorithms
```C
         //Pseudo code

         // Make your comparison function
         int cmp(const void*x, const void*y);

         int array[10] = {10,2,3,1,5,6,4,8,7,6};

         merge_sort(array, 10, sizeof(int), cmp);

         All algorithm functions follow this format and work with any data type
```