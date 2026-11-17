#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "my_linked_list.h"
#include "my_hash_map.h"

#define HASH_MAP_CAPACITY 16
#define HASH_MAP_RESIZE_THRESHOLD 0.7

typedef struct
{
    ItemKey key;
    ItemValue value;
} Item;

Item *create_item(ItemKey key, ItemValue value)
{
    Item *item = (Item *)malloc(sizeof(Item));
    if (!item)
    {
        return NULL;
    }

    item->key = key;
    item->value = value;
    return item;
}

void free_item(Item *item)
{
    switch(item->key.type) {
        case KEY_TYPE_STRING:
            free(item->key.data.s);
            break;
        default:
            break;
    }

    free(item);
}

static Item *search_item(MyListNode *bucket, ItemKey key)
{
    while (bucket)
    {
        Item *item = (Item *)(bucket->value);
        
        switch (key.type) {
            case KEY_TYPE_CHAR:
                if (item->key.data.c == key.data.c) {
                    return item;
                }
                break;
            case KEY_TYPE_STRING:
                if (strcmp(item->key.data.s, key.data.s) == 0) {
                    return item;
                }
                break;
            default:
                break;
        }

        bucket = bucket->next;
    }

    return NULL;
}

static bool remove_item(MyListNode **bucket, ItemKey key)
{
    while (*bucket)
    {
        Item *item = (Item *)(*bucket)->value;

        bool match_found;
        switch(key.type) {
            case KEY_TYPE_STRING:
                match_found = strcmp(item->key.data.s, key.data.s) == 0;
                break;
            case KEY_TYPE_CHAR:
                match_found = item->key.data.c == key.data.c;
                break;
        }

        if (match_found)
        {
            MyListNode *to_remove = *bucket;
            *bucket = to_remove->next;
            free_item(item);
            free(to_remove);
            return true;
        }

        bucket = &((*bucket)->next);
    }

    return false;
}

static uint64_t hash_key(ItemKey key)
{
    uint64_t hash = 5381;

    switch(key.type) {
        case KEY_TYPE_CHAR:
            return ((hash << 5) + hash) + key.data.c;
            break;
        case KEY_TYPE_STRING:
            int c;
            while ((c = *key.data.s++))
            {
                hash = ((hash << 5) + hash) + c;
            }
            return hash;
            break;
    }
}

static uint64_t get_index(uint64_t hash_code, uint64_t capacity) {
    return hash_code & (capacity - 1);
}

// --------------------------------------------------------------------------------------

MyHashMap *create_my_hash_map()
{
    MyHashMap *hash_map = (MyHashMap *)malloc(sizeof(MyHashMap));
    if (!hash_map)
    {
        return NULL;
    }

    hash_map->buckets = (MyListNode **)calloc(HASH_MAP_CAPACITY, sizeof(MyListNode *));
    if (!hash_map->buckets)
    {
        free(hash_map);
        return NULL;
    }

    hash_map->capacity = HASH_MAP_CAPACITY;
    hash_map->item_count = 0;
    return hash_map;
}

void my_hash_map_set(MyHashMap *hash_map, ItemKey key, ItemValue value)
{
    uint64_t hash_code = hash_key(key);
    uint64_t idx = get_index(hash_code, hash_map->capacity);
    MyListNode **bucket = &hash_map->buckets[idx];

    Item *existing = search_item(*bucket, key);
    if (existing)
    {
        existing->value = value;
        return;
    }

    Item *item = create_item(key, value);
    if (!item)
    {
        return;
    }

    my_linked_list_push(bucket, item);
    hash_map->item_count++;

    if (my_hash_map_get_load_factor(hash_map) >= HASH_MAP_RESIZE_THRESHOLD) {
        my_hash_map_resize(hash_map);
    }
}

bool my_hash_map_get(MyHashMap *hash_map, ItemKey key, ItemValue *out)
{
    uint64_t hash_code = hash_key(key);
    uint64_t idx = get_index(hash_code, hash_map->capacity);
    Item *item = search_item(hash_map->buckets[idx], key);
    if (!item) {
        return false;
    }

    *out = item->value;
    return true;
}

bool my_hash_map_get_uint64(MyHashMap *hash_map, ItemKey key, uint64_t *out) {
    ItemValue value;
    if (my_hash_map_get(hash_map, key, &value) && value.type == VALUE_TYPE_UINT64) {
        *out = value.data.u64;
        return true;
    }
    return false;
}

bool my_hash_map_get_char(MyHashMap *hash_map, ItemKey key, char *out)
{
    ItemValue value;
    if (my_hash_map_get(hash_map, key, &value) && value.type == VALUE_TYPE_CHAR) {
        *out = value.data.c;
        return true;
    }
    return false;
}

bool my_hash_map_get_int(MyHashMap *hash_map, ItemKey key, int *out)
{
    ItemValue value;
    if (my_hash_map_get(hash_map, key, &value) && value.type == VALUE_TYPE_INT) {
        *out = value.data.i;
        return true;
    }
    return false;
}

bool my_hash_map_get_double(MyHashMap *hash_map, ItemKey key, double *out)
{
    ItemValue value;
    if (my_hash_map_get(hash_map, key, &value) && value.type == VALUE_TYPE_DOUBLE) {
        *out = value.data.d;
        return true;
    }
    return false;
}

bool my_hash_map_get_string(MyHashMap *hash_map, ItemKey key, char **out)
{
    ItemValue value;
    if (my_hash_map_get(hash_map, key, &value) && value.type == VALUE_TYPE_STRING) {
        *out = value.data.s;
        return true;
    }
    return false;
}

void my_hash_map_remove(MyHashMap *hash_map, ItemKey key)
{
    uint64_t hash_code = hash_key(key);
    uint64_t idx = get_index(hash_code, hash_map->capacity);
    MyListNode **bucket = &hash_map->buckets[idx];
    if (remove_item(bucket, key))
    {
        hash_map->item_count--;
    }
}

void my_hash_map_resize(MyHashMap *hash_map) {
    uint64_t new_capacity = hash_map->capacity * 2;

    MyListNode **new_buckets = (MyListNode **)calloc(new_capacity, sizeof(MyListNode *));
    if (!new_buckets) {
        return;
    }

    for (uint64_t i = 0; i < hash_map->capacity; i++) {
        MyListNode **bucket = &hash_map->buckets[i];

        while(my_linked_list_peek_front(*bucket)) {
            Item *item = (Item *)my_linked_list_pop_front(bucket);

            uint64_t hash_code = hash_key(item->key);
            uint64_t idx = get_index(hash_code, new_capacity);

            my_linked_list_push(&new_buckets[idx], item);
        }
    }

    free(hash_map->buckets);

    hash_map->capacity = new_capacity;
    hash_map->buckets = new_buckets;
}

double my_hash_map_get_load_factor(MyHashMap *hash_map) {
    return (double)hash_map->item_count / hash_map->capacity;
}

void my_hash_map_free(MyHashMap *hash_map)
{
    for (uint64_t i = 0; i < hash_map->capacity; i++)
    {
        my_linked_list_free(&hash_map->buckets[i], (void *)free_item);
    }

    free(hash_map->buckets);
    free(hash_map);
}