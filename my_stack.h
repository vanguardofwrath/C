#ifndef MY_STACK_H
#define MY_STACK_H

#include <stdbool.h>

typedef struct
{
    double *items;
    int head;
    int capacity;
} MyDoubleStack;

typedef struct
{
    char *items;
    int head;
    int capacity;
} MyCharStack;

MyDoubleStack *create_my_double_stack(int capacity);
int my_double_stack_count(MyDoubleStack *stack);
bool my_double_stack_is_empty(MyDoubleStack *stack);
bool my_double_stack_is_full(MyDoubleStack *stack);
void my_double_stack_push(MyDoubleStack *stack, double value);
double my_double_stack_pop(MyDoubleStack *stack);
double my_double_stack_peek(MyDoubleStack *stack);
void my_double_stack_free(MyDoubleStack *stack);

MyCharStack *create_my_char_stack(int capacity);
int my_char_stack_count(MyCharStack *stack);
bool my_char_stack_is_empty(MyCharStack *stack);
bool my_char_stack_is_full(MyCharStack *stack);
void my_char_stack_push(MyCharStack *stack, char value);
int my_char_stack_pop(MyCharStack *stack);
int my_char_stack_peek(MyCharStack *stack);
void my_char_stack_free(MyCharStack *stack);

#endif