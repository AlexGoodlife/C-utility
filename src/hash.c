/**
 * @file hash.c
 * @author Alexandre Boavida (novaisboavida@gmail.com)
 * @brief source for functions and structs defined in hash.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/hash.h"

typedef struct h_element{
    void *data;
    void *key;
    struct h_element* next;
}*Hash_element;

typedef struct h_table{
    Hash_element* table;
    size_t capacity;
    size_t (*hash_function)(const void*, size_t);
    int (*key_cmp)(const void*, const void*);
    size_t stored;
}*Hash_table;

Hash_element element_create(void* data,void* key){
    Hash_element result = (Hash_element)malloc(sizeof(struct h_element));
    if(result == NULL)
        return NULL;
    result->data = data;
    result->key = key;
    result->next = NULL;
    return result;
}

Hash_table hash_table_create(size_t capacity,size_t (*hash_function)(const void*, size_t), int (*key_cmp)(const void*, const void*)){
    if(capacity == 0)
        return NULL;
    Hash_table result = (Hash_table)malloc(sizeof(struct h_table));
    if(result == NULL)
        return NULL;
    result->table = (Hash_element*)calloc(capacity, sizeof(Hash_element));
    if(result->table == NULL)
        return NULL;
    result->capacity = capacity;
    result->stored = 0;
    result->hash_function = hash_function;
    result->key_cmp = key_cmp;
    return result;
}

void hash_table_destroy(Hash_table *map){
    if(*map != NULL){
        for(int i = 0; i < (*map)->capacity;i++){
            if((*map)->table[i]!= NULL){
                free((*map)->table[i]);
                (*map)->table[i] = NULL;
            }
        }
        free((*map)->table);
        (*map)->table = NULL;
        free((*map));
        *map = NULL;
    }
}

void hash_print(Hash_table map){
    if(map != NULL){
        for(int i = 0; i < map->capacity;i++){
            Hash_element head = map->table[i];
            while(head != NULL){
                printf("%p : %p => ", map->table[i], map->table[i]->data);
                head = head->next;
            }
        printf("NULL\n");
        }
    }
}

size_t hash_getSize(Hash_table map){
    return map->stored;
}

bool hash_set(Hash_table map, void* data, void * key){
    if(map != NULL && data != NULL && key != NULL){
        Hash_element element = element_create(data, key);
        if(element == NULL)
            return false;
        int index = map->hash_function(element->key,map->capacity);
        element->next = map->table[index];
        map->table[index] = element;
        map->stored++;
    }
    return true;
}

void *hash_lookup(Hash_table map, void *key){
    void *result = NULL;
    int index = map->hash_function(key, map->capacity);
    Hash_element head = map->table[index];
    while(head != NULL && map->key_cmp(key,head->key) != 0){
        head = head->next;
    }
    if(head != NULL && map->key_cmp(head->key, key) == 0)
        result = head->data;
    return result;
}

bool hash_contains(Hash_table map, void *key){
    return hash_lookup(map, key) != NULL;
}

void* hash_delete(Hash_table map, void* key){
    void *result = NULL;
    int index = map->hash_function(key, map->capacity);
    Hash_element head = map->table[index];
    Hash_element prev = NULL;
    while(head != NULL && map->key_cmp(key,head->key) != 0){
        prev = head;
        head = head->next;
    }
    if(head != NULL){
        if(prev == NULL)
            map->table[index] = head->next;
        else
            prev->next = head->next;
        result = head->data;
        free(head);
        map->stored--;
    }
    return result;
}

size_t hash_extract_values(Hash_table map,void **output){
    int result = 0;
    for(int i = 0; i < map->capacity;i++){
        Hash_element head = map->table[i];
        while(head != NULL){
            output[result++] = head->data;
            head = head->next;
        }
    }
    assert(result == map->stored);
    return result;
}

size_t hash_extract_keys(Hash_table map,void **output){
    int result = 0;
    for(int i = 0; i < map->capacity;i++){
        Hash_element head = map->table[i];
        while(head != NULL){
            output[result++] = (head->key);
            head = head->next;
        }
    }
    assert(result == map->stored);
    return result;
}

void hash_foreach(Hash_table map, void (*func)(void*)){
    for(int i = 0; i < map->capacity;i++){
        Hash_element head = map->table[i];
        while(head != NULL){
            func(head->data);
            head = head->next;
        }
    }
}