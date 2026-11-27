#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <stdint.h>

typedef struct MinHeapNode {
    uint8_t c;
    uint64_t frequency;
    struct MinHeapNode *left;
    struct MinHeapNode *right;
} MinHeapNode;

typedef struct {
    MinHeapNode **array;
    uint64_t length;
    uint64_t capacity;
} MinHeap;

MinHeapNode *create_min_heap_node(uint8_t c, uint64_t frequency);
bool min_heap_node_is_leaf(MinHeapNode *min_heap_node);
void free_min_heap_node(MinHeapNode *min_heap_node);

MinHeap *create_min_heap();
void min_heap_insert(MinHeap *min_heap, MinHeapNode *min_heap_node);
MinHeapNode *min_heap_extract_min(MinHeap *min_heap);
void min_heap_print(MinHeap *min_heap);
void free_min_heap(MinHeap *min_heap);

#endif