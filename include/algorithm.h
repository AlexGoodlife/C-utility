/**
 * @file algorithm.h
 * 
 * @author Alexandre Boavida (novaisboavida@gmail.com)
 * 
 * @brief Function prototypes for algorithm functions
 * 
 * @date 2022-09-09
 */

#ifndef ALGORITHM_SIMPLE_H
#define ALGORITHM_SIMPLE_H

#include <stdbool.h>

/**
 * @brief Generic linear search function, finds a target reference in a generic unsorted or sorted array in O(n) time
 * 
 * @param array the array to search
 * @param array_size the size(length) of the array to search
 * @param data_size data size of array elements i.e sizeof(some_type)
 * @param target element to look for in the array, should be passed by reference
 * @param cmp comparison function which the function uses to check if it has reached its target. Comparison functions are to be made like the ones used for qsort(LibC)
 * @return size_t the index of the target in the array. returns -1 if it is not found
 */
size_t linear_search(void *array, size_t array_size, size_t data_size,void* target, int (*cmp)(const void*, const void*));

size_t linear_lastsearch(void *array, size_t array_size, size_t data_size,void* target, int (*cmp)(const void*, const void*));

/**
 * @brief Generic binary search functon, 
 * 
 * @param array the array to search, finds a target reference in a generic sorted array in O(log(n)) time
 * @param array_size the size(length) of the array to search
 * @param data_size data size of array elements i.e sizeof(some_type)
 * @param target  element to look for in the array, should be passed by reference
 * @param cmp comparison function which the function uses to check if it has reached its target. Comparison functions are to be made like the ones used for qsort(LibC)
 * @return size_t index of the target in the array. returns -1 if it is not found
 */
size_t binary_search(void *array, size_t array_size, size_t data_size, void *target, int (*cmp)(const void*, const void*));

size_t binary_lastsearch(void *array, size_t array_size, size_t data_size, void *target, int (*cmp)(const void*, const void*));

/**
 * @brief Helper function for merge sort. Merges two arrays "a" and "b" and sorts them, holding the result in "temp. Resulting array has size n+m
 * 
 * @param a first array to merge
 * @param n size(length) of the first array to merge
 * @param b second array to merge
 * @param m size(length) of the second array to merge
 * @param temp array that will hold the resulting merged array
 * @param data_size data size of array elements i.e sizeof(some_type)
 * @param cmp comparison function which the function uses to check if it has reached its target. Comparison functions are to be made like the ones used for qsort(LibC)
 */
void merge(void *a, size_t n, void* b, size_t m, void* temp,size_t data_size,int (*cmp)(const void*,const void*));

/**
 * @brief Generic merge sort function, sorts arrays in O(nlog(n)) time
 * 
 * @param array the array to sort
 * @param array_size size(length) of array to sort
 * @param data_size data size of array elements i.e sizeof(some_type)
 * @param cmp comparison function which the function uses to check if it has reached its target. Comparison functions are to be made like the ones used for qsort(LibC)
 */
void merge_sort(void *array, size_t array_size, size_t data_size, int (*cmp)(const void*,const void*));

/**
 * @brief Generic insertion sort function, sorts arrays in O(n^2) time
 * 
 * @param array the array to sort
 * @param array_size size(length) of array to sort
 * @param data_size data size of array elements i.e sizeof(some_type)
 * @param cmp comparison function which the function uses to check if it has reached its target. Comparison functions are to be made like the ones used for qsort(LibC)
 */
void insertion_sort(void*array , size_t array_size, size_t data_size, int (*cmp)(const void*,const void*));

/**
 * @brief Swaps the contents pointed to by two pointers
 * 
 * @param x data to swap
 * @param y data to swap
 * @param data_size size of data to swap
 */
void swap(void *x , void *y, size_t data_size);

