#ifndef MY_STACK
#define MY_STACK

#include <stdlib.h>

typedef struct
{
    double *items;
    int head;
    int capacity;
} DoubleStack;

DoubleStack *create_double_stack(int capacity)
{
    DoubleStack *s = (DoubleStack *)malloc(sizeof(DoubleStack));
    if (s == NULL)
    {
        return NULL;
    }

    s->items = (double *)malloc(capacity * sizeof(double));
    if (s->items == NULL)
    {
        free(s);
        return NULL;
    }

    s->capacity = capacity;
    s->head = -1;
    return s;
}

int double_stack_count(DoubleStack *s)
{
    return s->head + 1;
}

int double_stack_is_empty(DoubleStack *s)
{
    return s->head == -1;
}

int double_stack_is_full(DoubleStack *s)
{
    return s->head == s->capacity - 1;
}

void double_stack_push(DoubleStack *s, double value)
{
    if (s == NULL || double_stack_is_full(s))
    {
        return;
    }

    s->items[++s->head] = value;
}

double double_stack_pop(DoubleStack *s)
{
    if (double_stack_is_empty(s))
    {
        return 0;
    }

    return s->items[s->head--];
}

double double_stack_peek(DoubleStack *s)
{
    if (double_stack_is_empty(s))
    {
        return 0;
    }

    return s->items[s->head];
}

void free_double_stack(DoubleStack *s)
{
    if (s == NULL)
    {
        return;
    }

    free(s->items);
    free(s);
}

typedef struct
{
    char *items;
    int head;
    int capacity;
} CharStack;

CharStack *create_char_stack(int capacity)
{
    CharStack *s = (CharStack *)malloc(sizeof(CharStack));
    if (s == NULL)
    {
        return NULL;
    }

    s->items = (char *)malloc(capacity * sizeof(char));
    if (s->items == NULL)
    {
        free(s);
        return NULL;
    }

    s->capacity = capacity;
    s->head = -1;
    return s;
}

int char_stack_count(CharStack *s)
{
    return s->head + 1;
}

int char_stack_is_empty(CharStack *s)
{
    return s->head == -1;
}

int char_stack_is_full(CharStack *s)
{
    return s->head == s->capacity - 1;
}

void char_stack_push(CharStack *s, char value)
{
    if (s == NULL || char_stack_is_full(s))
    {
        return;
    }

    s->items[++s->head] = value;
}

int char_stack_pop(CharStack *s)
{
    if (char_stack_is_empty(s))
    {
        return 0;
    }

    return s->items[s->head--];
}

int char_stack_peek(CharStack *s)
{
    if (char_stack_is_empty(s))
    {
        return 0;
    }

    return s->items[s->head];
}

void free_char_stack(CharStack *s)
{
    if (s == NULL)
    {
        return;
    }

    free(s->items);
    free(s);
}

#endif