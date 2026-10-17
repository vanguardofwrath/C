#ifndef MY_STACK_H
#define MY_STACK_H

#include <stdio.h>
#include <stdlib.h>
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

// --------------------------------------------------------------------------------------

MyDoubleStack *create_my_double_stack(int capacity)
{
    MyDoubleStack *stack = (MyDoubleStack *)malloc(sizeof(MyDoubleStack));
    if (stack == NULL)
    {
        return NULL;
    }

    stack->items = (double *)malloc(capacity * sizeof(double));
    if (stack->items == NULL)
    {
        free(stack);
        return NULL;
    }

    stack->capacity = capacity;
    stack->head = -1;
    return stack;
}

int my_double_stack_count(MyDoubleStack *stack)
{
    return stack->head + 1;
}

bool my_double_stack_is_empty(MyDoubleStack *stack)
{
    return stack->head == -1;
}

bool my_double_stack_is_full(MyDoubleStack *stack)
{
    return stack->head == stack->capacity - 1;
}

void my_double_stack_push(MyDoubleStack *stack, double value)
{
    if (stack == NULL)
    {
        return;
    }

    if (my_double_stack_is_full(stack)) {
        int new_capacity = stack->capacity * 2;

        double *temp = (double *)realloc(stack->items, new_capacity * sizeof(double));
        if (!temp) {
            return;
        }

        stack->items = temp;
        stack->capacity = new_capacity;
    }

    stack->items[++stack->head] = value;
}

double my_double_stack_pop(MyDoubleStack *stack)
{
    if (my_double_stack_is_empty(stack))
    {
        return 0;
    }

    return stack->items[stack->head--];
}

double my_double_stack_peek(MyDoubleStack *stack)
{
    if (my_double_stack_is_empty(stack))
    {
        return 0;
    }

    return stack->items[stack->head];
}

void my_double_stack_free(MyDoubleStack *stack)
{
    if (stack == NULL)
    {
        return;
    }

    free(stack->items);
    free(stack);
}

MyCharStack *create_my_char_stack(int capacity)
{
    MyCharStack *stack = (MyCharStack *)malloc(sizeof(MyCharStack));
    if (stack == NULL)
    {
        return NULL;
    }

    stack->items = (char *)malloc(capacity * sizeof(char));
    if (stack->items == NULL)
    {
        free(stack);
        return NULL;
    }

    stack->capacity = capacity;
    stack->head = -1;
    return stack;
}

int my_char_stack_count(MyCharStack *stack)
{
    return stack->head + 1;
}

bool my_char_stack_is_empty(MyCharStack *stack)
{
    return stack->head == -1;
}

bool my_char_stack_is_full(MyCharStack *stack)
{
    return stack->head == stack->capacity - 1;
}

void my_char_stack_push(MyCharStack *stack, char value)
{
    if (stack == NULL)
    {
        return;
    }

    if (my_char_stack_is_full(stack)) {
        int new_capacity = stack->capacity * 2;

        char *temp = (char *)realloc(stack->items, new_capacity * sizeof(char));
        if (!temp) {
            return;
        }

        stack->items = temp;
        stack->capacity = new_capacity;
    }

    stack->items[++stack->head] = value;
}

int my_char_stack_pop(MyCharStack *stack)
{
    if (my_char_stack_is_empty(stack))
    {
        return 0;
    }

    return stack->items[stack->head--];
}

int my_char_stack_peek(MyCharStack *stack)
{
    if (my_char_stack_is_empty(stack))
    {
        return 0;
    }

    return stack->items[stack->head];
}

void my_char_stack_free(MyCharStack *stack)
{
    if (stack == NULL)
    {
        return;
    }

    free(stack->items);
    free(stack);
}

#endif