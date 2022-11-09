#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/algorithm.h"

#include "../include/test_utils.h"
#include "../include/unit_tests.h"

//Tests for insertion sort
void unit_isort(){
    int a[10] = {10,9,8,7,6,5,4,3,2,1};
    insertion_sort(a,10,sizeof(int),int_cmp);
    assert(isSorted(a,10,sizeof(int),int_cmp));

    int* b = exampleArray(1000);
    insertion_sort(b, 1000, sizeof(int), int_cmp);
    assert(isSorted(b,1000,sizeof(int),int_cmp));
    free(b);

    int *c = exampleArray(10000);
    insertion_sort(c, 10000,sizeof(int), int_cmp);
    assert(isSorted(c,10000,sizeof(int),int_cmp));
    free(c);

    int d[1] = {1};
    insertion_sort(d,1,sizeof(int),int_cmp);

    int e[0] = {};
    insertion_sort(e,0,sizeof(int),int_cmp);
}

void unit_mergesort(){
    int a[10] = {10,9,8,7,6,5,4,3,2,1};
    merge_sort(a,10,sizeof(int),int_cmp);
    assert(isSorted(a,10,sizeof(int),int_cmp));

    int* b = exampleArray(1000);
    merge_sort(b, 1000, sizeof(int), int_cmp);
    assert(isSorted(b,1000,sizeof(int),int_cmp));
    free(b);

    int *c = exampleArray(10000);
    merge_sort(c, 10000,sizeof(int), int_cmp);
    assert(isSorted(c,10000,sizeof(int),int_cmp));
    merge_sort(c, 10000,sizeof(int), int_cmp);
    assert(isSorted(c,10000,sizeof(int),int_cmp));
    free(c);

    int d[1] = {1};
    merge_sort(d,1,sizeof(int),int_cmp);

    int e[0] = {};
    merge_sort(e,0,sizeof(int),int_cmp);
}

//test for searches
void unit_searches(){
    int a[11] = {10,9,8,7,6,5,5,4,3,2,1};
    int* p = &a[5];
    assert(linear_search(a,11,sizeof(int),p,int_cmp) == 5);
    assert(linear_lastsearch(a,11,sizeof(int),p,int_cmp) == 6);

    int x = 22;
    assert(linear_search(a,11,sizeof(int),&x,int_cmp) == -1);
    assert(linear_search(a,11,sizeof(int),&a[0],int_cmp) == 0);
    assert(linear_search(a,11,sizeof(int),&a[10],int_cmp) == 10);

    assert(linear_search(people, n_people, sizeof(Person*),&MIKE,int_cmp) == 0);
    assert(linear_search(people, n_people, sizeof(Person*),&JANE,int_cmp) == 1);
    assert(linear_search(people, n_people, sizeof(Person*),&RICHARD,int_cmp) == 7);

    insertion_sort(a, 11, sizeof(int), int_cmp);

    int b[5] = {1,2,3,4};
    x = 1;
    int y = 94;
    assert(binary_search(b,5,sizeof(int),&x, int_cmp) == 0);
    assert(binary_search(a,11,sizeof(int),&x, int_cmp) == 0);
    assert(binary_lastsearch(a,11,sizeof(int),&x, int_cmp) == 0);
    assert(binary_lastsearch(a,11,sizeof(int),&x, int_cmp) == 0);
    assert(binary_search(a,11,sizeof(int),&a[10], int_cmp) == 10);
    assert(binary_lastsearch(a,11,sizeof(int),&a[10], int_cmp) == 10);
    assert(binary_search(a,11,sizeof(int),&a[5], int_cmp) == 4);
    assert(binary_lastsearch(a,11,sizeof(int),&a[5], int_cmp) == 5);
    assert(binary_search(a,11,sizeof(int),&y, int_cmp) == -1);
    assert(binary_lastsearch(a,11,sizeof(int),&y, int_cmp) == -1);
    assert(binary_search(a,11,sizeof(int),&a[9], int_cmp) == 9);

    Person* peepz[n_people+1];
    size_t n_peepz = copyArray(people, n_people,sizeof(Person*),peepz)+1;
    peepz[n_people] = MIKE;
    insertion_sort(peepz,n_peepz,sizeof(Person*),person_cmp);
    
    #define bin_people(a,n,t) binary_search(a,n,sizeof(Person*),t,person_cmp)
    #define binlast_people(a,n,t) binary_lastsearch(a,n,sizeof(Person*),t,person_cmp)

    assert(binary_search(peepz, n_peepz, sizeof(Person*),&ALEX,person_cmp) == 0);
    assert(binary_lastsearch(peepz, n_peepz, sizeof(Person*),&ALEX,person_cmp) == 0);
    assert(bin_people(peepz, n_peepz, &SUMMER) == 8);
    assert(binlast_people(peepz,n_peepz, &SUMMER) == 8);
    assert(bin_people(peepz, n_peepz, &JACQUES) == 2);
    assert(binlast_people(peepz,n_peepz, &JACQUES) == 2);
    assert(bin_people(peepz,n_peepz,&MIKE) == 5);
    assert(binlast_people(peepz, n_peepz, &MIKE) == 6);
}

#define ints_clone(a,n) array_clone(a,n,sizeof(int))
#define ints_equal(a,b,n) isEqual(a,b,n,sizeof(int),int_cmp)
void unit_clone(){

    int a[11] = {10,9,8,7,6,5,5,4,3,2,1};
    int *b = ints_clone(a,11);
    assert(ints_equal(a,b,11));
    free(b);

    int *test = exampleArray(1000);
    int *c = ints_clone(test,1000);
    assert(ints_equal(test,c,1000));
    free(test);
    free(c);

    test = exampleArray(100000);
    int *d = ints_clone(test, 100000);
    assert(ints_equal(test,d,100000));
    free(test);
    free(d);

    Person** p = array_clone(people, n_people, sizeof(Person*));
    assert(isEqual(people,p,n_people,sizeof(Person*),person_cmp));
    free(p);

}

void unit_max_min(){
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    assert(*(int*)array_max(a,10,sizeof(int),int_cmp) == 9);
    assert(array_argmax(a,10,sizeof(int),int_cmp) == 9);
    assert(*(int*)array_min(a,10,sizeof(int),int_cmp) == 0);
    assert(array_argmin(a,10,sizeof(int),int_cmp) == 0);

    int b[10] = {5,4,3,2,-22,1,12,8,7,6};
    assert(*(int*)array_max(b,10,sizeof(int),int_cmp) == 12);
    assert(array_argmax(b,10,sizeof(int),int_cmp) == 6);
    assert(*(int*)array_min(b,10,sizeof(int),int_cmp) == -22);
    assert(array_argmin(b,10,sizeof(int),int_cmp) == 4);

    assert(person_cmp((Person**)array_max(people, n_people, sizeof(Person*),person_cmp), &SUMMER) == 0);
    assert(array_argmax(people, n_people, sizeof(Person*),person_cmp) == 4);
    assert(person_cmp((Person**)array_min(people, n_people, sizeof(Person*),person_cmp), &ALEX) == 0);
    assert(array_argmin(people, n_people, sizeof(Person*),person_cmp) == 6);      

}

void unit_algorithm(){
    unit_isort();
    unit_searches();
    unit_mergesort();
    unit_clone();
    unit_max_min();
}