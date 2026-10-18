#ifndef MY_DICTIONARY_H
#define MY_DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *items;
    size_t length;
    size_t capacity;
} MyDictionary;

MyDictionary *create_my_dictionary(size_t length);
void my_dictionary_add(MyDictionary *dictionary, const char *key, char value);
void my_dictionary_remove(MyDictionary *dictionary, const char *key);
void my_dictionary_free(MyDictionary *dictionary);

// --------------------------------------------------------------------------------------

static size_t djb2_hash(const char *string)
{
    size_t hash = 5381;
    int c;

    while ((c = *string++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

// --------------------------------------------------------------------------------------

MyDictionary *create_my_dictionary(size_t capacity)
{
    MyDictionary *dictionary = (MyDictionary *)malloc(sizeof(MyDictionary));
    if (!dictionary)
    {
        return NULL;
    }

    dictionary->items = (char *)malloc(sizeof(char) * capacity);
    if (!dictionary->items)
    {
        free(dictionary);
        return NULL;
    }

    dictionary->capacity = capacity;
    dictionary->length = 0;
    return dictionary;
}

void my_dictionary_get(MyDictionary *dictionary, const char *key)
{
    size_t hash_code = djb2_hash(key);
}

void my_dictionary_add(MyDictionary *dictionary, const char *key, char value)
{
    size_t hash_code = djb2_hash(key);
}

void my_dictionary_remove(MyDictionary *dictionary, const char *key)
{
}

void my_dictionary_free(MyDictionary *dictionary)
{
}

#endif