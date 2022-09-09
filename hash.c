#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "hash.h"

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


size_t hash_fnc(const char* key, size_t capacity){
    int result = 0;
    for(int i = 0; key[i];i++){
        result += key[i];
        result = (result*key[i]) % capacity;
    }
    return result;
}

Hash_element element_create(void* data,void* key){
    Hash_element result = (Hash_element)malloc(sizeof(struct h_element));
    result->data = data;
    result->key = key;
    result->next = NULL;
    return result;
}

Hash_table hash_table_create(size_t capacity,size_t (*hash_function)(const void*, size_t), int (*key_cmp)(const void*, const void*)){
    if(capacity == 0)
        return NULL;

    Hash_table result = (Hash_table)malloc(sizeof(struct h_table));
    result->table = (Hash_element*)calloc(capacity, sizeof(Hash_element));
    result->capacity = capacity;
    result->stored = 0;
    // if(hash_function == NULL)
    //     result->hash_function = hash_fnc;
    // else
    //     result->hash_function = hash_function;
    result->hash_function = hash_function;
    result->key_cmp = key_cmp;
    return result;
}

void hash_table_destroy(Hash_table map){
    if(map != NULL){
        for(int i = 0; i < map->capacity;i++){
            if(map->table[i]!= NULL)
                free(map->table[i]->data);
            free(map->table[i]);
        }
        free(map->table);
        free(map);
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

void hash_set(Hash_table map, void* data, void * key){
    if(map != NULL && data != NULL && key != NULL){
        Hash_element element = element_create(data, key);
        int index = map->hash_function(element->key,map->capacity);
        element->next = map->table[index];
        map->table[index] = element;
        map->stored++;
    }
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

int hash_store_values(Hash_table map,void **output){
    int result = 0;
    for(int i = 0; i < map->capacity;i++){
        Hash_element head = map->table[i];
        while(head != NULL){
            output[result++] = head->data;
            // memcpy(output + (result*map->data_size), head->data, map->data_size);
            head = head->next;
        }
    }
    assert(result == map->stored);
    return result;
}

int hash_store_keys(Hash_table map,void **output){
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
