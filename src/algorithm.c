/**
 * @file algorithm.c
 * @author Alexandre Boavida (novaisboavida@gmail.com)
 * @brief source for functions defined in algorithm.h
 * @date 2022-09-09
 * 
 */

#include <stdlib.h>
#include <string.h>

#include "../include/algorithm.h"

size_t linear_search(void *array, size_t array_size, size_t data_size,void* target, int (*cmp)(const void*, const void*)){
    for(size_t i= 0; i < array_size;i++){
        void *current = array + (i*data_size);
        if(cmp(target, current) == 0)
            return i;
    }
    return -1;
}

size_t linear_lastsearch(void *array, size_t array_size, size_t data_size,void* target, int (*cmp)(const void*, const void*)){
    size_t result = -1;
    for(size_t i= 0; i < array_size;i++){
        void *current = array + (i*data_size);
        if(cmp(target, current) == 0)
            result = i;
    }
    return result;
}

size_t binary_search(void *array, size_t array_size, size_t data_size, void *target, int (*cmp)(const void*, const void*))
{
    size_t low = 0;
    size_t high = array_size;
    size_t result = -1;
    while (low < high)
    {
        size_t mid = (low + high)/2;
        void * current = array + (mid*data_size);
        if (cmp(target, current) == 0)
        {
            result = mid;
            high = mid;
        }
        else if (cmp(target, current) < 0) {
            high = mid;
        }
        else {
            low = mid + 1;
        }
    }
    return result;
}

size_t binary_lastsearch(void *array, size_t array_size, size_t data_size, void *target, int (*cmp)(const void*, const void*))
{
    size_t low = 0;
    size_t high = array_size;
    size_t result = -1;
    while (low < high)
    {
        size_t mid = (low + high)/2;
        void * current = array + (mid*data_size);
        if (cmp(target, current) == 0)
        {
            result = mid;
            low = mid + 1;
        }
        else if (cmp(target, current) < 0) {
            high = mid;
        }
        else {
            low = mid + 1;
        }
    }
    return result;
}

void swap(void*a, void*b,size_t data_size){
    char* tmp[data_size];
    memcpy(tmp,a,data_size);
    memcpy(a,b,data_size);
    memcpy(b, tmp,data_size);
}

void insertion_sort(void*array , size_t array_size, size_t data_size, int (*cmp)(const void*,const void*)){
    for(size_t i = 1; i < array_size;i++){
        size_t j = i;
        while(j > 0 && cmp(array + ((j-1)*data_size), array + (j*data_size)) > 0){
            swap(array + ((j-1)*data_size),  array + (j*data_size),data_size);
            j--;
        }
    }
}

void merge(void *a, size_t n, void* b, size_t m, void* temp,size_t data_size,int (*cmp)(const void*,const void*)){
    size_t size = 0;
    size_t i = 0;
    size_t j = 0;
    while(i < n && j < m){
        if(cmp((a + (data_size*i)), (b + (data_size*j))) <= 0){
            memcpy(temp+(size*data_size), a+(data_size*i),data_size);
            size++;
            i++;
        }
        else{
            memcpy(temp+(size*data_size), b+(data_size*j),data_size);
            size++;
            j++;
        }
    }
    memmove(temp+(size*data_size), (a+i*data_size), (n-i)*data_size);
    size += (n-i);
    memmove(temp+size*data_size, (b+j*data_size), (m-j)*data_size);
}

void merge_sort_helper(void *array, size_t array_size, size_t data_size, void* temporary, int (*cmp)(const void*,const void*)){
    if(array_size > 1){
        size_t m = array_size / 2;
        merge_sort_helper(array, m, data_size, temporary, cmp);
        merge_sort_helper(array + (m* data_size), array_size- m, data_size, temporary, cmp);
        merge(array, m, array+(m*data_size), array_size-m,temporary, data_size, cmp);
        memcpy(array,temporary,array_size * data_size);
    }
}

void merge_sort(void *array, size_t array_size, size_t data_size, int (*cmp)(const void*,const void*)){
    void *temporary = malloc(data_size*array_size);
    merge_sort_helper(array, array_size, data_size, temporary, cmp);
    free(temporary);
}   


