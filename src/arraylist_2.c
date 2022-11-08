/**
 * @file arraylist.c
 * @author Alexandre Boavida (novaisboavida@gmail.com)
 * @brief Source code for arraylist.h
 * @date 2022-09-24
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../include/arraylist.h"
#include "../include/algorithm.h"

typedef struct arraylist_t{
    void** array;
    size_t length;
    size_t capacity;
    size_t data_size;
    int (*cmp)(const void*, const void*);
    bool sorted;
}*ArrayList;

ArrayList arraylist_create(size_t data_size, int (*cmp)(const void*,const void*)){
    ArrayList result = malloc(sizeof(struct arraylist_t));
    if(result == NULL)
        return NULL;
    result->capacity = 5;
    result->data_size = data_size;
    result->length = 0;
    result->sorted = false;
    result->cmp= cmp;
    result->array = calloc(result->capacity, sizeof(void*));
    if(result->array == NULL)
        return NULL;
    return result;
}

void arraylist_destroy(ArrayList* a){
    free((*a)->array);
    (*a)->array = NULL;
    free(*a);
    *a = NULL;
}

bool arraylist_resize(ArrayList a, size_t newCapacity){
    bool success = true;
    a->capacity = newCapacity;
    a->array = realloc(a->array,a->capacity*sizeof(void*));
    if(a->array == NULL)
        success = false;
    return success;
}

size_t arraylist_getLength(ArrayList a){
    return a->length;
}

void arraylist_setcmp(ArrayList a, int (*cmp)(const void*, const void*)){
    if(cmp != NULL)
        a->cmp = cmp;
}

bool arraylist_add(ArrayList a, void* data){
    bool success = false;
    if(data != NULL){
        success = true;
        if(a->length == a->capacity){
            success = arraylist_resize(a, a->capacity*2);
        }
        a->array[a->length++] = data;
    }
    return success;
}

bool arraylist_addArray(ArrayList a, void* array, size_t array_size){
    bool success = false;
    size_t old_length = a->length;
    a->length += array_size;
    if(a->length > a->capacity){
        a->capacity = a->length + a->length/2;
        a->array = realloc(a->array, a->capacity*a->data_size);
    }
    if(a->array != NULL){
        size_t count = 0;
        for(size_t i = old_length-1; i < a->length;i++){
            a->array[i]  = array + (count*a->data_size);
        }
        success = true;
    }
    return success;
}

void arraylist_clear(ArrayList a){
    free(a->array);
    a->capacity = 5;
    a->array = calloc(a->capacity, sizeof(void*));
    a->length = 0;
}

ArrayList arraylist_clone(ArrayList a){
    ArrayList result = malloc(sizeof(struct arraylist_t));
    if(result == NULL)
        return NULL;
    result->capacity = a->capacity;
    result->data_size = a->data_size;
    result->length = a->length;
    result->sorted = a->sorted;
    result->cmp= a->cmp;
    if(a->array != NULL){
        result->array = calloc(a->capacity,sizeof(void*));
        if(result->array != NULL){
            memcpy(result->array, a->array, sizeof(void*) * a->capacity);
        }
    }
    if(result->array == NULL)
        return NULL;
    return result;
}

bool arraylist_contains(ArrayList a, void* target){
    for(size_t i = 0 ; i < a->length;i++){
        if(a->cmp(a->array[i], target) == 0){
            return true;
        }
    }
    return false;
}

void* arraylist_get(ArrayList a, size_t index){
    void* result = NULL;
    if(index < a->length)
        result = a->array[index];
    return result;
}

size_t arraylist_find(ArrayList a, void* target){
    if(a->sorted)
        return binary_search(*a->array, a->length, a->data_size, target, a->cmp);
    else
        return linear_search(*a->array, a->length, a->data_size, target, a->cmp);
}

void arraylist_sort(ArrayList a){
    merge_sort(a->array, a->length, sizeof(void*), a->cmp);
    a->sorted = true;
}

void arraylist_removeIndex(ArrayList a, size_t index){
    if(index >= 0 && index < a->length){
        memmove(a->array + sizeof(void*)*index, a->array + sizeof(void*)*(index+1), ((--(a->length))-index)*sizeof(void*));
        if(a->length < a->capacity/4)
            arraylist_resize(a, a->capacity/2);
    }
}

bool arraylist_isEmpty(ArrayList a){
    return a->length == 0;
}

bool arraylist_set(ArrayList a, size_t index, void* data){
    bool success = false;
    if(index < a->length && index >= 0 && data != NULL){
        // memcpy(a->array[index],data,sizeof(int));
        // printf("CHANGE: %d\n", *(int*)(*a->array + a->data_size * index));
        memcpy(a->array[index], data, sizeof(void*));
        // a->array[index] = data;
        // printf("AFTER CHANGE: %d\n", *(int*)(*a->array + a->data_size * index));
        
        success = true;
    }
    return success;
}

void* arraylist_toArray(ArrayList a){
    // printf("BY THE INDEX\n");
    // for(int i = 0; i < a->length;i++){
    //     printf("%d\n", *(int*)a->array[i]);
    // }
    // void* p= *a->array;
    // printf("BY THE SUM\n");
    // for(int i = 0; i < a->length;i++){
    //     printf("%d\n", *(int*)(p + a->data_size*i));
    // }
    void* result = calloc(a->length, a->data_size);
    // for(int i = 0; i < a->length;i++){
    //     memcpy(result + i*a->data_size, a->array[i],a->data_size); 
    // }
    // void** result = calloc(a->length, sizeof(void*));
    // for(int i = 0; i < a->length;i++){
    //     result[i] = a->array[i];
    // }
    // memmove(result, a->array, a->length*sizeof(void*));
    if(result != NULL)
        memmove(result, *(a->array), a->data_size*a->length);
    return result;
}

void* arraylist_getArrayRef(ArrayList a){
    return *(a->array);
}

bool arraylist_reserve(ArrayList a, size_t capacity){
    bool success = false;
    if(capacity > a->length){
        a->capacity = capacity;
        a->array = realloc(a->array, a->capacity*sizeof(void*));
        if(a->array != NULL)
            success = true;
    }
    return success;
}

size_t arraylist_findLast(ArrayList a, void* target){
    size_t result = -1;
    if(target != NULL){
        if(a->sorted)
            result = binary_lastsearch(*a->array, a->length, a->data_size, target,a->cmp);
        else
            result = linear_lastsearch(*a->array, a->length, a->data_size, target,a->cmp);
    }
    return result;
}

void arraylist_foreach(ArrayList a, void (*func)(void*)){
    for(size_t i = 0; i < a->length;i++){
        func(a->array[i]);
    }
}

size_t arraylist_filter(ArrayList a, bool(*func)(const void*)){
    void* temp;
    temp = array_filter_new(a->array, a->length, sizeof(void*), func,&(a->length));
    free(a->array);
    a->array = temp;
    if(a->length < a->capacity/4)
        arraylist_resize(a, a->capacity/2);
    return a->length;
}

size_t arraylist_rmdups(ArrayList a){
    void* temp;
    temp = array_rmdups_new(a->array, a->length, sizeof(void*), a->cmp, a->sorted, &(a->length));
    free(a->array);
    a->array = temp;
    if(a->length < a->capacity/4)
        arraylist_resize(a, a->capacity/2);
    return a->length;
}

void* arraylist_max(ArrayList a){
    return array_max(a->array, a->length, sizeof(void*), a->cmp);
}

void* arraylist_min(ArrayList a){
    return array_min(a->array, a->length, sizeof(void*), a->cmp);
}

size_t arraylist_argmax(ArrayList a){
    return array_argmax(a->array, a->length, sizeof(void*), a->cmp);
}

size_t arraylist_argmin(ArrayList a){
    return array_argmin(a->array, a->length, sizeof(void*), a->cmp);
}

size_t arraylist_shrinkToSize(ArrayList a){
    a->capacity = a->length;
    a->array = realloc(a->array, a->capacity);
    return a->length;
}

void arraylist_swap(ArrayList a, size_t i, size_t j){
    if(i < a->length && i >= 0 && j < a->length && j >= 0 && j != i){
        swap(a->array + i*sizeof(void*), a->array + j*sizeof(void*), sizeof(void*));
    }
}

typedef struct arraylist_it{
    ArrayList list;
    size_t nextIndex;
    void* nextItem;
}*ArrayList_iterator;

ArrayList_iterator arraylist_it_create(ArrayList arraylist){
    ArrayList_iterator result = malloc(sizeof(struct arraylist_it));
    if(result == NULL)
        return NULL;
    result->list = arraylist;
    result->nextIndex = 0;
    result->nextItem = arraylist->array[0];
    return result;
}

void arraylist_it_destroy(ArrayList_iterator* it){
    free(*it);
    *it = NULL;
}

void* arraylist_Next(ArrayList_iterator it){
    void* result = it->nextItem;
    it->nextIndex++;
    it->nextItem = it->nextIndex == it->list->length ? NULL : it->list->array[it->nextIndex];
    return result;
}

bool arraylist_hasNext(ArrayList_iterator it){
    return it->nextItem != NULL && it->nextIndex < it->list->length;
}

void* arraylist_iterate(ArrayList_iterator it){
    void* result = NULL;
    if(arraylist_hasNext(it)){
        result = arraylist_Next(it);
    }
    return result;
}

void arraylist_it_reset(ArrayList_iterator it){
    it->nextIndex = 0;
    it->nextItem = it->list->array;
}