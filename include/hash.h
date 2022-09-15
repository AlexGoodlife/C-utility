/**
 * @file hash.h
 * @author Alexandre Boavida (novaisboavida@gmail.com)
 * @brief struct declaration and function prototypes refering to the Hash_table struct
 * 
 * @date 2022-09-09
 *  * 
 */

#ifndef HASH_SIMPLE_H
#define HASH_SIMPLE_H

#include <stdbool.h>

/**
 * @brief main hash table struct, 
 * holds pointer array of hash_elements, its capacity, the number of elements stored and respective hash functions and comparison functions
 * collisions are handled with chaining of hash elements
 */
typedef struct h_table *Hash_table;

/**
 * @brief allocates a hash table dynamically on the heap and returns its pointer. (Call hash_delete when done with the table)
 * 
 * @param capacity the max size of the hash table
 * @param hash_function hash function to map elements, 
 * accepts whatever key struct desired and a size_t for the capacity of the table (Ensuring things dont get mapped out of memory)
 * 
 * @param key_cmp comparison function for keys,
 * used to compare for key structs in hash_lookup and hash_delete, is made in the same style as qsort(LibC) comparison functions,
 * bad comparison functions will lead to a crash so it is advised to be careful with your pointers
 * 
 * @return The Hash_table created  or NULL if not enough memory
 */

Hash_table hash_table_create(size_t capacity,size_t (*hash_function)(const void*, size_t),int (*key_cmp)(const void*, const void*));

/**
 * @brief Frees the memory allocated in hash_table_create, it DOES NOT free the memory of the elements set in it.
 * 
 * @param map Hash_table to destroy passed by reference
 */
void hash_table_destroy(Hash_table* map);

/**
 * @brief Debug function, prints pointers of hash elements and their respective next pointers in order to vizualize them
 * 
 * @param map Hash_table to print
 */

void hash_print(Hash_table map);

/**
 * @brief returns the amount of non NULL elements stored in the hash table
 * 
 * @param map the hash table in question
 * @return size_t number of elements stored
 */

size_t hash_getSize(Hash_table map);

/**
 * @brief Sets a value inside the hash_table
 * 
 * @param map the hash_table which to set the value in
 * @param data data to set in table 
 * @param key key struct which to pass in the hash_table's hash function to map it to an index
 * @return true if successful, false if unsuccessful(Ran out of memory)
 */
bool hash_set(Hash_table map, void* data, void* key);

/**
 * @brief returns data associated to a key
 * 
 * @param map hash_table to look up data in
 * @param key key struct associated to data
 * @return void* data that was in hash table index corresponding to the key provided
 */
void *hash_lookup(Hash_table map, void *key);

/**
 * @brief removes data associated to key from a hash_table and returns its pointer
 * 
 * @param map hash_table to remove data in
 * @param key key struct associated to data to remove
 * @return void* data that was removed from the hash_table
 */
void* hash_delete(Hash_table map, void* key);

/**
 * @brief Stores all non NULL values in the hash_table into output array and returns its size,
 * output array must be casted, example:
 *  size_t size = hash_extract_values(some_table, (void**)some_array);
 * 
 * @param map the hash table to extract values from
 * @param output array in which to store values
 * @return size_t size(length) of final output array
 */
size_t hash_extract_values(Hash_table map,void **output);

/**
 * @brief Stores all keys of non NULL values in the hash_table into output array and returns its size,
 *  output array must be casted, example:
 *  size_t size = hash_extract_keys(some_table, (void**)some_array);
 * 
 * @param map the hash table to extract keys from
 * @param output array in which to store values
 * @return size_t size(length) of final output array
 */
size_t hash_extract_keys(Hash_table map, void **output);


/**
 * @brief Applies function func to every non NULL element data present in Hash table
 * 
 * @param map hash table to loop through
 * @param func function to apply to every element data
 */
void hash_foreach(Hash_table map, void (*func)(void*));

#endif