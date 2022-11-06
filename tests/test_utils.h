#ifndef TEST_UITL_CUTIL
#define TEST_UTIL_CUTIL

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    const char* name;
    int age;
}Person;

Person mike = {"mike", 21};
Person jane = {"jane", 32};
Person manny = {"manny", 17};
Person beatrice = {"beatrice", 22};
Person summer = {"summer", 44};
Person jacques = {"jacques", 12};
Person alex =  {"alex", 26};
Person richard = {"richard", 55};

Person *people[8] = {&mike, &jane, &manny, &beatrice, &summer, &jacques, &alex, &richard};

#define MIKE (people + 0)
#define JANE (people + 1)
#define MANNY (people + 2)
#define BEATRICE (people +3)
#define SUMMER (people + 4)
#define JACQUES (people + 5)
#define ALEX (people + 6)
#define RICHARD (people + 7)

#define n_people (sizeof people / sizeof *people)

int numbers[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

int random_number(size_t lower, size_t upper){
    return (rand() % (upper-lower+1)) + lower;
}

int int_cmp(const void*x, const void*y){
    return( *(int*)x - *(int*)y);
}

int person_cmp(const void*x, const void*y){
    Person* first = *(Person**)x;
    Person *second = *(Person**)y;
    return strcmp(first->name,second->name);
}

bool isSorted(void *a, size_t size,size_t data_size,int(*cmp)(const void*, const void*)){
    for(int i = 1; i < size; i++){
        if(cmp(a+((i-1)*data_size), a+(i*data_size)) > 0)
            return false;
    }
    return true;
}

bool isEqual(void *a, void* b, size_t size,size_t data_size,int(*cmp)(const void*, const void*)){
    for(int i = 0; i < size; i++){
        if(cmp(a+(i*data_size), b+(i*data_size)) != 0)
            return false;
    }
    return true;
}

int *exampleArray(size_t n){
    int *result = malloc(sizeof(int)*n);
    for(int i = 0; i < n;i++){
        result[i] = random_number(0,n);
    }
    return result;
}

#endif