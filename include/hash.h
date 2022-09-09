#ifndef HASH_SIMPLE_H
#define HASH_SIMPLE_H

typedef struct h_element *Hash_element;

typedef struct h_table *Hash_table;

Hash_table hash_table_create(size_t capacity,size_t (*hash_function)(const void*, size_t),int (*key_cmp)(const void*, const void*));

void hash_table_destroy(Hash_table map);

void hash_print(Hash_table map);

void hash_set(Hash_table map, void* data, void* key);

void *hash_lookup(Hash_table map, void *key);

void* hash_delete(Hash_table map, void* key);

int hash_store_values(Hash_table map,void **output);

int hash_store_keys(Hash_table map, void **output);

#endif