#ifndef ALGORITHM_SIMPLE_H
#define ALGORITHM_SIMPLE_H

size_t linear_search(void *array, size_t array_size, size_t data_size,void* target, int (*cmp)(const void*, const void*));

size_t binary_search(void *array, size_t array_size, size_t data_size, void *target, int (*cmp)(const void*, const void*));

void merge(void *a, size_t n, void* b, size_t m, void* temp,size_t data_size,int (*cmp)(const void*,const void*));

void merge_sort(void *array, size_t array_size, size_t data_size, int (*cmp)(const void*,const void*));

void insertion_sort(void*array , size_t array_size, size_t data_size, int (*cmp)(const void*,const void*));


#endif