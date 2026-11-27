#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "modules/minheap.h"
#include "modules/bitwriter.h"

#define POSSIBLE_BYTE_VALUES_COUNT 256
#define BYTES_TO_READ_PER_CHUNK 1024
#define COMPRESSED_TO_CONCAT "_compressed.bin"

char *read_file(const char *path_to_file, uint64_t *out_size) {
    FILE *fPtr = fopen(path_to_file, "rb");
    if (!fPtr) {
        return NULL;
    }

    uint64_t capacity = BYTES_TO_READ_PER_CHUNK;
    uint8_t *data = (uint8_t *)malloc(capacity);
    if (!data) {
        fclose(fPtr);
        return NULL;
    }

    uint64_t bytes_read = fread(data, 1, BYTES_TO_READ_PER_CHUNK, fPtr);
    uint64_t total_bytes_read = bytes_read;

    while (bytes_read == BYTES_TO_READ_PER_CHUNK) {
        uint64_t new_capacity = capacity + BYTES_TO_READ_PER_CHUNK;

        uint8_t *expanded = (uint8_t *)realloc(data, new_capacity);
        if (!expanded) {
            free(data);
            fclose(fPtr);
            return NULL;
        }

        data = expanded;
        capacity = new_capacity;

        bytes_read = fread(data + total_bytes_read, 1, BYTES_TO_READ_PER_CHUNK, fPtr);
        total_bytes_read += bytes_read;
    }

    fclose(fPtr);

    if (total_bytes_read == 0) {
        free(data);
        return NULL;
    }

    uint8_t *shrunken = (uint8_t *)realloc(data, total_bytes_read);
    if (!shrunken) {
        free(data);
        return NULL;
    }

    *out_size = total_bytes_read;

    data = shrunken;
    return data;
}

typedef struct {
    uint64_t code;
    uint32_t length;
} PrefixCode;

void map_prefix_codes(MinHeapNode *node, uint64_t code, uint32_t length, PrefixCode *code_map) {
    if (min_heap_node_is_leaf(node)) {
        code_map[node->c].code = code;
        code_map[node->c].length = length;
        return;
    }

    map_prefix_codes(node->left, code << 1, length + 1, code_map);
    map_prefix_codes(node->right, (code << 1) | 1, length + 1, code_map);
}

char *get_compressed_file_name(const char *source) {
    uint64_t len_to_concat = strlen(COMPRESSED_TO_CONCAT);

    char *period = strrchr(source, '.');
    if (!period) {
        return NULL;
    }

    uint64_t length = period - source;

    char *string = malloc(length + len_to_concat + 1);
    if (!string) {
        return NULL;
    }

    memcpy(string, source, length);
    strcpy(string + length, COMPRESSED_TO_CONCAT);
    return string;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Not enough arguments!\n");
        return EXIT_FAILURE;
    }

    uint64_t *file_size;

    char *file_data = read_file(argv[1], file_size);
    if (!file_data) {
        printf("Failed to read file!\n");
        return EXIT_FAILURE;
    }

    MinHeap *min_heap = create_min_heap();
    if (!min_heap) {
        free(file_data);
        return EXIT_FAILURE;
    }

    uint64_t frequency_map[POSSIBLE_BYTE_VALUES_COUNT] = {0};
    for (uint64_t i = 0; i < *file_size; i++) {
        frequency_map[file_data[i]]++;
    }

    for (uint32_t i = 0; i < POSSIBLE_BYTE_VALUES_COUNT; i++) {
        if (frequency_map[i] > 0) {
            MinHeapNode *min_heap_node = create_min_heap_node(i, frequency_map[i]);
            if (!min_heap_node) {
                free(file_data);
                free_min_heap(min_heap);
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
            free(file_data);
            free_min_heap(min_heap);
            return EXIT_FAILURE;
        }

        merged->left = node1;
        merged->right = node2;
        min_heap_insert(min_heap, merged);
    }

    MinHeapNode *root = min_heap_extract_min(min_heap);
    free_min_heap(min_heap);

    PrefixCode code_map[POSSIBLE_BYTE_VALUES_COUNT] = {0};
    map_prefix_codes(root, 0, 0, code_map);

    char *file_name = get_compressed_file_name(argv[1]);

    FILE *compressed_file = fopen(file_name, "ab+");
    if (!compressed_file) {
        
        return EXIT_FAILURE;
    }
    free(file_name);
    
    BitWriter bit_writer = create_bit_writer(compressed_file);
    for (uint64_t i = 0; i < file_size; i++) {
        PrefixCode prefix_code = code_map[file_data[i]];
        bit_writer_write(&bit_writer, prefix_code.code, prefix_code.length);
    }
    bit_writer_flush(&bit_writer);
    fclose(compressed_file);

    free_min_heap_node(root);
    free(file_data);
    return EXIT_SUCCESS;
}