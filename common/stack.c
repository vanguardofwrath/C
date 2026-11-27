#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

DoubleStack *create_double_stack(uint64_t capacity)
{
    DoubleStack *stack = (DoubleStack *)malloc(sizeof(DoubleStack));
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

uint64_t double_stack_count(DoubleStack *stack)
{
    return stack->head + 1;
}

bool double_stack_is_empty(DoubleStack *stack)
{
    return stack->head == -1;
}

bool double_stack_is_full(DoubleStack *stack)
{
    return stack->head == stack->capacity - 1;
}

void double_stack_push(DoubleStack *stack, double value)
{
    if (double_stack_is_full(stack))
    {
        int new_capacity = stack->capacity * 2;

        double *temp = (double *)realloc(stack->items, new_capacity * sizeof(double));
        if (!temp)
        {
            return;
        }

        stack->items = temp;
        stack->capacity = new_capacity;
    }

    stack->items[++stack->head] = value;
}

double double_stack_pop(DoubleStack *stack)
{
    if (double_stack_is_empty(stack))
    {
        return 0;
    }

    return stack->items[stack->head--];
}

double double_stack_peek(DoubleStack *stack)
{
    if (double_stack_is_empty(stack))
    {
        return 0;
    }

    return stack->items[stack->head];
}

void double_stack_free(DoubleStack *stack)
{
    free(stack->items);
    free(stack);
}

CharStack *create_char_stack(uint64_t capacity)
{
    CharStack *stack = (CharStack *)malloc(sizeof(CharStack));
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

uint64_t char_stack_count(CharStack *stack)
{
    return stack->head + 1;
}

bool char_stack_is_empty(CharStack *stack)
{
    return stack->head == -1;
}

bool char_stack_is_full(CharStack *stack)
{
    return stack->head == stack->capacity - 1;
}

void char_stack_push(CharStack *stack, char value)
{
    if (char_stack_is_full(stack))
    {
        int new_capacity = stack->capacity * 2;

        char *temp = (char *)realloc(stack->items, new_capacity * sizeof(char));
        if (!temp)
        {
            return;
        }

        stack->items = temp;
        stack->capacity = new_capacity;
    }

    stack->items[++stack->head] = value;
}

int char_stack_pop(CharStack *stack)
{
    if (char_stack_is_empty(stack))
    {
        return 0;
    }

    return stack->items[stack->head--];
}

int char_stack_peek(CharStack *stack)
{
    if (char_stack_is_empty(stack))
    {
        return 0;
    }

    return stack->items[stack->head];
}

void char_stack_free(CharStack *stack)
{
    free(stack->items);
    free(stack);
}