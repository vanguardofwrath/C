#ifndef stackutil
#define stackutil

#include <stdlib.h>

typedef struct
{
    void **items;
    int head;
    int capacity;
} stack;

stack *create_stack(int capacity)
{
    stack *s = (stack *)malloc(sizeof(stack));
    if (s == NULL)
    {
        return NULL;
    }

    s->items = (void **)malloc(capacity * sizeof(void *));
    if (s->items == NULL)
    {
        free(s);
        return NULL;
    }

    s->capacity = capacity;
    s->head = -1;
    return s;
}

int get_num_items(stack *s) {
    return s->head + 1;
}

int is_empty(stack *s)
{
    return s->head == -1;
}

int is_full(stack *s) {
    return s->head == s->capacity - 1;
}

void push(stack *s, void *value)
{
    if (s == NULL || is_full(s)) {
        return;
    }

    s->items[++s->head] = value;
}

void* pop(stack *s)
{
    if (is_empty(s))
    {
        return NULL;
    }

    return s->items[s->head--];
}

void* peek(stack *s)
{
    if (is_empty(s))
    {
        return NULL;
    }

    return s->items[s->head];
}

void free_stack(stack *s)
{
    if (s == NULL) {
        return;
    }

    free(s->items);
    free(s);
}

#endif