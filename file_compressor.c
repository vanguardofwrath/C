#include <stdio.h>
#include <stdlib.h>

#include "my_string.h"

#define FILE_TO_COMPRESS "C:\\Users\\Netanel Ojukwu\\Documents\\Projects\\C\\test_file.txt"
#define BYTE_VALUES_COUNT 256

long get_file_size(FILE *file) {
    if(fseek(file, 0, SEEK_END) != 0) {
        return -1;
    }
    
    return ftell(file);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    FILE *file = fopen(FILE_TO_COMPRESS, "rb");
    if (!file) {
        return EXIT_FAILURE;
    }

    long size = get_file_size(file);
    if (size < 0) {
        fclose(file);
        return EXIT_FAILURE;
    }

    unsigned char *char_list = malloc(size);
    if (!char_list) {
        fclose(file);
        return EXIT_FAILURE;
    }

    fread(char_list, 1, size, file);

    size_t *frequency_list = calloc(BYTE_VALUES_COUNT, sizeof(size_t));
    if (!frequency_list) {
        free(char_list);
        fclose(file);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < size; i++) {
        frequency_list[char_list[i]]++;
    }

    return EXIT_SUCCESS;
}  