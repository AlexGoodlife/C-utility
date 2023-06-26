
#ifndef _CUTIL_HASH_DECL_H
#define _CUTIL_HASH_DECL_H

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

typedef struct cutil_hash_el{
  void* key;
  void* value;
  struct cutil_hash_el* next;
}cutil_hash_el;

typedef struct cutil_hash_name {
  size_t capacity;
  size_t n_buckets;
  size_t key_size;
  size_t value_size;
  int (*cmp)(const void*,const void*);
  cutil_hash_el** data;
}cutil_hash_s;

CUTILDEF cutil_hash_s* cutil_hash_init(size_t key_size, size_t value_size, int (*keycmp)(const void*, const void*));

CUTILDEF void cutil_hash_free(cutil_hash_s** map );

CUTILDEF void* cutil_hash_get(cutil_hash_s* map, void* key);

CUTILDEF int cutil_hash_contains(cutil_hash_s* map, void* key);

CUTILDEF int cutil_hash_put(cutil_hash_s* map, void* key, void* value);

CUTILDEF void cutil_hash_remove(cutil_hash_s* map, void* key);

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
#ifndef CUTIL_LOG
#define CUTIL_LOG(message,...) do{printf("[CUTIL_LOG] @%s, line- %d: ", __FILE__, __LINE__);printf(message, ##__VA_ARGS__);fflush(stdin);}while(0)
#endif
#ifndef CUTIL_ASSERT
#define CUTIL_ASSERT(expr) assert(expr)
#endif
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

#define _CUTIL_HASH_DEF_SIZE 31 // Good old 31

// FOLLOWING NEXT PRIME IMPLEMENTATION SHAMELESSLY STOLEN FROM "https://stackoverflow.com/questions/4475996/given-prime-number-n-compute-the-next-prime"
static const size_t _cutil_small_primes[] =
{
    2,
    3,
    5,
    7,
    11,
    13,
    17,
    19,
    23,
    29
};

static const size_t _cutil_indices[] =
{
    1,
    7,
    11,
    13,
    17,
    19,
    23,
    29
};

static int _cutil_is_prime(size_t x)
{
    const size_t N = sizeof(_cutil_small_primes) / sizeof(_cutil_small_primes[0]);
    for (size_t i = 3; i < N; ++i)
    {
        const size_t p = _cutil_small_primes[i];
        const size_t q = x / p;
        if (q < p)
            return 1;
        if (x == q * p)
            return 0;
    }
    for (size_t i = 31; 1;)
    {
        size_t q = x / i;
        if (q < i)
            return 1;
        if (x == q * i)
            return 0;
        i += 6;

        q = x / i;
        if (q < i)
            return 1;
        if (x == q * i)
            return 0;
        i += 4;

        q = x / i;
        if (q < i)
            return 1;
        if (x == q * i)
            return 0;
        i += 2;

        q = x / i;
        if (q < i)
            return 1;
        if (x == q * i)
            return 0;
        i += 4;

        q = x / i;
        if (q < i)
            return 1;
        if (x == q * i)
            return 0;
        i += 2;

        q = x / i;
        if (q < i)
            return 1;
        if (x == q * i)
            return 0;
        i += 4;

        q = x / i;
        if (q < i)
            return 1;
        if (x == q * i)
            return 0;
        i += 6;

        q = x / i;
        if (q < i)
            return 1;
        if (x == q * i)
            return 0;
        i += 2;
    }
    return 1;
}

CUTIL_INLINE static size_t _cutil_lower_bound(const size_t* a, size_t n, size_t element){
  for(size_t i = 0; i < n;i++){
    if(a[i] > element){
      return i;
    }
  }
  return n-1;
}

static size_t _cutil_next_prime(size_t n)
{
    const size_t L = 30;
    const size_t N = sizeof(_cutil_small_primes) / sizeof(_cutil_small_primes[0]);
    // If n is small enough, search in _cutil_small_primes
    if (n <= _cutil_small_primes[N-1])
      return _cutil_small_primes[_cutil_lower_bound(_cutil_small_primes, N,n)];
    // Else n > largest _cutil_small_primes
    // Start searching list of potential primes: L * k0 + _cutil_indices[in]
    const size_t M = sizeof(_cutil_indices) / sizeof(_cutil_indices[0]);
    // Select first potential prime >= n
    //   Known a-priori n >= L
    size_t k0 = n / L;
    size_t in = _cutil_lower_bound(_cutil_indices, M, n - k0*L);
    n = L * k0 + _cutil_indices[in];
    while (!_cutil_is_prime(n))
    {
        if (++in == M)
        {
            ++k0;
            in = 0;
        }
        n = L * k0 + _cutil_indices[in];
    }
    return n;
}

// END OF STOLEN CODE

CUTIL_INLINE static size_t _cutil_hash_func(void* key, size_t data_size){
  // KINDA BAD HASH FUNC 
  cutil_uint8* ptr = (cutil_uint8*)key;
  size_t h = 0;
  for(size_t i = 0; i < data_size;i++){
    h += 31*h + *(ptr + i);
  }
  return h;

}

CUTIL_INLINE static cutil_hash_el* _cutil_hash_el_create(void* key, void* value, size_t key_size, size_t value_size){
  cutil_hash_el* result = (cutil_hash_el*)CUTIL_MALLOC(sizeof(cutil_hash_el));
  if(!result) return NULL;
  result->key = CUTIL_MALLOC(key_size);
  if(!result->key) {
    CUTIL_FREE(result);
    return NULL;
  }
  CUTIL_MEMCPY(result->key, key, key_size);
  result->value = CUTIL_MALLOC(value_size);
  if(!result->value){
    CUTIL_FREE(result->key);
    CUTIL_FREE(result);
    return NULL;
  } 
  CUTIL_MEMCPY(result->value, value, value_size);
  result->next = NULL;
  return result;
}

