#ifndef MY_HASH_MAP_H
#define MY_HASH_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_linked_list.h"

typedef struct
{
    MyListNode **buckets;
    size_t length;
    size_t capacity;
} MyHashMap;

typedef struct
{
    char *key;
    void *value;
} HashMapItem;

MyHashMap *create_my_hash_map();
void my_hash_map_set(MyHashMap *hash_map, char *key, void *value);
void *my_hash_map_get(MyHashMap *hashmap, char *key);
void my_hash_map_remove(MyHashMap *hash_map, char *key);
void my_hash_map_free(MyHashMap *hash_map);

HashMapItem *create_hash_map_item(char *key, void *value);
void hash_map_item_free(HashMapItem *item);

// --------------------------------------------------------------------------------------

static size_t djb2_hash(char *string)
{
    size_t hash = 5381;

    int c;
    while ((c = *string++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

static HashMapItem *search_item(MyListNode *bucket, size_t hash_code, char *key)
{
    while (bucket)
    {
        HashMapItem *item = (HashMapItem *)(bucket->value);
        if (strcmp(item->key, key) == 0)
        {
            return item;
        }

        bucket = bucket->next;
    }

    return NULL;
}

static bool remove_item(MyListNode **bucket, size_t hash_code, char *key)
{
    while (*bucket)
    {
        HashMapItem *item = (HashMapItem *)(*bucket)->value;
        if (strcmp(item->key, key) == 0)
        {
            MyListNode *to_remove = *bucket;
            *bucket = to_remove->next;
            hash_map_item_free(item);
            free(to_remove);
            return true;
        }
        
        bucket = &((*bucket)->next);
    }
    return false;
}

// --------------------------------------------------------------------------------------

HashMapItem *create_hash_map_item(char *key, void *value) {
    HashMapItem *item = (HashMapItem *)malloc(sizeof(HashMapItem));
    if (!item) {
        return NULL;
    }

    item->key = strdup(key);
    if (!item->key) {
        free(item);
        return NULL;
    }

    item->value = value;
    return item;
}

void hash_map_item_free(HashMapItem *item) {
    free(item->key);
    free(item->value);
    free(item);
}

// --------------------------------------------------------------------------------------

#define DEFAULT_CAPACITY 16

MyHashMap *create_my_hash_map()
{
    MyHashMap *hash_map = (MyHashMap *)malloc(sizeof(MyHashMap));
    if (!hash_map)
    {
        return NULL;
    }

    hash_map->buckets = (MyListNode **)calloc(DEFAULT_CAPACITY, sizeof(MyListNode *));
    if (!hash_map->buckets)
    {
        free(hash_map);
        return NULL;
    }

    hash_map->capacity = DEFAULT_CAPACITY;
    hash_map->length = 0;
    return hash_map;
}

void my_hash_map_set(MyHashMap *hash_map, char *key, void *value)
{
    size_t hash_code = djb2_hash(key);
    size_t index = hash_code % hash_map->capacity;
    MyListNode **bucket = &hash_map->buckets[index];

    HashMapItem *existing = search_item(*bucket, hash_code, key);
    if (existing)
    {
        free(existing->value);

        existing->value = value;
        return;
    }

    HashMapItem *item = create_hash_map_item(key, value);
    if (!item)
    {
        return;
    }

    my_linked_list_push(bucket, item);
    hash_map->length++;
}

void *my_hash_map_get(MyHashMap *hash_map, char *key)
{
    size_t hash_code = djb2_hash(key);
    size_t index = hash_code % hash_map->capacity;
    MyListNode *bucket = hash_map->buckets[index];
    HashMapItem *item = search_item(bucket, hash_code, key);
    return item != NULL ? item->value : NULL;
}

void my_hash_map_remove(MyHashMap *hash_map, char *key)
{
    size_t hash_code = djb2_hash(key);
    size_t index = hash_code % hash_map->capacity;
    MyListNode **bucket = &hash_map->buckets[index];
    if (remove_item(bucket, hash_code, key)) {
        hash_map->length--;
    }
}

void my_hash_map_free(MyHashMap *hash_map)
{
    for (size_t i = 0; i < hash_map->capacity; i++) {
        my_linked_list_free(&hash_map->buckets[i], (void *)hash_map_item_free);
    }

    free(hash_map->buckets);
    free(hash_map);
}

#endif