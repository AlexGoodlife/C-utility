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

size_t binary_search(void *array, size_t array_size, size_t data_size, void *target, int (*cmp)(const void*, const void*))
{
    size_t low = 0;
    size_t high = array_size - 1;
    size_t result = -1;
    while (low <= high)
    {
        size_t mid = (low + high)/2;
        void * current = array + (mid*data_size);
        if (cmp(target, current) == 0)
        {
            result = mid;
            high = mid - 1;
        }
        else if (cmp(target, current) < 0) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return result;
}

void swap(void *x , void *y, size_t data_size){
    void *temp = malloc(data_size);
    temp = memcpy(temp,x,data_size);
    x = memcpy(x,y,data_size);
    y = memcpy(y,temp, data_size);
    free(temp);
}

void insertion_sort(void*array , size_t array_size, size_t data_size, int (*cmp)(const void*,const void*)){
    for(size_t i = 1; i < array_size;i++){
        size_t j = i;
        while(j > 0 && cmp(array + ((j-1)*data_size), array + (j*data_size)) > 0){
            swap(array + ((j-1)*data_size),  array + (j*data_size), data_size);
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