// FIRST BYTE OF ANY KEY_VALUE_PAIR DICTATES IF SPOT IS VACANT OR NOT, MEANING ITS SET TO EITHER 0 or 1
CUTILDEF cutil_hash_s* cutil_hash_init(size_t key_size, size_t value_size, int (*keycmp)(const void*, const void*)){
  cutil_hash_s* result = (cutil_hash_s*)CUTIL_MALLOC(sizeof(cutil_hash_s));
  CUTIL_ASSERT(result != NULL);
  if(!result) return NULL;
  result->data = (cutil_hash_el**)CUTIL_MALLOC(sizeof(cutil_hash_el*) * _CUTIL_HASH_DEF_SIZE);
  CUTIL_ASSERT(result ->data != NULL);
  if(!result->data){
    CUTIL_FREE(result);
    return NULL;
  }
  result->capacity = _CUTIL_HASH_DEF_SIZE;
  result->n_buckets = 0;
  result->key_size = key_size;
  result->value_size = value_size;
  result->cmp = keycmp;
  for(size_t i = 0; i < result->capacity;i++){
    result->data[i] = NULL;
  }
  return result;  
}

CUTILDEF void cutil_hash_free(cutil_hash_s** map ){
  for(size_t i = 0; i < (*map)->capacity;i++){
    cutil_hash_el* head = (*map)->data[i];
    while(head != NULL){
      cutil_hash_el* prev = head;
      head = prev->next;
      CUTIL_FREE(prev->key);
      CUTIL_FREE(prev->value);
      CUTIL_FREE(prev);
    }
  }
  CUTIL_FREE((*map)->data);
  CUTIL_FREE(*map);
  *map = NULL;
}

static int _cutil_hash_put_h(cutil_hash_s* map, void* key, void* value){
  size_t index = _cutil_hash_func(key, map->key_size) % map->capacity;
  cutil_hash_el* h = map->data[index];
  while(h != NULL && map->cmp(h->key, key) != 0){
    h = h->next;  
  }

  if(h != NULL){
    CUTIL_MEMCPY(h->value, value, map->value_size);
    return 2;
  }
  else{
    cutil_hash_el* el = _cutil_hash_el_create(key, value, map->key_size, map->value_size);
    CUTIL_ASSERT(el != NULL);
    CUTIL_ASSERT(el->key != NULL);
    CUTIL_ASSERT(el->value != NULL);
    if(!el) return 0;
    el->next = map->data[index];
    map->data[index] = el;
    return 1;
  }
}


static void _cutil_hash_resize(cutil_hash_s** map){
  cutil_hash_s* m = (*map);
  size_t new_size = _cutil_next_prime(m->capacity*2 + 1);
  size_t old_capacity = m->capacity;

  cutil_hash_el** new_data = (cutil_hash_el**)CUTIL_MALLOC(sizeof(cutil_hash_el*) * new_size);
  CUTIL_ASSERT(new_data != NULL);
  if(!new_data) return;
  cutil_hash_el** old_data = m->data;
  m->data = new_data;
  m->capacity = new_size;
  for(size_t i = 0; i < m->capacity;i++){
    m->data[i] = NULL;
  }
  for(size_t i = 0; i < old_capacity;i++){
    if(old_data[i] != NULL){
      cutil_hash_el* h = old_data[i];
      while(h != NULL){
        (void)_cutil_hash_put_h(m, h->key, h->value);
        cutil_hash_el* old = h;
        h = h->next;
        CUTIL_FREE(old->key);
        CUTIL_FREE(old->value);
        CUTIL_FREE(old);
      } 
    }
  }
  CUTIL_FREE(old_data);
}

CUTILDEF int cutil_hash_put(cutil_hash_s* map, void* key, void* value){
  int sucess;
  sucess = _cutil_hash_put_h(map,key,value);
  if(!sucess) return sucess;
  if(sucess == 1)
    map->n_buckets++;
  if(map->n_buckets >= map->capacity/2){
    _cutil_hash_resize(&map);
  }
  return sucess;
}

CUTILDEF void* cutil_hash_get(cutil_hash_s* map, void* key){
  void* result = NULL;
  size_t index = _cutil_hash_func(key, map->key_size) % map->capacity;
  cutil_hash_el* h = map->data[index];
  while(h != NULL && map->cmp(key, h->key) != 0){
    h = h->next;
  }
  if(h != NULL){
    result = h->value;
  }
  return result;
}

#define _CUTIL_REINSERT_SIZE 8

CUTILDEF void cutil_hash_remove(cutil_hash_s* map, void* key){
  size_t index = _cutil_hash_func(key, map->key_size) % map->capacity;
  cutil_hash_el* h = map->data[index];
  cutil_hash_el* prev = NULL;
  while(h != NULL && map->cmp(key, h->key) != 0){
    prev = h;
    h = h->next;
  }
  if(h != NULL && prev == NULL){
    CUTIL_FREE(h->value);
    CUTIL_FREE(h->key);
    CUTIL_FREE(h);
    map->data[index] = NULL;
  }
  else{
    prev->next = h->next;
    CUTIL_FREE(h->value);
    CUTIL_FREE(h->key);
    CUTIL_FREE(h);
  }
  
}

CUTILDEF int cutil_hash_contains(cutil_hash_s* map, void* key){
  return cutil_hash_get(map, key) != NULL;
}
#endif // CUTIL_IMPLEMENTATION
