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

#define ints_clone(a,n) array_clone(a,n,sizeof(int))

#define person_clone(a,n) array_clone(a,n,sizeof(Person*))

#define ints_equal(a,b,n) isEqual(a,b,n,sizeof(int),int_cmp)

#define person_equal(a,b,n) isEqual(a,b,n,sizeof(Person*),person_cmp)


extern int numbers[20];

#define n_numbers (sizeof numbers / sizeof *numbers)

int random_number(size_t lower, size_t upper);

int int_cmp(const void*x, const void*y);

int person_cmp(const void*x, const void*y);

bool isSorted(void *a, size_t size,size_t data_size,int(*cmp)(const void*, const void*));

bool isEqual(void *a, void* b, size_t size,size_t data_size,int(*cmp)(const void*, const void*));

int *exampleArray(size_t n);

size_t copyArray(void*input, size_t size, size_t data_size,void*output);

#endif