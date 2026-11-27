#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    FILE *to_decompress = fopen(argv[1], "rb");
    if (!to_decompress) {
        return EXIT_FAILURE;
    } 

    uint16_t *code_count;
    if (fread(code_count, sizeof(uint16_t), 1, to_decompress) == 0) {
        fclose(to_decompress);
        return EXIT_FAILURE;
    }

    

    return EXIT_SUCCESS;
}