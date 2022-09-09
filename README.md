# Generic data structures and algorithms

This library serves as a useful addition to any C program that might need a certain data structure or algorithm without the need to write it yourself.  
These functions and structs were made as an educational exercise but they can serve a purpose as a simple and lightweight library.

This library was made in Windows with it in consideration so performance on other OS systems is unknown

## Tools

 - [ ] Hash table struct 
 - [ ] Stack struct 
 - [ ] Queue struct
 - [ ] Several algorithms like merge sort and binary search

## Installation and compilation
   To install, download the include folder and the lib folder and paste them in your C library path.  

   To compile you just have to link the libraries to your program, as an example compilation statement using gcc:  
   >gcc your_program.c -IC:\YourIncludePath -LC:\YourLibraryPath -lcutility -o executable_name

   Alternatively you can copy the source and header files and compile them with your program

## Todo
   - [ ] Trees, heaps and graphs
   - [ ] More algorithms


# Example usage

## Hash table

         // PSEUDO CODE
         typedef any_struct example_t
         typdef any_key key_t

         example_t* someone;
         key_t* someone_key;

         example_t* something;
         keyt_t* something_key;

         size_t some_hash(const void* key, size_t table_capacity);
         int some_cmp_func(const void*key1, const void* key2);

         Hash_table table = hash_table_create(any number, some_hash, some_cmp_func);

         someone = malloc(sizeof(example_t));
         someone_key = malloc(sizeof(key_t));

         something = malloc(sizeof(example_t));
         something_key = malloc(sizeof(key_t));

         // INITIALIZE YOUR VARIABLES 

         hash_set(table, someone, someone_key);
         hash_set(table, something, something_key);

         example_t* find_someone = hash_lookUp(someone_key);

         example_t* remove_something = hash_delete(something_key);

         // Free your pointers when you want to
         free(...)

         //Destroy table when done
         hash_table_destroy(table)

         


