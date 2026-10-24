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

typedef struct {
    char *key;
    void *value;
} HashMapItem;

MyHashMap *create_my_hash_map();
void my_hash_map_set(MyHashMap *hash_map, char *key, void *value);
HashMapItem *my_hash_map_get(MyHashMap *hashmap, char *key);
void my_hash_map_remove(MyHashMap *hash_map, char *key);
void my_hash_map_free(MyHashMap *hash_map);

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

static HashMapItem *search_item(MyListNode *bucket, size_t hash_code) {
    while (bucket) {
        HashMapItem *item = (HashMapItem *)(bucket->value);
        if (djb2_hash(item->key) == hash_code) {
            return item;
        }
        bucket = bucket->next;
    }
    return NULL;
}


// --------------------------------------------------------------------------------------

#define DEFAULT_CAPACITY 10

MyHashMap *create_my_hash_map()
{
    MyHashMap *hash_map = (MyHashMap *)malloc(sizeof(MyHashMap));
    if (!hash_map)
    {
        return NULL;
    }

    hash_map->buckets = (MyListNode **)malloc(sizeof(MyListNode *) * DEFAULT_CAPACITY);
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
    MyListNode *bucket = hash_map->buckets[index];

    HashMapItem *found_item = search_item(bucket, hash_code);
    if (found_item) {
        found_item->value = value;
        return;
    }

    HashMapItem *new_item = (HashMapItem *)malloc(sizeof(HashMapItem));
    if (!new_item)
    {
        return;
    }

    new_item->key = key;
    new_item->value = value;

    my_linked_list_push(&bucket, new_item);
}

HashMapItem *my_hash_map_get(MyHashMap *hash_map, char *key) {
    size_t hash_code = djb2_hash(key);
    size_t index = hash_code % hash_map->capacity;
    MyListNode *bucket = hash_map->buckets[index];
    return search_item(bucket, hash_code);
}

void my_hash_map_remove(MyHashMap *hash_map, char *key)
{
    size_t hash_code = djb2_hash(key);
    size_t index = hash_code % hash_map->capacity;
    MyListNode *bucket = hash_map->buckets[index];
    while (bucket) {
        HashMapItem *item = bucket->value;
        if (djb2_hash(item->key) == hash_code) {
            
        }
        bucket = bucket->next;
    }
}

void my_hash_map_free(MyHashMap *hash_map)
{
    for (int i = 0; i < DEFAULT_CAPACITY; i++) {
        my_linked_list_free(hash_map->buckets[i]);
    }

    free(hash_map->buckets);
    free(hash_map);
}

#endif