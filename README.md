# Single header stb style libraries

This serves as repo for me to package the random bits of utilitarian code I make for my  projects.
These files are made for ease of use and portability you can disable use of the standard library,
provided you implement the required functions by use of provided macros.

## Instalation

Just download the ".h" file of your choosing and in any source file (I recommend doing it in a seperate file) write: 
```C 
#define CUTIL_IMPLEMENTATION
#include <whatever_cutil_file.h>
```

And you're good to go, just compile the source file and you can just include the header in any other source files and everything will work.
But make sure you do the #define **BEFORE** the #include.

## Modules

 - vecq
    - Packages dynamic array, queue and some array utilities
 - hash
    - Packages hash

# Some usage

## vecq 

the vector and queue structures work exactly like C arrays with one limitation,
do **NOT** increment or otherwise change the pointer given to you by "CUTIL_VECTOR_INIT()" or "CUTIL_QUEUE_INIT()",
this results in undefined behaviour. The vectors double up as stacks aswell.

```C
  CUTIL_VECTOR(int) vec = CUTIL_VECTOR_INIT(int);

  size_t size = CUTIL_VECTOR_SIZE(vec);
  for(int i = 0; i < NUMS;i++){
    CUTIL_VECTOR_PUSH(vec, i);
  }

  size = CUTIL_VECTOR_SIZE(vec);
  for(size_t i = 0; i < size;i++){
    printf("%d\n", vec[i]); // Acess elements just like an array
  }

  for(size_t i = 0; i < size;i++){
    printf("%d\n", CUTIL_VECTOR_POP(vec)); //pops elements
  }
  CUTIL_VECTOR_CLEAR(vec); // clears all elements
  CUTIL_VECTOR_FREE(vec);
```

## hash

Hash uses the standard closed addressing approach with chaining, it also takes ownwership of whatever data is provided
meaning it will use more memory.

```C
  cutil_hash_s *ht = cutil_hash_init(sizeof(some_key_struct),sizeof(some_value_struct),cmp_func);  
  for(int i = 0; i < number;i++){
    some_key_struct key = some_key;
    some_value_struct value = some_value;
    cutil_hash_put(ht,&key,&value); 
    if(i % 2 == 0){
      cutil_hash_remove(ht, &key); // you can also remove
    }
  }
  some_value_struct lookup = cutil_hash_get(ht, &whatever_key);
  cutil_hash_free(&ht); // in the end free memory like usual
```

