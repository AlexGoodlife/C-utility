// MODIFIED IMPLEMENTATION OF TIM SORT USING API
#include "../cutil.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "common.h"

#define MAX_INTERVAL 64
#include <assert.h>

typedef struct{
  size_t start;
  size_t length;
}_cutil_run;
inline static int get_run_size(size_t n)
{
  int notPower2= 0;
  while(n >= MAX_INTERVAL){
    if(n % 2 != 0)
      notPower2 = 1;
    n /= 2;
  }
  return notPower2 ? n + 1 : n;
}


inline static void swap(void*a, void*b,size_t data_size, void* tmp){
  memcpy(tmp,a,data_size);
  memcpy(a,b,data_size);
  memcpy(b, tmp,data_size);
}
static void insertion_sort(void* a, size_t data_size, int(*cmp)(const void*,const void*), size_t low, size_t high, size_t initial_sorted)
{
  assert(low <= high);
  assert(low + initial_sorted <= high+1);
  void* tmp = malloc(data_size);

  int limit = high +1;
  for(int i = low+initial_sorted; i < limit; i++)
  {
    for(size_t j = i; j > low ; j--)
    {
      void* a_j = (cutil_uint8*)a + j*data_size;
      void* a_j_1 = (cutil_uint8*)a + (j-1)*data_size;
      if(cmp(a_j,a_j_1) < 0){
        swap(a_j,a_j_1,data_size,tmp);
      }
      else break;
    }
  }
  free(tmp);

}

_cutil_run get_natural_run(void* a, size_t low, size_t high, size_t data_size, int(*cmp)(const void*, const void*)){
  assert(low <= high);
  size_t count = 1;
  size_t i = low + 1;
  while(i <=high && cmp((cutil_uint8*) a + i * data_size, (cutil_uint8*) a + (i-1)*data_size) >= 0){
    count++;
    i++;
  }
  _cutil_run result;
  result.start = low;
  result.length = count;
  return result;
}

_cutil_run get_run_descending(void* a, size_t low, size_t high,size_t data_size,int(*cmp)(const void*, const void*)){
  assert(low <= high);
  size_t count = 1;
  size_t i = low + 1;
  while(i <=high && cmp((cutil_uint8*) a + i * data_size, (cutil_uint8*) a + (i-1)*data_size) < 0){
    count++;
    i++;
  }
  _cutil_run result;
  result.start = low;
  result.length = count;
  return result;
}

void invert_array(void*a, size_t low, size_t high, size_t data_size){
  void* temp = malloc(data_size);
  while(low < high){
    swap((cutil_uint8*)a + low * data_size, (cutil_uint8*) a + high*data_size, data_size,temp);
    low++;
    high--;
  }
  free(temp);
}

_cutil_run get_run_or_ascend(void* a, size_t low, size_t high,size_t data_size, int(*cmp)(const void*, const void*))
{
  assert(low <= high);

  if(high+1 - low <=1){
    _cutil_run result;
    result.start = low;
    result.length = 1;
    return result;
  }
  _cutil_run result;
  if(cmp((cutil_uint8*)a + low * data_size, (cutil_uint8*)a + (low+1)*data_size) < 0){
    result = get_natural_run(a,low,high, data_size, cmp);
  }
  else{
    result = get_run_descending(a, low , high,data_size, cmp);
    invert_array(a, low, low + result.length-1, data_size);
  }
  return result;
}

size_t math_min(size_t a, size_t b){
  return a > b ? b : a;
}
_cutil_run run_with_min_size(void* a,size_t n, size_t data_size, int(*cmp)(const void*,const void*), size_t low, size_t high, size_t min_run_size)
{
  assert(low <= high);
  assert(min_run_size > 0);

  _cutil_run result = get_run_or_ascend(a,low,high,data_size,cmp);

  if(result.length < min_run_size){
    insertion_sort(a,data_size,cmp,low, math_min(min_run_size+ low - 1, high), result.length);
    result = get_natural_run(a,low,high,data_size,cmp);
  }

  return result;
}

void merge_left(cutil_uint8* a, cutil_uint8* aux, _cutil_run leftRun, _cutil_run rightRun, size_t data_size, int(*cmp)(const void*, const void*))
{
  // printf("merge left\n");
  assert(rightRun.start == leftRun.start + leftRun.length);

  long low = leftRun.start;
  long high = rightRun.start+rightRun.length-1;

  long left = 0;
  long right = rightRun.start;

  memcpy(aux, a + low * data_size, leftRun.length*data_size);

  for(long i = low; i <= high; i++)
  {
    if (left > (long)leftRun.length-1){
      memmove(a + i*data_size, a + (right++)*data_size,data_size);
    }
    else if(right > high){
      memmove(a + i*data_size, aux + (left++)*data_size,data_size);
    }
    else if(cmp(a + right * data_size, aux + left*data_size) < 0){
      memmove(a + i*data_size, a + (right++)* data_size, data_size);
    }
    else{
      memmove(a + i *data_size, aux + (left++)*data_size, data_size);
    }
  }
}

void merge_right(cutil_uint8* a, cutil_uint8* aux, _cutil_run leftRun, _cutil_run rightRun, size_t data_size, int(*cmp)(const void*, const void*))
{
  // printf("merge_right\n");
  assert(rightRun.start == leftRun.start + leftRun.length);

  long low = leftRun.start;
  long high = rightRun.start+rightRun.length-1;

  long right = rightRun.length-1;
  long mid = rightRun.start-1;
  long left = mid;
  // printf("low: %lu\n, high: %lu\n, right: %lu\n, mid: %lu\n, left: %lu\n", low, high, right, mid, left);

  memcpy(aux, (cutil_uint8*) a + data_size*rightRun.start, rightRun.length * data_size);

  for(long i = high; i >= low; i--)
  {
    //left array is exausted
    if (left < low){
      memmove(a + i * data_size, aux + (right--)*data_size, data_size);
    }
      //right array is exausted
    else if (right < 0){
      memmove(a + i * data_size, a + (left--)*data_size, data_size);
    }
    else if(cmp(aux + right *data_size, a + left * data_size) >= 0){
      memmove(a + i * data_size, aux + (right--)*data_size, data_size);
    }
    else
      memmove(a + i * data_size, a + (left--)*data_size, data_size);
  }
}

