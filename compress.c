#include <stdio.h>
#include <stdlib.h>

#include "my_string.h"
#include "my_hash_map.h"

#define PATH_TO_FILE "C:\\Users\\Netanel Ojukwu\\Documents\\Projects\\C\\test_file.txt"
#define BYTES_PER_CHUNK 1024

char *read_file(FILE *file) {
    size_t capacity = BYTES_PER_CHUNK;

    char *buffer = malloc(capacity);
    if (!buffer) {
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, BYTES_PER_CHUNK, file);
    size_t total_bytes_read = bytes_read;

    while (bytes_read == BYTES_PER_CHUNK) {
        size_t new_capacity = capacity + BYTES_PER_CHUNK;

        char *expanded = realloc(buffer, new_capacity);
        if (!expanded) {
            free(buffer);
            return NULL;
        }

        buffer = expanded;
        capacity = new_capacity;

        bytes_read = fread(buffer + total_bytes_read, 1, BYTES_PER_CHUNK, file);
        total_bytes_read += bytes_read;
    }

    char *shrunken = realloc(buffer, total_bytes_read + 1);
    if (!shrunken) {
        free(buffer);
        return NULL;
    }

    buffer = shrunken;
    buffer[total_bytes_read] = '\0';
    return buffer;
}

int main(int argc, char **argv)
{
    FILE *file = fopen(PATH_TO_FILE, "rb");
    if (!file) {
        return EXIT_FAILURE;
    }

    char *buffer = read_file(file);
    if (!buffer) {
        fclose(file);
        return EXIT_FAILURE;
    }

    size_t *frequency_list = calloc(256, sizeof(size_t));
    if (!frequency_list) {
        free(buffer);
        fclose(file);
        return EXIT_FAILURE;
    }

    char *bPtr = buffer;
    while (*bPtr != '\0') {
        frequency_list[*bPtr++]++;
    }

    return EXIT_SUCCESS;
}