#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define PATH_TO_FILE "C:\\Users\\Netanel Ojukwu\\Documents\\Projects\\C\\test_file.txt"
#define NUM_BYTE_VALUES 256
#define BYTES_PER_CHUNK 1024
#define INITIAL_HEAP_CAPACITY 16

typedef struct MinHeapNode {
    uint8_t c;
    uint64_t frequency;
    struct MinHeapNode *left;
    struct MinHeapNode *right;
} MinHeapNode;

void swap_min_heap_nodes(MinHeapNode **node1, MinHeapNode **node2) {
    MinHeapNode *temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

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

void min_heap_node_free(MinHeapNode *min_heap_node) {
    free(min_heap_node);
}

typedef struct {
    MinHeapNode **array;
    uint64_t length;
    uint64_t capacity;
} MinHeap;

uint64_t parent_index(uint64_t index) { return (index - 1) / 2; }
uint64_t left_index(uint64_t index) { return 2 * index + 1; }
uint64_t right_index(uint64_t index) { return 2 * index + 2; }

MinHeap *create_min_heap() {
    MinHeap *min_heap = (MinHeap *)malloc(sizeof(MinHeap));
    if (!min_heap) {
        return NULL;
    }

    min_heap->array = (MinHeapNode **)malloc(sizeof(MinHeapNode *) * INITIAL_HEAP_CAPACITY);
    if (!min_heap->array) {
        free(min_heap);
        return NULL;
    }

    min_heap->length = 0;
    min_heap->capacity = INITIAL_HEAP_CAPACITY;
    return min_heap;
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

void min_heap_free(MinHeap *min_heap) {
    for (uint64_t i = 0; i < min_heap->length; i++) {
        min_heap_node_free(min_heap->array[i]);
    }
    free(min_heap);
}

typedef struct {
    uint8_t *data;
    uint64_t size;
} FileInfo;

FileInfo read_file(const char *path_to_file) {
    FileInfo file_info = { .data = NULL, .size = 0 };

    FILE *file = fopen(PATH_TO_FILE, "rb");
    if (!file) {
        return file_info;
    }

    uint64_t capacity = BYTES_PER_CHUNK;

    uint8_t *data = malloc(capacity);
    if (!data) {
        fclose(file);
        return file_info;
    }

    uint64_t bytes_read = fread(data, 1, BYTES_PER_CHUNK, file);
    uint64_t total_bytes_read = bytes_read;

    while (bytes_read == BYTES_PER_CHUNK) {
        uint64_t new_capacity = capacity + BYTES_PER_CHUNK;

        uint8_t *expanded = realloc(data, new_capacity);
        if (!expanded) {
            free(data);
            fclose(file);
            return file_info;
        }

        data = expanded;
        capacity = new_capacity;

        bytes_read = fread(data + total_bytes_read, 1, BYTES_PER_CHUNK, file);
        total_bytes_read += bytes_read;
    }

    fclose(file);

    uint8_t *shrunken = realloc(data, total_bytes_read + 1);
    if (!shrunken) {
        free(data);;
        return file_info;
    }

    data = shrunken;

    file_info.data = data;
    file_info.size = total_bytes_read;
    return file_info;
}

void free_file_info(FileInfo file_info) {
    free(file_info.data);
}

int main(int argc, char **argv)
{
    FileInfo file_info = read_file(PATH_TO_FILE);
    if (!file_info.data || file_info.size == 0) {
        return EXIT_FAILURE;
    }

    uint64_t *frequency_list = calloc(NUM_BYTE_VALUES, sizeof(uint64_t));
    if (!frequency_list) {
        free_file_info(file_info);
        return EXIT_FAILURE;
    }

    MinHeap *min_heap = create_min_heap();
    if (!min_heap) {
        free_file_info(file_info);
        free(frequency_list);
        return EXIT_FAILURE;
    }

    for (uint64_t i = 0; i < file_info.size; i++) {
        frequency_list[file_info.data[i]]++;
    }

    for (uint16_t i = 0; i < NUM_BYTE_VALUES; i++) {
        if (frequency_list[i] > 0) {
            MinHeapNode *min_heap_node = create_min_heap_node(i, frequency_list[i]);
            if (!min_heap_node) {
                free_file_info(file_info);
                free(frequency_list);
                min_heap_free(min_heap);
                return EXIT_FAILURE;
            }

            min_heap_insert(min_heap, min_heap_node);
        }
    }

    while(min_heap->length > 1) {
        MinHeapNode *node1 = min_heap_extract_min(min_heap);
        MinHeapNode *node2 = min_heap_extract_min(min_heap);

        MinHeapNode *merged = create_min_heap_node('\0', node1->frequency + node2->frequency);
        if (!merged) {
            min_heap_node_free(node1);
            min_heap_node_free(node2);
            free_file_info(file_info);
            free(frequency_list);
            min_heap_free(min_heap);
            return EXIT_FAILURE;
        }

        merged->c = '\0';
        merged->frequency = node1->frequency + node2->frequency;
        min_heap_insert(min_heap, merged);

        free(node1);
        free(node2);
    }

    free_file_info(file_info);
    free(frequency_list);
    min_heap_free(min_heap);
    return EXIT_SUCCESS;
}