//ARRAY UTILITY

void* array_clone(void*array, size_t array_size, size_t data_size){
    void* result = calloc(array_size,data_size);
    if((result != NULL))     
        memcpy(result, array, array_size*data_size);
    return result;
}

void* array_max(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*)){
    void* max = array;
    for(int i = 0; i < array_size;i++){
        void* current = array + i*data_size;
        if(cmp(max, current) < 0){
            max = current;
        }
    }
    return max;

}

void* array_min(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*)){
    void* min = array;
    for(int i = 0; i < array_size;i++){
        void* current = array + i*data_size;
        if(cmp(min, current) > 0){
            min = current;
        }
    }
    return min;
}

size_t array_argmax(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*)){
    void* max = array;
    size_t argmax = 0;
    for(int i = 0; i < array_size;i++){
        void* current = array + i*data_size;
        if(cmp(max, current) < 0){
            max = current;
            argmax = i;
        }
    }
    return argmax;
}

size_t array_argmin(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*)){
    void* min = array;
    size_t argmin = 0;
    for(int i = 0; i < array_size;i++){
        void* current = array + i*data_size;
        if(cmp(min, current) > 0){
            min = current;
            argmin = i;
        }
    }
    return argmin;
}

bool array_contains(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*), const void* target){
    for(size_t i = 0; i < array_size;i++){
        if(cmp(target, array + i*data_size) == 0)
            return true;
    }
    return false;
}

size_t array_remove(void* array, size_t array_size, size_t data_size, size_t index){
    if(index >= 0 && index < array_size){
        memmove(array + data_size*index, array + data_size*(index+1), ((--(array_size))-index)*data_size);
    }
    return array_size;
}

size_t array_rmdups_unsorted(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*), void* exit_array){
    size_t size = 0;
    for(size_t i = 0; i < array_size;i++){
        if(linear_search(exit_array, size, data_size, array+i*data_size, cmp) == -1){
            memmove(exit_array+size*data_size,array+i*data_size, data_size);
            size++;
        }
    }
    return size;
}

size_t count_while(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*), void* target){
    size_t count = 0;
    while(count < array_size && cmp(array+count*data_size,target) == 0){
        count++;
    }
    return count;
}

size_t array_rmdups_sorted(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*), void* exit_array){
    size_t size = 0;
    size_t j = 0;
    size_t i = 0;
    while(i < array_size){
        j = count_while(array+i*data_size, array_size-i, data_size, cmp, array+i*data_size);
        memmove(exit_array + size*data_size, array+i*data_size, data_size);
        size++;
        i += j;
    }
    return size;
}

size_t array_rmdups(void *array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*), bool sorted){
    return sorted ? array_rmdups_sorted(array, array_size, data_size, cmp,array) : array_rmdups_unsorted(array, array_size, data_size, cmp,array);
}

void* array_rmdups_new(void *array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*), bool sorted, size_t* returnSize){
    *returnSize = 0;
    void* exit_array = calloc(array_size,data_size);
    if(sorted){
        *returnSize = array_rmdups_sorted(array, array_size, data_size, cmp,exit_array);
    }
    else{
        *returnSize = array_rmdups_unsorted(array, array_size, data_size, cmp,exit_array);
    }
    exit_array = realloc(exit_array, (*returnSize)*data_size);
    return exit_array;
}

size_t array_filter(void* array, size_t array_size, size_t data_size, bool(*func)(const void*)){
    size_t result = array_size;
    for(size_t i = 0; i < array_size;i++){
        if(!(func(array + i*data_size))){
            array_remove(array, array_size, data_size, i);
            result--;
        }
    }
    return result;
}

void* array_filter_new(void* array, size_t array_size, size_t data_size, bool(*func)(const void*), size_t* returnSize){
    *returnSize = 0;
    void* result = calloc(array_size, data_size);
    *returnSize = 0;
    if(result == NULL)
        return NULL;
    for(size_t i = 0; i < array_size;i++){
        if((func(array + i*data_size))){
            memcpy(result+(*returnSize)*data_size, array+i*data_size, data_size);
            (*returnSize)++;
        }
    }
    result = realloc(result, (*returnSize)*data_size);
    return result;
}
