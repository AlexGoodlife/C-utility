/**
 * @file arraylist.h
 * @author Alexandre Boavida (novaisboavida@gmail.com)
 * @brief Struct and function prototypes for array list functions
 * @date 2022-09-24
 * 
 */

#ifndef ARRAYLIST_SIMPLE_H
#define ARRAYLIST_SIMPLE_H

#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief
 *  typedef struct arraylist_t{
 *  void* array;
 *   size_t length;
 *   size_t capacity;
 *   size_t data_size;
 *   int (*cmp)(const void*, const void*);
 *   bool sorted;
 *  }*ArrayList;
 * 
 *  Private data type
 */

typedef struct arraylist_t *ArrayList;

/**
 * @brief Creates arraylist holding members of 'data_size' size
 * 
 * @param data_size data size of elements to store
 * @param cmp comparison function to use in arraylist functions
 * @return the array list created
 */
ArrayList arraylist_create(size_t data_size, int (*cmp)(const void*,const void*));

/**
 * @brief Destroys created array list
 * 
 * @param a array list to destroy, passed by reference
 */
void arraylist_destroy(ArrayList* a);

/**
 * @brief Returns the length of stored elements in array list
 * 
 * @param a array list to get length from
 * @return length of stored elements in array list
 */
size_t arraylist_getLength(ArrayList a);

/**
 * @brief Adds data to array list
 * 
 * @param a array list to add data to
 * @param data data to add
 * @return true if successful
 * @return false if unsuccessful
 */
bool arraylist_add(ArrayList a, void* data);

/**
 * @brief Adds all data from target array to the end of arraylist 
 * 
 * @param a array list to add array to
 * @param array array to copy data from
 * @param array_size array size of target array
 * @return true if successfull
 * @return false if unsuccessfull
 */
bool arraylist_addArray(ArrayList a, void* array, size_t array_size);

/**
 * @brief Clears all data in array list
 * 
 * @param a array list to clear
 */
void arraylist_clear(ArrayList a);

/**
 * @brief Clones array list, memory is allocated dynamically
 * 
 * @param a array list to clone
 * @return cloned ArrayList 
 */
ArrayList arraylist_clone(ArrayList a);

/**
 * @brief Checks if given target is present in array list
 * 
 * @param a array list to check for target
 * @param target target to search in array list
 * @return true if target is present
 * @return false if target is not present
 */
bool arraylist_contains(ArrayList a, void* target);

/**
 * @brief Gets data present in array list at given index
 * 
 * @param a array list to search
 * @param index index of desired data in array list
 * @return void* to data 
 */
void* arraylist_get(ArrayList a, size_t index);

/**
 * @brief finds a given target in array list
 * 
 * @param a array list to search
 * @param target target data to find in array
 * @return index of data in array 
 */
size_t arraylist_find(ArrayList a, void* target);

/**
 * @brief Removes data at given index, mutates array list
 * 
 * @param a array list to remove data in
 * @param index index of data to remove
 */
void arraylist_removeIndex(ArrayList a, size_t index);

/**
 * @brief Sorts array list using merge sort
 * 
 * @param a array list to sort
 */
void arraylist_sort(ArrayList a);

/**
 * @brief Checks if array list is empty
 * 
 * @param a array list to check
 * @return true if empty
 * @return false if not empty
 */
bool arraylist_isEmpty(ArrayList a);

/**
 * @brief Sets data at specified index to desired data
 * 
 * @param a array list to set data in
 * @param index index to where data is to be set
 * @param data data to set in desired index
 * @return true if successful
 * @return false if unsuccesful
 */
bool arraylist_set(ArrayList a, size_t index, void* data);

/**
 * @brief Returns dynamically allocated array containing all data in array list
 * 
 * @param a array list to get data from
 * @return void* to resulting array 
 */
void* arraylist_toArray(ArrayList a);

/**
 * @brief Reserves memory in arraylist, will only do so if requested memory to reserve is larger than current number of elements
 * 
 * @param a array list to reserve memory
 * @param capacity number of elements to reserve 
 * @return true if successful
 * @return false if unsuccessful
 */
bool arraylist_reserve(ArrayList a, size_t capacity);

/**
 * @brief Finds last occurence of given target in array list
 * 
 * @param a array list to search
 * @param target target to find last occurence of 
 * @return index of last occurence of data
 */
size_t arraylist_findLast(ArrayList a, void* target);

/**
 * @brief Loops through array list and runs function specified to all data present
 * 
 * @param a array list to loop through
 * @param func desired function
 */
void arraylist_foreach(ArrayList a, void (*func)(void*));

/**
 * @brief Filters array list based on specified function
 * 
 * @param a array list to filter
 * @param func desired function
 * @return size of resulting arraylist size
 */
size_t arraylist_filter(ArrayList a, bool(*func)(const void*));

/**
 * @brief Removes duplicate data from array list
 * 
 * @param a array list to remove duplicates from
 * @return length of resulting array list 
 */
size_t arraylist_rmdups(ArrayList a);

/**
 * @brief Returns maximum value of array list
 * 
 * @param a array list to search
 * @return void* to maximum value
 */
void* arraylist_max(ArrayList a);

/**
 * @brief Returns minimum value of array list
 * 
 * @param a array list to search
 * @return void* to minimum value
 */
void* arraylist_min(ArrayList a);

/**
 * @brief Returns index of maximum value in array list
 * 
 * @param a array list to search
 * @return index of maximum value 
 */
size_t arraylist_argmax(ArrayList a);

/**
 * @brief Returns index of minimum value in array list
 * 
 * @param a array list to search
 * @return index of minimum value 
 */
size_t arraylist_argmin(ArrayList a);

/**
 * @brief Trims array list capacity to its length only (used to save memory)
 * 
 * @param a array list to trim
 * @return length of array list 
 */
size_t arraylist_shrinkToSize(ArrayList a);

/**
 * @brief Swaps two elements of an array list
 * 
 * @param a array list to swap element 
 * @param i index of first element
 * @param j index of second element
 */
void arraylist_swap(ArrayList a, size_t i, size_t j);


typedef struct arraylist_it *ArrayList_iterator;

ArrayList_iterator arraylist_it_create(ArrayList arraylist);

void arraylist_it_destroy(ArrayList_iterator* it);

void* arraylist_Next(ArrayList_iterator it);

bool arraylist_hasNext(ArrayList_iterator it);

void* arraylist_iterate(ArrayList_iterator it);

void arraylist_it_reset(ArrayList_iterator it);

#endif