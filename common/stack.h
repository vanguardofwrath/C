#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    double *items;
    uint64_t head;
    uint64_t capacity;
} DoubleStack;

typedef struct
{
    char *items;
    uint64_t head;
    uint64_t capacity;
} CharStack;

DoubleStack *create_double_stack(uint64_t capacity);
uint64_t double_stack_count(DoubleStack *stack);
bool double_stack_is_empty(DoubleStack *stack);
bool double_stack_is_full(DoubleStack *stack);
void double_stack_push(DoubleStack *stack, double value);
double double_stack_pop(DoubleStack *stack);
double double_stack_peek(DoubleStack *stack);
void double_stack_free(DoubleStack *stack);

CharStack *create_char_stack(uint64_t capacity);
uint64_t char_stack_count(CharStack *stack);
bool char_stack_is_empty(CharStack *stack);
bool char_stack_is_full(CharStack *stack);
void char_stack_push(CharStack *stack, char value);
int char_stack_pop(CharStack *stack);
int char_stack_peek(CharStack *stack);
void char_stack_free(CharStack *stack);

#endif