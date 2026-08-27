#ifndef custom_string
#define custom_string

#include <stdlib.h>
#include <stdio.h>
#include "strutil.h"

typedef struct
{
    char *data;
    int length;
    int capacity;
} string;

typedef struct {
    string **list;

} string_list;

string *create_string(const char *start_string)
{
    string *new_string = (string *)malloc(sizeof(string));
    if (!new_string)
    {
        return NULL;
    }

    if (!start_string)
    {
        new_string->length = 0;
        new_string->capacity = 2;

        char *temp = (char *)malloc(new_string->capacity * sizeof(char));
        if (!temp)
        {
            free(new_string);
            return NULL;
        }

        new_string->data = temp;
        new_string->data[0] = '\0';
        return new_string;
    }

    new_string->length = get_string_length(start_string);
    new_string->capacity = new_string->length + 1;

    char *string_copy = (char *)copy_string(start_string);
    if (!string_copy)
    {
        free(new_string);
        return NULL;
    }

    new_string->data = string_copy;
    return new_string;
}

void append_string(string *target, string *other)
{
    if (!target || !other)
    {
        return;
    }

    int new_length = target->length + other->length;

    if (new_length >= target->capacity)
    {
        int new_capacity = target->capacity * 2;

        if (new_capacity < new_length + 1)
        {
            new_capacity = new_length + 1;
        }

        char *temp = (char *)realloc(target->data, new_capacity * sizeof(char));
        if (!temp)
        {
            return;
        }

        target->capacity = new_capacity;
        target->data = temp;
    }

    for (int i = 0; i < other->length; i++)
    {
        target->data[target->length + i] = other->data[i];
    }

    target->length = new_length;
    target->data[target->length] = '\0';
}

void append_char(string *target, char c)
{
    if (!target)
    {
        return;
    }

    int new_length = target->length + 1;

    if (new_length + 1 > target->capacity)
    {
        int new_capacity = target->capacity * 2;

        if (new_capacity < new_length + 1)
        {
            new_capacity = new_length + 1;
        }

        char *temp = (char *)realloc(target->data, new_capacity * sizeof(char));
        if (!temp)
        {
            return;
        }

        target->capacity = new_capacity;
        target->data = temp;
    }

    target->data[target->length] = c;

    target->length = new_length;
    target->data[target->length] = '\0';
}

char *get_string(string *target) {
    if (!target) {
        return NULL;
    }
    
    return target->data;
}

void print_string(string *target)
{
    if (!target)
    {
        return;
    }

    printf(target->data);
}

void free_string(string *target)
{
    if (!target)
    {
        return;
    }

    free(target->data);
    free(target);
}

#endif