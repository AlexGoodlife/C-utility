/**
 * @file tree.c
 * @author Alexandre Boavida (novaisboavida@gmail.com)
 * @brief source code for functions specified in tree.h
 * 
 * @date 2022-09-11
 *  
 */
#include <stdlib.h>
#include "../include/tree.h"

typedef struct bst_t{
    void *data;
    void* key;
    struct bst_t* left;
    struct bst_t* right;
}*BS_node;

typedef struct bs_tree{
    BS_node* root;
    int (*cmp)(const void*, const void*);
}*BS_tree;

BS_node bst_nodecreate(void* data, void *key){
    BS_node result = malloc(sizeof(struct bst_t));
    if(result == NULL)
        return NULL;
    result->data = data;
    result->key = key;
    result->left = NULL;
    result->right = NULL;
    return result;
}

BS_tree bst_create(int (*cmp)(const void*, const void*)){
    BS_tree result = malloc(sizeof(BS_tree));
    if(result == NULL)
        return NULL;
    result->root = malloc(sizeof(BS_node));
    *(result->root) = NULL;
    result->cmp = cmp;
    return result;
}

void bst_destroy_rec(BS_node *root){
    BS_node root_node = *(root);
    if(root_node == NULL)
        return;
    bst_destroy_rec(&(root_node->left));
    bst_destroy_rec(&(root_node->right));
    free(root_node);
}

void bst_destroy(BS_tree tree){
    bst_destroy_rec(tree->root);
    free(tree->root);
    free(tree);
}

bool bst_insert_rec(BS_tree tree,BS_node *root, void*data, void*key){
    BS_node root_node = *root;
    if(root_node == NULL){
        *(root) = bst_nodecreate(data,key);
        if(*(root) == NULL)
            return false;
         return true;
    }
    if(tree->cmp(root_node->key, key) == 0)
        return false;
    if(tree->cmp(key, root_node->key) < 0){
        return bst_insert_rec(tree,&(root_node->left), data, key);
    }
    else
        return bst_insert_rec(tree,&(root_node->right), data, key);
}

bool bst_insert(BS_tree tree, void* data, void* key){
    return bst_insert_rec(tree, tree->root, data, key);
}

void* bst_lookup_rec(BS_tree tree, BS_node *root, void*key){
    BS_node root_node = *(root);
    if(root_node == NULL)
        return NULL;
    if(tree->cmp(root_node->key, key) == 0){
        return root_node->data;
    }
    if(tree->cmp(key, root_node->key) < 0)
        return bst_lookup_rec(tree,&(root_node->left),key);
    else
        return bst_lookup_rec(tree,&(root_node->right),key);
}

void *bst_lookup(BS_tree tree, void *key){
    return bst_lookup_rec(tree, tree->root, key);
}

void *bst_min_rec(BS_tree tree, BS_node* root){
    BS_node root_node = *(root);
    if(root_node == NULL){
        return NULL;
    }
    else if(root_node->left == NULL)
        return root_node->data;
    else
        return bst_min_rec(tree, &(root_node->left));
}

void *bst_min(BS_tree tree){
    return bst_min_rec(tree, tree->root);
}

void *bst_max_rec(BS_tree tree, BS_node* root){
    BS_node root_node = *(root);
    if(root_node == NULL){
        return NULL;
    }
    else if(root_node->left == NULL)
        return root_node->data;
    else
        return bst_max_rec(tree, &(root_node->right));
}

void *bst_max(BS_tree tree){
    return bst_max_rec(tree, tree->root);
}
