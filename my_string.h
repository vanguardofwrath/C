#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdbool.h>

typedef struct
{
    char *data;
    uint64_t length;
    uint64_t capacity;
} MyString;

typedef struct
{
    MyString **strings;
    uint64_t capacity;
    uint64_t length;
} MyStringList;

MyString *create_my_string(const char *source);
void my_string_replace(MyString *string, const char *to_replace, const char *replacement);
void my_string_insert(MyString *string, const char *to_insert, uint64_t index);
bool my_string_is_equal(MyString *string, const char *to_compare);
bool my_string_is_number(MyString *string);
void my_string_free(MyString *string);

MyStringList *create_my_string_list(uint64_t capacity);
void my_string_list_push(MyStringList *string_list, MyString *string);
MyString *my_string_list_peek(MyStringList *string_list);
MyString *my_string_list_pop(MyStringList *string_list);
void my_string_list_reverse(MyStringList *string_list);
void my_string_list_free(MyStringList *string_list);

bool my_string_regex_contains(MyString *string, const char *pattern);
MyString *my_string_regex_match(MyString *string, const char *pattern);
MyStringList *my_string_regex_match_all(MyString *string, const char *pattern);

#endif