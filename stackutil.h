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

int get_length(stack *s) {
    return s->head + 1;
}

int is_empty(stack *s)
{
    return s->head == -1;
}

void push(stack *s, void *value)
{
    if (s == NULL) {
        return;
    }

    if (s->head == s->capacity - 1)
    {
        int new_capacity = s->capacity *= 2;
        
        void **temp = (void **)realloc(s->items, new_capacity * sizeof(void *));
        if (temp == NULL) {
            return;
        }

        s->capacity = new_capacity;
        s->items = temp;
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