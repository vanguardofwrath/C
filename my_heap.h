#ifndef MY_HEAP_H
#define MY_HEAP_H

#include <stdlib.h>

typedef struct MyHeapNode {
    void *value;
    struct MyHeapNode *left;
    struct MyHeapNode *right;
} MyHeapNode;

typedef struct {
    MyHeapNode **array;
    size_t length;
    size_t capacity;
} MyHeap;

MyHeap *create_my_heap();
void my_heap_insert(MyHeap *heap, void *value);

#define INITIAL_CAPACITY 16

MyHeap *create_my_heap() {
    MyHeap *my_heap = (MyHeap *)malloc(sizeof(MyHeap));
    if (!my_heap) {
        return NULL;
    }

    my_heap->array = (MyHeapNode **)malloc(sizeof(MyHeapNode *) * INITIAL_CAPACITY);
    if (!my_heap->array) {
        free(my_heap);
        return NULL;
    }

    my_heap->capacity = INITIAL_CAPACITY;
    my_heap->length = 0;
    return my_heap;
}

void my_heap_insert(MyHeap *heap, void *value) {
    
}

#endif