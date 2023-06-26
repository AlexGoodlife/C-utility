#ifndef CUTIL_COMMON_H
#define CUTIL_COMMON_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
typedef struct{
  const char* name;
  int age;
}person_t;

inline static int intcmp(const void*a, const void*b){
  int x = *(int*)a;
  int y = *(int*)b;
  return x - y;
}

inline static int personcmp(const void*a, const void* b){
  int result = strcmp((*(person_t**)a)->name, (*(person_t**)b)->name);
  if(!result)
    result = ((*(person_t**)a)->age - (*(person_t**)b)->age);
  return result;
}

inline static int arrays_equal(void*a, void* b,size_t n,size_t m,size_t data_size, int(*cmp)(const void*, const void*)){
  assert(n==m);
  for(size_t i = 0; i < n;i++){
    if(cmp((char*)a + i*data_size, (char*)b + i*data_size) != 0)
      return 0;
  }
  return 1;
}

inline static void print_ints(int* a, int n){
  printf("[");
  for(int i = 0; i < n;i++){
    printf("%d\n", a[i]);
  }
  printf("]");
}

inline static int is_sorted(void* a, size_t n, size_t data_size, int(*cmp)(const void*, const void*)){
  for(size_t i = 0; i < n-1;i++){
    if(cmp((char*) a + i * data_size, (char*)a + (i+1)*data_size) > 0){
      return 0;
    }
  }
  return 1;
}

static const char*  people[] = {
  "John",
  "Michael",
  "Mary",
  "Joseph",
  "Peter",
  "Lois",
  "Chris",
  "Stewart",
  "Megan",
  "Glenn",
  "Joe",
  "Bonnie",
  "Cleveland",
  "Donna",
  "Some other family guy character"
};

inline static person_t* random_person(){
  int n_people = sizeof(people)/sizeof(*people);
  person_t result;
  result.age = rand();
  result.name = people[rand() % n_people];
  person_t* ptr = (person_t*)malloc(sizeof(person_t));
  *ptr = result;
  return ptr;
}

inline static void shuffle_array(int*a, int n){
  for(int i = 0; i < n;i++){
    // a[i] = i;
    a[i] = rand();
  }
}

// inline static void shuffle_array(int*a, int n){
//   int divisions = (int)(0.00001*n);
//   int stop = divisions == 0 ? 1 : n/divisions;
//   for(int i = 0; i < n;i++){
//     if((i+1) % stop == 0){
//       int put = rand();
//       // while(i!= 0 && !less(put, result[i-1]))
//       //     put = randomGenerator.nextInt(n);
//       a[i] = put;
//     }
//     else{
//       a[i] = i;
//     }
//   }
// }

inline static void shuffle_array_people(person_t** a, int n){
  for(int i = 0; i < n;i++){
    a[i] = random_person();
  }
}

#define assert_ints(a,b,n,m) assert(arrays_equal((void*)a,(void*)b,n,m,sizeof(int),intcmp))
#define assert_people(a,b,n,m) assert(arrays_equal((void*)a,(void*)b,n,m,sizeof(person_t*),personcmp))
#define is_sorted_ints(a,n) is_sorted((void*)a, n, sizeof(int), intcmp)
#define is_sorted_people(a, n) is_sorted((void*)a, n, sizeof(person_t*), personcmp)



#endif //CUTIL_COMMON_H
