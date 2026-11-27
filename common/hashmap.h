
#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdint.h>

#include "linkedlist.h"

typedef struct
{
    ListNode **buckets;
    uint64_t item_count;
    uint64_t capacity;
} HashMap;

typedef enum {
    KEY_TYPE_CHAR,
    KEY_TYPE_STRING,
} KeyType;

typedef enum {
    VALUE_TYPE_UINT64,
    VALUE_TYPE_CHAR,
    VALUE_TYPE_INT,
    VALUE_TYPE_DOUBLE,
    VALUE_TYPE_STRING,
} ValueType;

typedef struct {
    KeyType type;
    union {
        char c;
        char *s;
    } data;
} ItemKey;

typedef struct {
    ValueType type;
    union {
        uint64_t u64;
        char c;
        int i;
        double d;
        char *s;
    } data;
} ItemValue;

#define KEY_CHAR(ch) ((ItemKey){.type = KEY_TYPE_CHAR, .data.c = (ch)})
#define KEY_STRING(str) ((ItemKey){.type = KEY_TYPE_STRING, .data.s = (str)})

#define VALUE_UINT64(n) ((ItemValue){.type = VALUE_TYPE_UINT64, .data.u64 = (n)})
#define VALUE_CHAR(c) ((ItemValue){.type = VALUE_TYPE_CHAR, .data.c = (c)})
#define VALUE_INT(n) ((ItemValue){.type = VALUE_TYPE_INT, .data.i = (n)})
#define VALUE_DOUBLE(n) ((ItemValue){.type = VALUE_TYPE_DOUBLE, .data.d = (n)})
#define VALUE_STRING(s) ((ItemValue){.type = VALUE_TYPE_STRING, .data.s = (s)})

HashMap *create_hash_map();
void hash_map_set(HashMap *hash_map, ItemKey key, ItemValue value);
bool hash_map_get_uint64(HashMap *hash_map, ItemKey key, uint64_t *out);
bool hash_map_get_char(HashMap *hash_map, ItemKey key, char *out);
bool hash_map_get_int(HashMap *hash_map, ItemKey key, int *out);
bool hash_map_get_double(HashMap *hash_map, ItemKey key, double *out);
bool hash_map_get_string(HashMap *hash_map, ItemKey key, char **out);
void hash_map_remove(HashMap *hash_map, ItemKey key);
void hash_map_resize(HashMap *hash_map);
double hash_map_get_load_factor(HashMap *hash_map);
void hash_map_free(HashMap *hash_map);

#endif