void merge(cutil_uint8* a,cutil_uint8* buffer,_cutil_run leftRun, _cutil_run rightRun,size_t data_size, int(*cmp)(const void*, const void*))
{
  _cutil_run left = leftRun.start < rightRun.start ? leftRun : rightRun;
  _cutil_run right = (left.start == leftRun.start && left.length == leftRun.length) ? rightRun : leftRun;
  if(left.length >= right.length){
    // printf("merge right\n");
    merge_right(a,buffer, left, right,data_size, cmp);
  }
  else{
    // printf("merge left\n");
    merge_left(a,buffer, left, right, data_size, cmp);
  }
}

void collapse_stack(CUTIL_VECTOR(_cutil_run) stack, int i){
  int index = CUTIL_VECTOR_SIZE(stack)-(i+1);
  assert(index >= 0);
  _cutil_run collapsed;
  collapsed.start = stack[index].start;
  collapsed.length = stack[index+1].length + stack[index].length;
  // _cutil_run collapsed = {.start = stack[index].start, .length = stack[index+1].length + stack[index].length};
  stack[index] = collapsed;
  // this.runs[index] = this.runs[index].collapse(this.runs[index+1]);

  CUTIL_VECTOR_SIZE(stack)--;
  for(size_t j = index +1; j < CUTIL_VECTOR_SIZE(stack); j++)
  {
    stack[j]  = stack[j+1];
  }

}
void merge_collapse(CUTIL_VECTOR(_cutil_run) stack, cutil_uint8* buffer, cutil_uint8* a,size_t n,size_t data_size, int(*cmp)(const void*, const void*))
{

  size_t h;
  while((h = CUTIL_VECTOR_SIZE(stack)) > 1){
    if(h >= 3 && stack[h-1].length > stack[h-3].length){
      merge(a,buffer,stack[h-2], stack[h-3],data_size,cmp);
      // merge(a,buffer,stack.get(2), stack.get(3));
      // stack.collapse(2);
      collapse_stack(stack, 2);
    }
    else if(h>= 2 && stack[h-1].length >= stack[h-2].length){
      merge(a,buffer,stack[h-1], stack[h-2], data_size, cmp);
      // merge(a,buffer,stack.get(1), stack.get(2));
      // stack.collapse(1);
      collapse_stack(stack, 1);
    }
    else if(h>= 3 && (stack[h-1].length + stack[h-2].length) >= stack[h-3].length){
      merge(a, buffer, stack[h-1], stack[h-2], data_size, cmp);
      // merge(a,buffer,stack.get(1), stack.get(2));
      // stack.collapse(1);
      collapse_stack(stack, 1);
    }
    else if(h>= 4 &&(stack[h-2].length + stack[h-3].length) >= stack[h-4].length){
      merge(a,buffer,stack[h-1], stack[h-2],data_size,cmp);
      // merge(a,buffer,stack.get(1), stack.get(2));
      // stack.collapse(1);
      collapse_stack(stack, 1);
    }
    else{
      break;
    }
  }
}

void sort(void*a, size_t n, size_t data_size, int(*cmp)(const void*, const void*))
{
  if(n < 64){
    insertion_sort(a,data_size,cmp,0,n-1,0);
    return;
  }

  int k = get_run_size(n);
  cutil_uint8* buffer = (cutil_uint8*)malloc(data_size*(n/2));
  if(!buffer) return;
  
  CUTIL_VECTOR(_cutil_run) stack = CUTIL_VECTOR_INIT(_cutil_run);
  _cutil_run r;
  for(size_t i = 0; i < n; i += r.length){
    // printf("One iteration\n");
    r = run_with_min_size(a,n,data_size,cmp,i,n-1,k);
    CUTIL_VECTOR_PUSH(stack, r);
    merge_collapse(stack, (cutil_uint8*)buffer, (cutil_uint8*)a,n,data_size,cmp);
    // printf("done with merge_collapse\n");
  }
  //
  while(CUTIL_VECTOR_SIZE(stack) > 1){
    // printf("Im done\n");
    size_t height = CUTIL_VECTOR_SIZE(stack);
    merge((cutil_uint8*)a, buffer, stack[height-1],stack[height-2],data_size,cmp);
    collapse_stack(stack, 1);
    // stack.collapse(1);
  }
  free(buffer);
  CUTIL_VECTOR_FREE(stack);

}



#define SIZE 100000
int main(){
  CUTIL_VECTOR(person_t*) v = CUTIL_VECTOR_INIT(person_t*);
  int a[SIZE];
  for(int i = 0; i < SIZE;i++){
    
    a[i] = rand();
  }

  sort(a,SIZE,sizeof(int),intcmp);
  assert(is_sorted_ints(a,SIZE));
  printf("Ints are good\n");

  
  for(int i = 0; i < SIZE;i++){
    person_t* r = random_person();
    CUTIL_VECTOR_PUSH(v, r);
  }

  sort(v,SIZE,sizeof(person_t*),personcmp);

  assert(is_sorted_people(v, CUTIL_VECTOR_SIZE(v)));
  for(int i = 0; i < SIZE;i++){
    free(v[i]);
  }

  CUTIL_VECTOR_FREE(v);
  printf("ALL GOOD\n");
  return 0;
}
