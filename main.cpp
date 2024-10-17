#include<stdio.h>
#include<stdlib.h>
#include<crtdbg.h>

#define DEBUG

typedef struct Array {
    int* data;
    size_t index;
    size_t maxSize;
} Array;;;



#define Array_BaseSize 16
#define Array_GrowthFactor 2

Array* Array_create(size_t size);
void   Array_destroy(Array* array);
void Array_insert(Array* array, int val);
void Array_increaseSize(Array* array);
void Array_decreaseSize(Array* array);
void Array_printData(Array* array);



Array* Array_create(size_t size) {
    Array* arr = (Array*)malloc(sizeof(Array) * size);
    arr->index = 0;
    arr->maxSize = Array_BaseSize;
    arr->data = (int*)malloc(sizeof(int) * Array_BaseSize);

    return arr;
}

void Array_destroy(Array* array) {
    free(array->data);
    free(array);
}


void Array_insert(Array* array, int val) {
    if (array->index == array->maxSize) {
        Array_increaseSize(array);
        Array_insert(array, val);
    }
    else {
        array->data[array->index++] = val;
    }
}

void Array_increaseSize(Array* array) {
    // create a newer array with size = original_size * growth_factor
    size_t newSize = (array->maxSize * Array_GrowthFactor);
    int* newDataArray = (int*)malloc(sizeof(int) * newSize);
    // copying old data from old array to newly created one
    for (int i = 0; i < array->index; i++) {
        newDataArray[i] = array->data[i];
    }

    array->maxSize = newSize;
    // de-allocating old data store (old array)
    free(array->data);
    array->data = newDataArray;
}

void Array_decreaseSize(Array* array) {
    // dividing size by growth factor
    size_t newArraySize = array->maxSize / Array_GrowthFactor;
    // creating a newer, smaller array:
    int* newerSmallerArray = (int*)malloc(sizeof(int) * newArraySize);
    // copying data from old array into newer one:
    for (int i = 0; i < newArraySize; i++) {
        newerSmallerArray[i] = array->data[i];
    }
    // deleting older array
    free(array->data);;
    array->data = newerSmallerArray;
}


void Array_printData(Array* array) {
    for (int i = 0; i < array->index; i++) {
        printf("%5d: %10d\n", i, array->data[i]);
    }
}

void main() {
    Array* myArray = Array_create(15);

    printf("array size: %d, current cursor: %d\n", myArray->maxSize, myArray->index);

    for (int i = 0; i < 20; i++) {
        Array_insert(myArray, i);
    }

    Array_printData(myArray);

    Array_destroy(myArray);

    _CrtDumpMemoryLeaks();
    return;
}
