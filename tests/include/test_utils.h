#ifndef TEST_UTIL_CUTIL
#define TEST_UTIL_CUTIL

typedef struct{
    const char* name;
    int age;
}Person;

extern Person* people[8];

#define MIKE people[0]
#define JANE people[1]
#define MANNY people[2]
#define BEATRICE people[3]
#define SUMMER people[4]
#define JACQUES people[5]
#define ALEX people[6]
#define RICHARD people[7]

#define n_people (sizeof people / sizeof *people)

extern int numbers[20];

int random_number(size_t lower, size_t upper);

int int_cmp(const void*x, const void*y);

int person_cmp(const void*x, const void*y);

bool isSorted(void *a, size_t size,size_t data_size,int(*cmp)(const void*, const void*));

bool isEqual(void *a, void* b, size_t size,size_t data_size,int(*cmp)(const void*, const void*));

int *exampleArray(size_t n);

size_t copyArray(void*input, size_t size, size_t data_size,void*output);

#endif