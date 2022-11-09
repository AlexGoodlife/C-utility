#include <assert.h>
#include <stdio.h>
#include "../../include/arraylist.h"

#include "../include/test_utils.h"
#include "../include/unit_tests.h"

#define list_get(a,i) *(void**)arraylist_get(a,i) 

//tests basic arraylist functionality
void test_basic(){
    ArrayList a = arraylist_create(sizeof(int), int_cmp);
    assert(a != NULL);
    assert(arraylist_getLength(a) == 0);
    assert(arraylist_isEmpty(a));
    
    assert(arraylist_add(a,&numbers[0]));
    assert(arraylist_add(a,&numbers[1]));
    assert(arraylist_add(a,&numbers[2]));
    assert(arraylist_add(a,&numbers[3]));
    assert(arraylist_add(a,&numbers[4]));
    assert(arraylist_add(a,&numbers[5]));

    assert(!(arraylist_add(a, NULL)));
    assert(arraylist_getLength(a) == 6);
    assert(!arraylist_isEmpty(a));

    assert(arraylist_contains(a,&numbers[0]));
    assert(arraylist_contains(a,&numbers[1]));
    assert(arraylist_contains(a,&numbers[2]));
    assert(arraylist_contains(a,&numbers[3]));
    assert(arraylist_contains(a,&numbers[4]));
    assert(arraylist_contains(a,&numbers[5]));

    int *x = arraylist_get(a, 4);
    assert((*x) == 4);
    int y = arraylist_find(a,&numbers[0]);
    assert(y == 0);
    assert(y == arraylist_findLast(a,&numbers[0]));

    assert(arraylist_get(a,6) == NULL);
    assert(arraylist_find(a,&numbers[19]) == -1);

    int compare[] = {0,1,2,3,4};
    int *array = arraylist_toArray(a);
    
    // for(int i = 0; i < 6;i++){
    //     printf("%d\n", array[i]);
    // }
    assert(isEqual(compare, array, 5, sizeof(int),int_cmp));
    free(array);

    int compare_2[] = {0,1,2,3,19};
    arraylist_set(a,4,&numbers[19]);
    array =  arraylist_toArray(a);

    // for(int i = 0; i < 6;i++){
    //     printf("%d\n", array[i]);
    // }
    assert(isEqual(compare_2, array, 5, sizeof(int),int_cmp));
    free(array);
    
    arraylist_destroy(&a);

    ArrayList b = arraylist_create(sizeof(Person*), person_cmp);
    assert(b != NULL);
    assert(arraylist_getLength(b) == 0);
    assert(arraylist_isEmpty(b));

    assert(arraylist_add(b,&people[0]));
    assert(arraylist_add(b,&people[1]));
    assert(arraylist_add(b,&people[2]));
    assert(arraylist_add(b,&people[3]));
    assert(arraylist_add(b,&people[4]));

    // Person* q = *(Person**)arraylist_get(b,0);
    // printf("%s\n", q->name);

    // printf("add\n");
    Person **arr = arraylist_toArray(b);
    // printf("%d\n", (*arr)->age);
    // for(int i = 0; i < 5;i++){
    //     Person *p = arr[i];
    //     printf("%s\n", p->name);
    // }

    assert(!(arraylist_add(b, NULL)));
    assert(arraylist_getLength(b) == 5);
    assert(!arraylist_isEmpty(b));
    assert(arraylist_contains(b,&people[0]));
    assert(arraylist_contains(b,&people[1]));
    assert(arraylist_contains(b,&people[2]));
    assert(arraylist_contains(b,&people[3]));
    assert(arraylist_contains(b,&people[4]));


    // Person *p = list_get(b,3);


    Person *p = *(Person**)arraylist_get(b,3);
    // printf("%d\n", p->age);
    assert(p->age == 22);

    int z = arraylist_find(b,&people[0]);
    assert(z == 0);
    assert(z == arraylist_findLast(b,&people[0]));

    assert(arraylist_get(b,5) == NULL);
    assert(arraylist_find(b,&people[7]) == -1);

    arr = arraylist_toArray(b);
    Person *comp[] = {MIKE, JANE, MANNY, BEATRICE, SUMMER};
    assert(isEqual(arr, comp, 5, sizeof(Person*), person_cmp));

    arraylist_destroy(&b);

}

void test_morphs(){
    // ArrayList a = arraylist_create(sizeof(int), int_cmp);
}

void unit_arraylist(){
    test_basic();
    test_morphs();
}

