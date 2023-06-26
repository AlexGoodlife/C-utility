#ifndef _CUTIL_DECL_H_
#define _CUTIL_DECL_H_

#include <stddef.h> // size_t

// I don't know why anyone would use this lib in C++
#ifdef __cplusplus 
extern "C"{
#endif 


#ifndef CUTILDEF
#ifdef CUTIL_STATIC
#define CUTILDEF static
#else
#define CUTILDEF extern
#endif
#endif // CUTILDEF
 
typedef unsigned char cutil_uint8;

// VECTOR API

typedef struct{
  size_t length;
  size_t capacity;
}_cutil_vector_s;

CUTILDEF void* _cutil_vector_init(size_t data_size);

CUTILDEF void _cutil_vector_free(void** v);

CUTILDEF void _cutil_vector_resize(void** v, size_t data_size);

CUTILDEF void _cutil_vector_clear_memory(void** v, size_t data_size);

#define CUTIL_VECTOR(_T) _T*

#define CUTIL_VECTOR_INIT(_T) (_T*)_cutil_vector_init(sizeof(_T))

#define _CUTIL_GET_HEADER(vec_ptr, header_t) (header_t*)((((cutil_uint8*)(vec_ptr))-sizeof(header_t)))

#define _CUTIL_VECTOR_GET_HEADER(vec_ptr) _CUTIL_GET_HEADER(vec_ptr, _cutil_vector_s)

// #define _CUTIL_VECTOR_GET_HEADER(vec_ptr) (_cutil_vector_s*)((((cutil_uint8*)(vec_ptr))-sizeof(_cutil_vector_s)))

#define CUTIL_VECTOR_SIZE(vec_ptr) (_CUTIL_VECTOR_GET_HEADER(vec_ptr))->length

#define CUTIL_VECTOR_PUSH(vec_ptr, element) do{vec_ptr[CUTIL_VECTOR_SIZE(vec_ptr)++] = (element); _cutil_vector_resize((void**)&vec_ptr, sizeof(*(vec_ptr)));}while(0) //NOLINT

#define CUTIL_VECTOR_POP(vec_ptr) vec_ptr[CUTIL_VECTOR_SIZE(vec_ptr)-- - 1]

#define CUTIL_VECTOR_PEEK(vec_ptr) vec_ptr[CUTIL_VECTOR_SIZE(vec_ptr) - 1]

#define CUTIL_VECTOR_FREE(vec_ptr) _cutil_vector_free((void**)&vec_ptr)

#define CUTIL_VECTOR_CLEAR(vec_ptr) do{_cutil_vector_s* header = _CUTIL_VECTOR_GET_HEADER(vec_ptr); header->length = 0;}while(0);

#define CUTIL_VECTOR_CLEAR_MEMORY(vec_ptr) _cutil_vector_clear_memory((void**)&(vec_ptr), sizeof((*vec_ptr)))

// QUEUE API

typedef struct{
  size_t size, capacity, head;
}_cutil_queue_s;

CUTILDEF void* _cutil_queue_init(size_t data_size);
CUTILDEF void  _cutil_queue_resize(void**v, size_t data_size);
CUTILDEF size_t _cutil_queue_dequeue(void*v);
CUTILDEF void _cutil_queue_free(void** v);

#define _CUTIL_QUEUE_GET_HEADER(ptr) _CUTIL_GET_HEADER(ptr, _cutil_queue_s)

#define CUTIL_QUEUE(_T) CUTIL_VECTOR(_T)

#define CUTIL_QUEUE_INIT(_T) (_T*)_cutil_queue_init(sizeof(_T))

#define CUTIL_QUEUE_FREE(ptr) _cutil_queue_free((void**)&ptr)

#define CUTIL_QUEUE_SIZE(ptr) (_CUTIL_QUEUE_GET_HEADER(ptr))->size

#define CUTIL_QUEUE_HEAD(ptr) (_CUTIL_QUEUE_GET_HEADER(ptr))->head
#define CUTIL_QUEUE_CAPACITY(ptr) (_CUTIL_QUEUE_GET_HEADER(ptr))->capacity
#define CUTIL_QUEUE_ENQUEUE(ptr, element) do{\
 _cutil_queue_s* header = _CUTIL_QUEUE_GET_HEADER(ptr); \
  size_t index = (header->head + header->size++) % header->capacity;\
  ptr[index] = (element);\
  if(header->size == header->capacity){ _cutil_queue_resize((void**)&ptr, sizeof((*ptr)));}\
}while(0)/*NOLINT*/\

