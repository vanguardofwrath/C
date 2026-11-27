#ifndef BIT_WRITER_H
#define BIT_WRITER_H

#include <stdio.h>
#include <stdint.h>

typedef struct {
    FILE *file;
    uint64_t buffer;
    uint32_t length;
} BitWriter;

BitWriter create_bit_writer(FILE *file);
void bit_writer_write(BitWriter *bit_writer, uint64_t bit_code, uint32_t bit_count);
void bit_writer_flush(BitWriter *bit_writer);

#endif