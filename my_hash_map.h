
#ifndef MY_HASH_MAP_H
#define MY_HASH_MAP_H

#include <stdint.h>

#include "my_linked_list.h"

typedef struct
{
    MyListNode **buckets;
    uint64_t item_count;
    uint64_t capacity;
} MyHashMap;

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
#define KEY_STRING(s) ((ItemKey){.type = KEY_TYPE_STRING, .data.s = (s)})

#define VALUE_UINT64(n) ((ItemValue){.type = VALUE_TYPE_UINT64, .data.u64 = (n)})
#define VALUE_CHAR(c) ((ItemValue){.type = VALUE_TYPE_CHAR, .data.c = (c)})
#define VALUE_INT(n) ((ItemValue){.type = VALUE_TYPE_INT, .data.i = (n)})
#define VALUE_DOUBLE(n) ((ItemValue){.type = VALUE_TYPE_DOUBLE, .data.d = (n)})
#define VALUE_STRING(s) ((ItemValue){.type = VALUE_TYPE_STRING, .data.s = (s)})

MyHashMap *create_my_hash_map();
void my_hash_map_set(MyHashMap *hash_map, ItemKey key, ItemValue value);
bool my_hash_map_get_uint64(MyHashMap *hash_map, ItemKey key, uint64_t *out);
bool my_hash_map_get_char(MyHashMap *hash_map, ItemKey key, char *out);
bool my_hash_map_get_int(MyHashMap *hash_map, ItemKey key, int *out);
bool my_hash_map_get_double(MyHashMap *hash_map, ItemKey key, double *out);
bool my_hash_map_get_string(MyHashMap *hash_map, ItemKey key, char **out);
void my_hash_map_remove(MyHashMap *hash_map, ItemKey key);
void my_hash_map_resize(MyHashMap *hash_map);
double my_hash_map_get_load_factor(MyHashMap *hash_map);
void my_hash_map_free(MyHashMap *hash_map);

#endif
