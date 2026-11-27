#include <stdio.h>
#include <stdlib.h>

#include "minheap.h"

#define INITIAL_MIN_HEAP_CAPACITY 64

MinHeapNode *create_min_heap_node(uint8_t c, uint64_t frequency) {
    MinHeapNode *min_heap_node = (MinHeapNode *)malloc(sizeof(MinHeapNode));
    if (!min_heap_node) {
        return NULL;
    }

    min_heap_node->c = c;
    min_heap_node->frequency = frequency;
    min_heap_node->left = NULL;
    min_heap_node->right = NULL;
    return min_heap_node;
}

static void swap_min_heap_nodes(MinHeapNode **node1, MinHeapNode **node2) {
    MinHeapNode *temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

bool min_heap_node_is_leaf(MinHeapNode *min_heap_node) {
    return !min_heap_node->left && !min_heap_node->right;
}

void free_min_heap_node(MinHeapNode *min_heap_node) {
    if (!min_heap_node) {
        return;
    }

    free_min_heap_node(min_heap_node->left);
    free_min_heap_node(min_heap_node->right);
    free(min_heap_node);
}

MinHeap *create_min_heap() {
    MinHeap *min_heap = (MinHeap *)malloc(sizeof(MinHeap));
    if (!min_heap) {
        return NULL;
    }

    min_heap->array = (MinHeapNode **)malloc(sizeof(MinHeapNode *) * INITIAL_MIN_HEAP_CAPACITY);
    if (!min_heap->array) {
        free(min_heap);
        return NULL;
    }

    min_heap->length = 0;
    min_heap->capacity = INITIAL_MIN_HEAP_CAPACITY;
    return min_heap;
}

static uint64_t parent_index(uint64_t index) {
     return (index - 1) / 2; 
}

static uint64_t left_index(uint64_t index) { 
    return 2 * index + 1; 
}

static uint64_t right_index(uint64_t index) { 
    return 2 * index + 2; 
}

void min_heap_insert(MinHeap *min_heap, MinHeapNode *min_heap_node) {
    if (min_heap->length == min_heap->capacity) {
        uint64_t new_capacity = min_heap->capacity * 2;

        MinHeapNode **temp = (MinHeapNode **)realloc(min_heap->array, sizeof(MinHeapNode *) * new_capacity);
        if (!temp) {
            return;
        }

        min_heap->array = temp;
        min_heap->capacity = new_capacity;
    }

    min_heap->array[min_heap->length++] = min_heap_node;

    uint64_t index = min_heap->length - 1;
    while (index > 0 && min_heap->array[index]->frequency < min_heap->array[parent_index(index)]->frequency) {
        uint64_t parent = parent_index(index);
        swap_min_heap_nodes(&min_heap->array[index], &min_heap->array[parent]);
        index = parent;
    }
}

MinHeapNode *min_heap_extract_min(MinHeap *min_heap) {
    if (min_heap->length == 0) {
        return NULL;
    }

    MinHeapNode *to_extract = min_heap->array[0];

    min_heap->array[0] = min_heap->array[min_heap->length - 1];
    min_heap->length--;

    uint64_t index = 0;
    while (left_index(index) < min_heap->length) {
        uint64_t left = left_index(index);
        uint64_t right = right_index(index);

        uint64_t smallest = left;
        if (right < min_heap->length && min_heap->array[right]->frequency < min_heap->array[left]->frequency) {
            smallest = right;
        }

        if (min_heap->array[index]->frequency <= min_heap->array[smallest]->frequency) {
            break;
        }

        swap_min_heap_nodes(&min_heap->array[index], &min_heap->array[smallest]);
        index = smallest;
    }

    return to_extract;
}

void min_heap_print(MinHeap *min_heap) {
    if (min_heap->length == 0) {
        return;
    }

    for (uint64_t i = 0; i < min_heap->length; i++) {
        MinHeapNode *min_heap_node = min_heap->array[i];
        printf("[%zu] c:%c freq:%zu\n", i, min_heap_node->c, min_heap_node->frequency);
    }
}

void free_min_heap(MinHeap *min_heap) {
    for (uint64_t i = 0; i < min_heap->length; i++) {
        free_min_heap_node(min_heap->array[i]);
    }

    free(min_heap->array);
    free(min_heap);
}