#ifndef stackutil
#define stackutil

#include <stdlib.h>

typedef struct
{
    double *items;
    int head;
    int capacity;
} double_stack;

double_stack *create_double_stack(int capacity)
{
    double_stack *s = (double_stack *)malloc(sizeof(double_stack));
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

int double_stack_count(double_stack *s)
{
    return s->head + 1;
}

int double_stack_is_empty(double_stack *s)
{
    return s->head == -1;
}

int double_stack_is_full(double_stack *s)
{
    return s->head == s->capacity - 1;
}

void double_stack_push(double_stack *s, double value)
{
    if (s == NULL || double_stack_is_full(s))
    {
        return;
    }

    s->items[++s->head] = value;
}

double double_stack_pop(double_stack *s)
{
    if (double_stack_is_empty(s))
    {
        return 0;
    }

    return s->items[s->head--];
}

double double_stack_peek(double_stack *s)
{
    if (double_stack_is_empty(s))
    {
        return 0;
    }

    return s->items[s->head];
}

void free_double_stack(double_stack *s)
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
} char_stack;

char_stack *create_char_stack(int capacity)
{
    char_stack *s = (char_stack *)malloc(sizeof(char_stack));
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

int char_stack_count(char_stack *s)
{
    return s->head + 1;
}

int char_stack_is_empty(char_stack *s)
{
    return s->head == -1;
}

int char_stack_is_full(char_stack *s)
{
    return s->head == s->capacity - 1;
}

void char_stack_push(char_stack *s, char value)
{
    if (s == NULL || char_stack_is_full(s))
    {
        return;
    }

    s->items[++s->head] = value;
}

int char_stack_pop(char_stack *s)
{
    if (char_stack_is_empty(s))
    {
        return 0;
    }

    return s->items[s->head--];
}

int char_stack_peek(char_stack *s)
{
    if (char_stack_is_empty(s))
    {
        return 0;
    }

    return s->items[s->head];
}

void free_char_stack(char_stack *s)
{
    if (s == NULL)
    {
        return;
    }

    free(s->items);
    free(s);
}

#endif