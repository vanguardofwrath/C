#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    char *data;
    uint64_t length;
    uint64_t capacity;
} String;

typedef struct
{
    String **strings;
    uint64_t capacity;
    uint64_t length;
} StringList;

String *create_string(const char *source);
void string_replace(String *string, const char *to_replace, const char *replacement);
void string_insert(String *string, const char *to_insert, uint64_t index);
void string_concat(String *string, const char *to_concat);
bool string_is_equal(String *string, const char *to_compare);
bool string_is_number(String *string);
void string_free(String *string);

StringList *create_string_list(uint64_t capacity);
void string_list_push(StringList *string_list, String *string);
String *string_list_peek(StringList *string_list);
String *string_list_pop(StringList *string_list);
void string_list_reverse(StringList *string_list);
void string_list_free(StringList *string_list);

bool string_regex_contains(String *string, const char *pattern);
String *string_regex_match(String *string, const char *pattern);
StringList *string_regex_match_all(String *string, const char *pattern);

#endif