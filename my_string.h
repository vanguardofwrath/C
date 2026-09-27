#ifndef MY_STRING
#define MY_STRING

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <regex.h>

typedef struct
{
    char *data;
    int length;
    int capacity;
} String;

String *create_string(const char *source)
{
    String *string = (String *)malloc(sizeof(String));
    if (!string)
    {
        return NULL;
    }

    if (!source)
    {
        string->length = 0;
        string->capacity = 2;

        char *temp = (char *)malloc(string->capacity * sizeof(char));
        if (!temp)
        {
            free(string);
            return NULL;
        }

        string->data = temp;
        string->data[0] = '\0';
        return string;
    }

    string->length = strlen(source);
    string->capacity = string->length + 1;

    char *copy = malloc(string->capacity * sizeof(char));
    if (!copy)
    {
        free(string);
        return NULL;
    }

    strcpy(copy, source);

    string->data = copy;
    return string;
}

void append_string(String *string, String *other)
{
    if (!string || !other)
    {
        return;
    }

    int new_length = string->length + other->length;

    if (new_length >= string->capacity)
    {
        int new_capacity = string->capacity * 2;

        while (new_capacity < new_length + 1)
        {
            new_capacity *= 2;
        }

        char *temp = (char *)realloc(string->data, new_capacity * sizeof(char));
        if (!temp)
        {
            return;
        }

        string->capacity = new_capacity;
        string->data = temp;
    }

    memcpy(string->data + string->length, other->data, other->length);

    string->length = new_length;
    string->data[string->length] = '\0';
}

void append_c_string(String *string, const char *other)
{
    if (!string || !other)
    {
        return;
    }

    int other_length = strlen(other);

    int new_length = string->length + other_length;

    if (new_length >= string->capacity)
    {
        int new_capacity = string->capacity * 2;

        while (new_capacity < new_length + 1)
        {
            new_capacity *= 2;
        }

        char *temp = (char *)realloc(string->data, new_capacity * sizeof(char));
        if (!temp)
        {
            return;
        }

        string->capacity = new_capacity;
        string->data = temp;
    }

    memcpy(string->data + string->length, other, other_length);

    string->length = new_length;
    string->data[string->length] = '\0';
}

void remove_substring(String *string, String *substring) {
    if (!string || !substring) {
        return;
    }
    
    if (substring->length == 0 || substring->length > string->length) {
        return;
    }

    char* first_occurence = strstr(string->data, substring->data);
    if (!first_occurence)
    {
        return;
    }

    size_t start_index = first_occurence - string->data;
    size_t end_index = start_index + substring->length;

    memmove(&string->data[start_index], &string->data[end_index], string->length - end_index + 1);

    string->length -= substring->length;
}

void append_char(String *string, char c)
{
    if (!string)
    {
        return;
    }

    int new_length = string->length + 1;

    if (new_length + 1 >= string->capacity)
    {
        int new_capacity = string->capacity * 2;

        char *temp = (char *)realloc(string->data, new_capacity * sizeof(char));
        if (!temp)
        {
            return;
        }

        string->capacity = new_capacity;
        string->data = temp;
    }

    string->data[string->length] = c;

    string->length = new_length;
    string->data[string->length] = '\0';
}

void print_string(String *string)
{
    if (!string)
    {
        return;
    }

    printf("%s\n", string->data);
}

void free_string(String *string)
{
    if (!string)
    {
        return;
    }

    free(string->data);
    free(string);
}

typedef struct {
    String **strings;
    int capacity;
    int length;
} StringList;

StringList *create_string_list(int capacity) {
    StringList *new_list = (StringList *)malloc(sizeof(StringList));
    if (!new_list) {
        return NULL;
    }

    new_list->strings = (String **)malloc(capacity * sizeof(String *));
    if (!new_list->strings) {
        free(new_list);
        return NULL;
    }

    new_list->capacity = capacity;
    new_list->length = 0;
    return new_list;
}

void append_string_to_list(StringList *string_list, String *string) {
    if (!string_list || !string) {
        return;
    }

    if (string_list->length == string_list->capacity) {
        int new_capacity = string_list->capacity * 2;

        String **temp = (String **)realloc(string_list->strings, new_capacity * sizeof(String *));
        if (!temp) {
            return;
        }

        string_list->strings = temp;
        string_list->capacity = new_capacity;
    }

    string_list->strings[string_list->length++] = string;
}

void append_c_string_to_list(StringList *string_list, const char* c_string) {
    if (!string_list || !c_string) {
        return;
    }

    String *string = create_string(c_string);
    if (!string) {
        return;
    }

    append_string_to_list(string_list, string);
}

void free_string_list(StringList *string_list) {
    if (!string_list) {
        return;
    }

    for (int i = 0; i < string_list->length; i++) {
        free_string(string_list->strings[i]);
    }

    free(string_list->strings);
    free(string_list);
}

#endif