#define CUTIL_QUEUE_DEQUEUE(ptr) ptr[_cutil_queue_dequeue((void*)ptr)]

#define CUTIL_QUEUE_PEEK(ptr) ptr[(_CUTIL_QUEUE_GET_HEADER(ptr))->head]

// ARRAY FUNCTIONS

CUTILDEF size_t cutil_linear_search(void *array, size_t array_size, size_t data_size,void* target, int (*cmp)(const void*, const void*));

CUTILDEF size_t cutil_linear_lastsearch(void *array, size_t array_size, size_t data_size,void* target, int (*cmp)(const void*, const void*));

CUTILDEF size_t cutil_binary_search(void *array, size_t array_size, size_t data_size, void *target, int (*cmp)(const void*, const void*));

CUTILDEF size_t cutil_binary_lastsearch(void *array, size_t array_size, size_t data_size, void *target, int (*cmp)(const void*, const void*));

CUTILDEF void*  cutil_array_clone(void*array, size_t array_size, size_t data_size);

CUTILDEF void*  cutil_array_max(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*));

CUTILDEF void*  cutil_array_min(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*));

CUTILDEF size_t cutil_array_argmax(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*));

CUTILDEF size_t cutil_array_argmin(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*));

CUTILDEF int    cutil_array_contains(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*), const void* target);

CUTILDEF size_t cutil_array_remove(void* array, size_t array_size, size_t data_size, size_t index);

CUTILDEF void*  cutil_array_filter(void* array, size_t array_size, size_t data_size, int(*func)(const void*), size_t* returnSize);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _CUTIL_DECL_H_
 
#ifdef CUTIL_IMPLEMENTATION

#ifndef CUTIL_NO_STDLIB
#include <stdlib.h> // malloc, realloc, free
#endif // CUTIL_NO_STDLIB

#ifndef CUTIL_NO_STRING
#include <string.h> // memcpy
#endif // CUTIL_NO_STRING 

#ifndef _MSC_VER
  #define CUTIL_INLINE inline
#else
  #define CUTIL_INLINE __forceinline
#endif // _MSC_VER


#if defined(CUTIL_REALLOC) && defined(CUTIL_FREE) && defined(CUTIL_MALLOC)
  // No problem
#elif !defined(CUTIL_REALLOC) && !defined(CUTIL_FREE) && !defined(CUTIL_MALLOC) 
  // No problem
#else
#error "If you wish to disable stdlib functions define CUTIL_NO_STDLIB and define implementations for malloc, free and realloc in the CUTIL_REALLOC, CUTIL_MALLOC and CUTIL_FREE macros"
#endif

#if !defined(CUTIL_MEMCPY) && !defined(CUTIL_MEMMMOVE)
  // No problem
#elif defined(CUTIL_MEMCPY) && defined(CUTIL_MEMMOVE)
  // No problem
#else
#error "If you with to disable string.h define CUTIL_NO_STRING and define implementation for memcpy under CUTIL_MEMCPY macro"
#endif

#ifdef CUTIL_DEBUG
#include <stdio.h>
#include <assert.h>
#define CUTIL_LOG(message,...) do{printf("[CUTIL_LOG] @%s, line- %d: ", __FILE__, __LINE__);printf(message, ##__VA_ARGS__);fflush(stdin);}while(0)
#define CUTIL_ASSERT(expr) assert(expr)
#else 
#define CUTIL_LOG(message,...)  
#define CUTIL_ASSERT(expr)
#endif // DEBUG

// If you wish to not use malloc or realloc or free you can define them yourself 
#ifndef CUTIL_MALLOC
#define CUTIL_MALLOC(size) malloc(size)
#endif //CUTIL_MALLOC

#ifndef CUTIL_REALLOC
#define CUTIL_REALLOC(ptr, size) realloc(ptr, size)
#endif //CUTIL_REALLOC

#ifndef CUTIL_FREE
#define CUTIL_FREE(pointer) free(pointer)
#endif // CUTIL_FREE

#ifndef CUTIL_MEMCPY
#define CUTIL_MEMCPY(dest, src, size) memcpy(dest, src, size)
#endif 

#ifndef CUTIL_MEMMOVE
#define CUTIL_MEMMOVE(dest,src,size) memmove(dest,src,size)
#endif

// VECTOR STRUCTS AND DEFINITIONS