/**
 * @brief Clones an array by dynamically allocating and copying memory from source array
 * 
 * @param array array to be cloned
 * @param array_size size of entry and exit array
 * @param data_size data size of elements in array
 * @return cloned array pointer 
 */
void* array_clone(void*array, size_t array_size, size_t data_size);

/**
 * @brief Checks if a given target is contained in a given array, must be passed by reference
 * 
 * @param array array to search
 * @param array_size size of array to search
 * @param data_size data size of elements in array
 * @param cmp comparison function which the function uses to check if it has reached its target
 * @param target element to look for in the array, should be passed by reference
 * @return true if element is contained
 * @return false if element is not contained
 */
bool array_contains(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*), const void* target);

/**
 * @brief Removes element from an array without allocating a new array at a certain index and returns the resulting array size
 * 
 * @param array array to delete in
 * @param array_size size of the array
 * @param data_size data size of elements in array
 * @param index index of element to delete
 * @return size of resulting array 
 */
size_t array_remove(void* array, size_t array_size, size_t data_size, size_t index);

/**
 * @brief Removes duplicates from array without allocating a new array and returns its size
 * 
 * @param array array to remove duplicates from
 * @param array_size size of the array
 * @param data_size data size of elements in array
 * @param cmp comparison function which the function uses to compare values
 * @param sorted True if array is sorted, false otherwise (Used to determine algorithm to use)
 * @return size of the array with duplicates removed
 */
size_t array_rmdups(void *array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*), bool sorted);

/**
 * @brief Removes duplicates from array, result is stored in seperate array that is dynamically allocated
 * 
 * @param array array to remove duplicates from
 * @param array_size size of the array
 * @param data_size data size of elements in array
 * @param cmp comparison function which the function uses to compare values
 * @param sorted True if array is sorted, false otherwise (Used to determine algorithm to use)
 * @param returnSize Reference to int or unsigned int, will hold final array size
 * @return pointer to resulting array without duplicates
 */
void* array_rmdups_new(void *array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*), bool sorted, size_t* returnSize);

/**
 * @brief Finds maximum value in an array
 * 
 * @param array array to find max in
 * @param array_size  size of the array
 * @param data_size data size of elements in array
 * @param cmp comparison function which the function uses to compare values
 * @return maximum value in array (by reference)
 */
void* array_max(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*));

/**
 * @brief Finds minimum value in an array
 * 
 * @param array array to find min in
 * @param array_size  size of the array
 * @param data_size data size of elements in array
 * @param cmp comparison function which the function uses to compare values
 * @return minimum value in array (by reference)
 */
void* array_min(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*));

/**
 * @brief Finds maximum value index in an array
 * 
 * @param array array to find max index in
 * @param array_size  size of the array
 * @param data_size data size of elements in array
 * @param cmp comparison function which the function uses to compare values
 * @return maximum value index in array
 */
size_t array_argmax(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*));

/**
 * @brief Finds minimum value index in an array
 * 
 * @param array array to find min index in
 * @param array_size size of the array
 * @param data_size data size of elements in array
 * @param cmp comparison function which the function uses to compare values
 * @return minimum value index in array
 */
size_t array_argmin(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*));

/**
 * @brief Filters array in accordance to function provided, doesn't allocated any more memory, mutates existing array
 * 
 * @param array array to filter
 * @param array_size size of the array
 * @param data_size data size of elements in array
 * @param func Function to dictate the filtration process
 * @return size of resulting array 
 */
size_t array_filter(void* array, size_t array_size, size_t data_size, bool(*func)(const void*));

/**
 * @brief Filters array in accordance to function provided by allocating new array dynamically
 * 
 * @param array array to filter
 * @param array_size size of the array
 * @param data_size data size of elements in array
 * @param func Function to dictate the filtration process
 * @param returnSize Reference to int or unsigned int, will hold final array size
 * @return pointer to resulting array
 */
void* array_filter_new(void* array, size_t array_size, size_t data_size, bool(*func)(const void*), size_t* returnSize);

#endif