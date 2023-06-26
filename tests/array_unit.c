#define CUTIL_IMPLEMENTATION
#include "../cutil_vecq.h"
#include "common.h"

#include <stdio.h>
#include <time.h>
#define LIMIT 1000000

void push_test(){
  {
    CUTIL_VECTOR(int) v = CUTIL_VECTOR_INIT(int);
    int test[LIMIT];
    for(int i = 0; i < LIMIT;i++){
      CUTIL_VECTOR_PUSH(v,i);
      test[i] = i;
    }
    assert_ints(v,test,LIMIT,LIMIT);
    CUTIL_VECTOR_FREE(v);
  }

  {
    CUTIL_VECTOR(person_t*) v2 = CUTIL_VECTOR_INIT(person_t*);
    person_t* test2[LIMIT];
    const char* names[5] = {"Ricchie", "Jica", "Boavida", "Bruno", "Afonso"};
    for(int i = 0; i < LIMIT;i++){
      int random = rand() % 5;
      person_t* a = (person_t*)malloc(sizeof(person_t));
      a->age = i;
      a->name = names[random];
      test2[i] = a;
      CUTIL_VECTOR_PUSH(v2,a);
    }
    assert_people(v2,test2,LIMIT,LIMIT);
    for(int i = 0; i < LIMIT;i++){
      free(test2[i]);
      test2[i] = NULL;
     }
    CUTIL_VECTOR_FREE(v2);
  }
}

void pop_test(){
  {
    CUTIL_VECTOR(int) v = CUTIL_VECTOR_INIT(int);
    int test[LIMIT];

    for(int i = 0; i < LIMIT;i++){
      CUTIL_VECTOR_PUSH(v,i);
      test[i] = i;
    }

    for(int i = 0; i < LIMIT;i++){
      assert(CUTIL_VECTOR_POP(v) == test[LIMIT- i-1]);
    }
    for(int i = 0; i < 10;i++){
      CUTIL_VECTOR_PUSH(v,i);
      if(i % 2 == 0){
        (void)(CUTIL_VECTOR_POP(v));
      }
    }
    int j = 0;
    for (int i = 0; i < 10; i++) {
      if(i % 2 != 0)
        test[j++] = i;
    }
    assert_ints(v,test,5,5);
  }
}

void test_free(){
  CUTIL_VECTOR(int) v = CUTIL_VECTOR_INIT(int);
  for(int i = 0; i < LIMIT;i++){
    CUTIL_VECTOR_PUSH(v,i);
  }

  CUTIL_VECTOR_CLEAR_MEMORY(v);
  int test[LIMIT];
  for(int i = 0; i < LIMIT;i++){
    CUTIL_VECTOR_PUSH(v,i);
    test[i] = i;
  }
  assert_ints(v,test,LIMIT,LIMIT);

  CUTIL_VECTOR_FREE(v);
}

#define ACCESS_LIMIT 10000000
void random_access_test(){
  CUTIL_VECTOR(int) v = CUTIL_VECTOR_INIT(int);
  for(int i = 0; i < LIMIT;i++){
    CUTIL_VECTOR_PUSH(v,i);
  }

  for(int i = 0; i < ACCESS_LIMIT;i++){
    if(((double)rand() / RAND_MAX) <= 0.5){
      v[i % LIMIT] = rand();
    }
    else{
      (void)CUTIL_VECTOR_POP(v);
      CUTIL_VECTOR_PUSH(v, i);
    }
  }

  // CHECK IF IT SEGFAULTS OR NOT
}


#define a_size 10
void sort_test(){
  int a[a_size] = {0,8,4,2,1,3,9,5,6,7};
  // assert(is_sorted_ints(a,a_size));
  assert(*(int*)cutil_array_max(a, a_size, sizeof(int), intcmp) == 9);
  assert(*(int*)cutil_array_min(a, a_size, sizeof(int), intcmp) == 0);
}

void unit_tests() {
  push_test();
  pop_test();
  test_free();
  random_access_test();
  sort_test();
}

int main(){
  srand(time(0));
  unit_tests();
  printf("ALL UNIT TESTS PASSED\n");
}