#define _CUTIL_DEFAULT_VECTOR_SIZE 8

CUTILDEF void* _cutil_vector_init(size_t data_size){
  cutil_uint8* buffer = (cutil_uint8*)CUTIL_MALLOC(sizeof(_cutil_vector_s) + _CUTIL_DEFAULT_VECTOR_SIZE * data_size);
  if(!buffer){CUTIL_LOG("Malloc failed at init\n"); return NULL;}
  _cutil_vector_s* header = (_cutil_vector_s*)buffer;
  
  header->length = 0;
  header->capacity = _CUTIL_DEFAULT_VECTOR_SIZE;
  return (void*)(buffer + sizeof(_cutil_vector_s));
}

CUTILDEF void _cutil_vector_free(void** v){
  if(!(*v)) return;
  void* to_free=(void*) _CUTIL_VECTOR_GET_HEADER(*v);
  CUTIL_FREE(to_free);
  *v = NULL;
}

CUTILDEF void _cutil_vector_resize(void** v,size_t data_size){
  if(!(*v)) return;
  _cutil_vector_s* header = _CUTIL_VECTOR_GET_HEADER(*v);
  if(header->length >= header->capacity){
    size_t new_capacity = header->capacity*2;
    header->capacity = new_capacity;
    *v = CUTIL_REALLOC((cutil_uint8*)header, sizeof(_cutil_vector_s) + new_capacity*data_size);
    *v = (cutil_uint8*)(*v) + sizeof(_cutil_vector_s);
  }
}

CUTILDEF void _cutil_vector_clear_memory(void** v, size_t data_size){
  if(!(*v)) return;
  void* to_free = *v;
  *v = _cutil_vector_init(data_size);
  _cutil_vector_free(&to_free);
}

// QUEUE API IMPLEMENTATION

#define _CUTIL_DEFAULT_QUEUE_SIZE _CUTIL_DEFAULT_VECTOR_SIZE
#define _CUTIL_QUEUE

CUTILDEF void* _cutil_queue_init(size_t data_size){
  cutil_uint8* buffer = (cutil_uint8*)CUTIL_MALLOC(sizeof(_cutil_queue_s) + _CUTIL_DEFAULT_QUEUE_SIZE*data_size);
  if(!buffer){CUTIL_LOG("Malloc failed at init\n"); return NULL;}
  _cutil_queue_s* header = (_cutil_queue_s*)buffer;

  header->capacity = _CUTIL_DEFAULT_QUEUE_SIZE; 
  header->head = 0;
  header->size = 0;
  return (void*)(buffer + sizeof(_cutil_queue_s));
}

CUTILDEF void _cutil_queue_free(void** v){
  if(!(*v)) return;
  void* to_free=(void*) _CUTIL_QUEUE_GET_HEADER(*v);
  CUTIL_FREE(to_free);
  *v = NULL;
}

CUTILDEF size_t _cutil_queue_dequeue(void*v){
  _cutil_queue_s* header = _CUTIL_QUEUE_GET_HEADER(v);
  header->size--;
  size_t result = header->head;
  header->head = (header->head + 1) % header->capacity;
  return result;
}


CUTILDEF void  _cutil_queue_resize(void**v, size_t data_size){
  CUTIL_LOG("QUEUE RESIZE\n");
  if(!(*v)) return;
  _cutil_queue_s* header = _CUTIL_QUEUE_GET_HEADER(*v);
  size_t new_capacity = header->capacity*2;
  cutil_uint8* new_buffer = (cutil_uint8*)CUTIL_MALLOC(sizeof(_cutil_queue_s) + new_capacity* data_size);
  if(!new_buffer){CUTIL_LOG("MALLOC FAILED AT RESIZE\n"); return;}
  cutil_uint8* queue_buffer = new_buffer + sizeof(_cutil_queue_s);
   
  // resize like this to reorder circular queue
  size_t j = 0;
  cutil_uint8* old_buffer = (cutil_uint8*)(*v);

  for(size_t i = header->head; j < header->size;i++){
    CUTIL_MEMCPY(queue_buffer + j++ * data_size, old_buffer + (i % header->capacity) * data_size, data_size); 

  }
  _cutil_queue_s* new_header =(_cutil_queue_s*) new_buffer;
  new_header->head = 0;
  new_header->size = header->size;
  new_header->capacity = new_capacity;
  

  _cutil_queue_free(v);
  *v = queue_buffer;
}

