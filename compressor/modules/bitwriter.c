#include "bitwriter.h"

BitWriter create_bit_writer(FILE *file) {
    BitWriter bit_writer = {.file = file, .buffer = 0, .length = 0};
    return bit_writer;
}

void bit_writer_write(BitWriter *bit_writer, uint64_t bit_code, uint32_t bit_count) {
    bit_writer->buffer = (bit_writer->buffer << bit_count) | bit_code;
    bit_writer->length += bit_count;

    while(bit_writer->length >= 8) {
        bit_writer->length -= 8;
        uint8_t byte = (bit_writer->buffer >> bit_writer->length) & 0xFF;
        fputc(byte, bit_writer->file);
    }
}

void bit_writer_flush(BitWriter *bit_writer) {
    if (bit_writer->length > 0) {
        uint8_t byte = (bit_writer->buffer << (8 - bit_writer->length)) & 0xFF;
        fputc(byte, bit_writer->file);
        bit_writer->length = 0;
    }
}
