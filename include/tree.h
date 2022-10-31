/**
 * @file tree.h
 * @author Alexandre Boavida (novaisboavida@gmail.com)
 * @brief function protoypes and structs refering to tree data structures
 * @date 2022-09-11
 * 
 */
#ifndef TREE_SIMPLE_H
#define TREE_SIMPLE_H

#include <stdbool.h>

/**
 * @brief Binary search tree struct, can hold any data <-> key pairs
 * 
 */
typedef struct bs_tree *BS_tree;

/**
 * @brief Allocated a binary search tree dynamically from a comparison function for the keys provided, type safety is up to the user
 * 
 * @param cmp Comparison function to be provided, is made in the style of qsort(LibC) cmp functions
 * @return BS_tree created or NULL if failed
 */
BS_tree bst_create(int (*cmp)(const void*, const void*));

/**
 * @brief Frees memory allocated by binary search tree
 * 
 * @param tree tree to destroy passed by reference
 */
void bst_destroy(BS_tree *tree);

/**
 * @brief Inserts data into tree specified by key provided, key must be of same type as intended in comparison function
 * 
 * @param tree The tree which data will be insert
 * @param data The data to insert
 * @param key Key associated with data to insert
 * @return true if successful
 * @return false if unsuccessful (memory issues)
 */
bool bst_insert(BS_tree tree, void* data, void* key);

/**
 * @brief returns data inside binary search tree pertaining to a certain key
 * 
 * @param tree tree to search in 
 * @param key key corresponding to data pair
 * @return returns the data specified
 */
void *bst_lookup(BS_tree tree, void *key);

/**
 * @brief Searches binary search tree for the value associated to its minimum key
 * 
 * @param tree The tree to search for the value
 * @return The minimum value associated to a key in the tree
 */
void *bst_min(BS_tree tree);

/**
 * @brief Searches binary search tree for the value associated to its maximum key
 * 
 * @param tree The tree to search for the value
 * @return The maximum value associated to a key in the tree 
 */
void *bst_max(BS_tree tree);

/**
 * @brief Deletes element in binary search tree pointed to by key
 * 
 * @param tree to delete element in
 * @param key key of element to delete
 * @return void* to data deleted
 */
void* bst_delete(BS_tree tree, void* key);

/**
 * @brief DEBUG FUNCTION DO NOT USE
 * 
 * @param tree 
 */
void print_tree(BS_tree tree);

#endif