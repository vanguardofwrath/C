#ifndef MY_HASH_MAP_H
#define MY_HASH_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_linked_list.h"

typedef struct
{
    MyListNode **buckets;
    size_t item_count;
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

static double get_load_factor(MyHashMap *hash_map) {
    return (double)hash_map->item_count / hash_map->capacity;
}

static size_t get_index(size_t hash_code, size_t capacity) {
    return hash_code & (capacity - 1);
}

static void resize_hash_map(MyHashMap *hash_map) {
    size_t new_capacity = hash_map->capacity * 2;

    MyListNode **new_buckets = (MyListNode **)calloc(new_capacity, sizeof(MyListNode *));
    if (!new_buckets) {
        return;
    }

    for (size_t i = 0; i < hash_map->capacity; i++) {
        MyListNode **bucket = &hash_map->buckets[i];

        while(my_linked_list_peek_front(*bucket)) {
            HashMapItem *item = my_linked_list_pop_front(bucket);

            size_t hash_code = djb2_hash(item->key);
            size_t index = get_index(hash_code, new_capacity);

            my_linked_list_push(&new_buckets[index], item);
        }
    }

    free(hash_map->buckets);

    hash_map->capacity = new_capacity;
    hash_map->buckets = new_buckets;
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

HashMapItem *create_hash_map_item(char *key, void *value)
{
    HashMapItem *item = (HashMapItem *)malloc(sizeof(HashMapItem));
    if (!item)
    {
        return NULL;
    }

    item->key = strdup(key);
    if (!item->key)
    {
        free(item);
        return NULL;
    }

    item->value = value;
    return item;
}

void hash_map_item_free(HashMapItem *item)
{
    free(item->key);
    free(item);
}

// --------------------------------------------------------------------------------------

#define DEFAULT_CAPACITY 16
#define RESIZE_THRESHOLD 0.7

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
    hash_map->item_count = 0;
    return hash_map;
}

void my_hash_map_set(MyHashMap *hash_map, char *key, void *value)
{
    size_t hash_code = djb2_hash(key);
    size_t index = get_index(hash_code, hash_map->capacity);
    MyListNode **bucket = &hash_map->buckets[index];

    HashMapItem *existing = search_item(*bucket, hash_code, key);
    if (existing)
    {
        existing->value = value;
        return;
    }

    HashMapItem *item = create_hash_map_item(key, value);
    if (!item)
    {
        return;
    }

    my_linked_list_push(bucket, item);
    hash_map->item_count++;

    if (get_load_factor(hash_map) >= RESIZE_THRESHOLD) {
        resize_hash_map(hash_map);
    }
}

void *my_hash_map_get(MyHashMap *hash_map, char *key)
{
    size_t hash_code = djb2_hash(key);
    size_t index = get_index(hash_code, hash_map->capacity);
    MyListNode *bucket = hash_map->buckets[index];
    HashMapItem *item = search_item(bucket, hash_code, key);
    return item != NULL ? item->value : NULL;
}

void my_hash_map_remove(MyHashMap *hash_map, char *key)
{
    size_t hash_code = djb2_hash(key);
    size_t index = get_index(hash_code, hash_map->capacity);
    MyListNode **bucket = &hash_map->buckets[index];
    if (remove_item(bucket, hash_code, key))
    {
        hash_map->item_count--;
    }
}

void my_hash_map_free(MyHashMap *hash_map)
{
    for (size_t i = 0; i < hash_map->capacity; i++)
    {
        my_linked_list_free(&hash_map->buckets[i], (void *)hash_map_item_free);
    }

    free(hash_map->buckets);
    free(hash_map);
}

#endif