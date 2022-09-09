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


#endif