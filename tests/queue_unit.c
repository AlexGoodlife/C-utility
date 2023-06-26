#include "common.h"
#include <stdio.h>
#define CUTIL_DEBUG
#define CUTIL_IMPLEMENTATION
#include "../cutil_vecq.h"


void integrity_test(){
  CUTIL_QUEUE(int) q= CUTIL_QUEUE_INIT(int);
  for(int i = 0; i < 7;i++){
    CUTIL_QUEUE_ENQUEUE(q,i);
  }

  for(int i = 0; i < 6;i++){
    (void)CUTIL_QUEUE_DEQUEUE(q);
  }
  int test[7] = {0,1,2,3,4,5,6};
  assert_ints(test, q,7,7);

  for(int i = 0; i < 6;i++){
    CUTIL_QUEUE_ENQUEUE(q, i + 7);
  }
  printf("head: %zu\n", CUTIL_QUEUE_HEAD(q));
  printf("capacity : %zu\n", CUTIL_QUEUE_CAPACITY(q));
  printf("size: %zu\n", CUTIL_QUEUE_SIZE(q));
  print_ints(q,8);

  int test_2[8] = {8,9,10,11,12,5,6,7};
  assert_ints(test_2, q,8,8);
  CUTIL_QUEUE_ENQUEUE(q, 69);
  int test_3[8] = {6,7,8,9,10,11,12,69};
  assert_ints(test_3, q,8,8);
  assert(CUTIL_QUEUE_CAPACITY(q) == 16);
  assert(CUTIL_QUEUE_SIZE(q) == 8);
  CUTIL_QUEUE_FREE(q);
}

#define NUMBERS 10000000

void stress_test(){
  CUTIL_QUEUE(int) q= CUTIL_QUEUE_INIT(int);
  for(int i = 0; i < NUMBERS;i++){
    CUTIL_QUEUE_ENQUEUE(q,i);
  }

  assert(CUTIL_QUEUE_CAPACITY(q) > NUMBERS);
  CUTIL_QUEUE_FREE(q);
}

void unit_tests(){
  integrity_test();
  stress_test();
}

int main(){
  unit_tests(); 
  printf("ALL UNIT TESTS PASSED\n");
}