CUTILDEF size_t linear_search(void *array, size_t array_size, size_t data_size,void* target, int (*cmp)(const void*, const void*)){
    for(size_t i= 0; i < array_size;i++){
        void *current = (cutil_uint8*)array + (i*data_size);
        if(cmp(target, current) == 0)
            return i;
    }
    return -1;
}

CUTILDEF size_t linear_lastsearch(void *array, size_t array_size, size_t data_size,void* target, int (*cmp)(const void*, const void*)){
    size_t result = -1;
    for(size_t i= 0; i < array_size;i++){
        void *current = (cutil_uint8*)array + (i*data_size);
        if(cmp(target, current) == 0)
            result = i;
    }
    return result;
}

CUTILDEF size_t binary_search(void *array, size_t array_size, size_t data_size, void *target, int (*cmp)(const void*, const void*))
{
    size_t low = 0;
    size_t high = array_size;
    size_t result = -1;
    while (low < high)
    {
        size_t mid = (low + high)/2;
        void * current = (cutil_uint8*)array + (mid*data_size);
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

CUTILDEF size_t binary_lastsearch(void *array, size_t array_size, size_t data_size, void *target, int (*cmp)(const void*, const void*))
{
    size_t low = 0;
    size_t high = array_size;
    size_t result = -1;
    while (low < high)
    {
        size_t mid = (low + high)/2;
        void * current = (cutil_uint8*)array + (mid*data_size);
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

//ARRAY UTILITY

CUTILDEF void* cutil_array_clone(void*array, size_t array_size, size_t data_size){
    void* result = CUTIL_MALLOC(array_size*data_size);
    if((result != NULL))     
        CUTIL_MEMCPY(result, array, array_size*data_size);
    return result;
}

CUTILDEF void* cutil_array_max(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*)){
    void* max = array;
    for(size_t i = 0; i < array_size;i++){
        void* current = (cutil_uint8*)array + i*data_size;
        if(cmp(max, current) < 0){
            max = current;
        }
    }
    return max;

}

CUTILDEF void* cutil_array_min(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*)){
    void* min = array;
    for(size_t i = 0; i < array_size;i++){
        void* current = (cutil_uint8*)array + i*data_size;
        if(cmp(min, current) > 0){
            min = current;
        }
    }
    return min;
}

CUTILDEF size_t cutil_array_argmax(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*)){
    void* max = array;
    size_t argmax = 0;
    for(size_t i = 0; i < array_size;i++){
        void* current = (cutil_uint8*)array + i*data_size;
        if(cmp(max, current) < 0){
            max = current;
            argmax = i;
        }
    }
    return argmax;
}

CUTILDEF size_t cutil_array_argmin(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*)){
    void* min = array;
    size_t argmin = 0;
    for(size_t i = 0; i < array_size;i++){
        void* current = (cutil_uint8*)array + i*data_size;
        if(cmp(min, current) > 0){
            min = current;
            argmin = i;
        }
    }
    return argmin;
}

CUTILDEF int cutil_array_contains(void*array, size_t array_size, size_t data_size, int(*cmp)(const void*, const void*), const void* target){
    for(size_t i = 0; i < array_size;i++){
        if(cmp(target, (cutil_uint8*)array + i*data_size) == 0)
            return 1;
    }
    return 0;
}

CUTILDEF size_t cutil_array_remove(void* array, size_t array_size, size_t data_size, size_t index){
    if(index >= 0 && index < array_size){
        CUTIL_MEMMOVE((cutil_uint8*)array + data_size*index, (cutil_uint8*)array + data_size*(index+1), ((--(array_size))-index)*data_size);
    }
    return array_size;
}

CUTILDEF void* cutil_array_filter(void* array, size_t array_size, size_t data_size, int(*func)(const void*), size_t* returnSize){
    *returnSize = 0;
    void* result = CUTIL_MALLOC(data_size * array_size);
    *returnSize = 0;
    if(result == NULL)
        return NULL;
    for(size_t i = 0; i < array_size;i++){
        if((func((cutil_uint8*)array + i*data_size))){
            CUTIL_MEMCPY((cutil_uint8*)result+(*returnSize)*data_size, (cutil_uint8*)array+i*data_size, data_size);
            (*returnSize)++;
        }
    }
    result = CUTIL_REALLOC(result, (*returnSize)*data_size);
    return result;
}
#endif // CUTIL_IMPLEMENTATION
