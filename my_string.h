#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>

typedef struct
{
    char *data;
    size_t length;
    size_t capacity;
} MyString;

typedef struct {
    MyString **strings;
    size_t capacity;
    size_t length;
} MyStringList;

MyString *create_my_string(const char *source);
void my_string_replace(MyString *string, const char *to_replace, const char *replacement);
void my_string_insert(MyString *string, const char *to_insert, size_t index);
bool my_string_is_equal(MyString *string, const char *to_compare);
bool my_string_is_number(MyString *string);
void my_string_free(MyString *string);

MyStringList *create_my_string_list(size_t capacity);
void my_string_list_push(MyStringList *string_list, MyString *string);
MyString *my_string_list_pop(MyStringList *string_list);
void my_string_list_reverse(MyStringList *string_list);
void my_string_list_print(MyStringList *string_list);
void my_string_list_free(MyStringList *string_list);

bool my_string_regex_contains(MyString *string, const char *pattern);
MyString *my_string_regex_match(MyString *string, const char *pattern);
MyStringList *my_string_regex_match_all(MyString *string, const char *pattern) ;

// --------------------------------------------------------------------------------------

#define MYSTRING_EXTRA_CAPACITY 12

static bool my_string_ensure_capacity(MyString *string, size_t min_capacity) {
    if (min_capacity >= string->capacity) {
        size_t new_capacity = string->capacity * 2;
        while (new_capacity < min_capacity + 1) {
            new_capacity *= 2;
        }

        char *temp = (char *)realloc(string->data, new_capacity * sizeof(char));
        if (!temp) {
            return false;
        }

        string->capacity = new_capacity;
        string->data = temp;
    }
    
    return true;
}

static bool my_string_list_ensure_capacity(MyStringList *string_list) {
    if (string_list->length == string_list->capacity) {
        size_t new_capacity = string_list->capacity * 2;

        MyString **temp = (MyString **)realloc(string_list->strings, new_capacity * sizeof(MyString *));
        if (!temp) {
            return false;
        }

        string_list->capacity = new_capacity;
        string_list->strings = temp;
    }

    return true;
}

MyString *create_my_string(const char *source) {
    MyString *string = (MyString *)malloc(sizeof(MyString));
    if (!string)
    {
        return NULL;
    }

    string->data = strdup(source);
    if (!string->data) {
        free(string);
        return NULL;
    }

    string->length = strlen(source);
    string->capacity = string->length + MYSTRING_EXTRA_CAPACITY;

    return string;
}

void my_string_replace(MyString *string, const char *to_replace, const char *replacement) {
    size_t to_replace_length = strlen(to_replace);
    size_t replacement_length = strlen(replacement);

    char *occurence = strstr(string->data, to_replace);
    while(occurence) {
            size_t start_index = occurence - string->data;
            size_t end_index = start_index + to_replace_length;

            memmove(string->data + start_index, string->data + end_index, string->length - end_index + 1);

            my_string_insert(string, replacement, start_index);

            occurence = strstr(string->data + start_index + replacement_length, to_replace);
    }
}

void my_string_insert(MyString *string, const char *to_insert, size_t index) {
    size_t to_insert_length = strlen(to_insert);
    size_t new_length = string->length + to_insert_length;

    bool success = my_string_ensure_capacity(string, new_length);
    if (!success) {
        return;
    }

    memmove(string->data + index + to_insert_length, string->data + index, string->length - index + 1);
    memcpy(string->data + index, to_insert, to_insert_length);

    string->length = new_length;
}

bool my_string_is_equal(MyString *string, const char *to_compare) {
    int i = 0;
    while (string->data[i] != '\0' || to_compare[i] != '\0') {
        if (string->data[i] != to_compare[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}

bool my_string_is_number(MyString *string) {
    char *endptr;
    strtod(string->data, &endptr);
    return (endptr != string->data && *endptr == '\0');
}

void my_string_free(MyString *string) {
    free(string->data);
    free(string);
}

// --------------------------------------------------------------------------------------

MyStringList *create_my_string_list(size_t capacity) {
    MyStringList *new_list = (MyStringList *)malloc(sizeof(MyStringList));
    if (!new_list) {
        return NULL;
    }

    new_list->strings = (MyString **)malloc(capacity * sizeof(MyString *));
    if (!new_list->strings) {
        free(new_list);
        return NULL;
    }

    new_list->capacity = capacity;
    new_list->length = 0;
    return new_list;
}

void my_string_list_push(MyStringList *string_list, MyString *string) {
    bool success = my_string_list_ensure_capacity(string_list);
    if (!success) {
        return;
    }

    string_list->strings[string_list->length++] = string;
}

MyString *my_string_list_peek(MyStringList *string_list) {
    if (string_list->length == 0) { 
        return NULL; 
    }

    return string_list->strings[string_list->length - 1];
}

MyString *my_string_list_pop(MyStringList *string_list) {
    if (string_list->length == 0) { 
        return NULL; 
    }

    MyString *string = string_list->strings[--string_list->length];
    string_list->strings[string_list->length] = NULL;
    return string;
}

void my_string_list_reverse(MyStringList *string_list) {
    if (string_list->length <= 1) {
        return;
    }

    int left = 0, right = string_list->length - 1;

    while (left < right) {
        MyString *temp = string_list->strings[left];
        string_list->strings[left] = string_list->strings[right];
        string_list->strings[right] = temp;

        left++;
        right--;
    }
}

void my_string_list_print(MyStringList *string_list) {
    if (string_list->length == 0) {
        printf("[]\n");
        return;
    }

    printf("[");
    for (int i = 0; i < string_list->length - 1; i++) {
        printf("%s, ", string_list->strings[i]->data);
    }
    printf("%s]\n", string_list->strings[string_list->length - 1]->data);
}

void my_string_list_free(MyStringList *string_list) {
    for (size_t i = 0; i < string_list->length; i++) {
        my_string_free(string_list->strings[i]);
    }

    free(string_list->strings);
    free(string_list);
}

// --------------------------------------------------------------------------------------

bool my_string_regex_contains(MyString *string, const char *pattern) {
    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED))
    {
        return false;
    }

    int result = regexec(&regex, string->data, 0, NULL, 0);
    regfree(&regex);

    return result != REG_NOMATCH;
}

MyString *my_string_regex_match(MyString *string, const char *pattern) {
    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED))
    {
        return NULL;
    }

    regmatch_t match;
    if (regexec(&regex, string->data, 1, &match, 0) == REG_NOMATCH) {
        regfree(&regex);
        return NULL;
    }

    regoff_t start = match.rm_so;
    regoff_t end = match.rm_eo;

    size_t match_length = (size_t)end - start;

    char *matched_string = malloc((match_length + 1) * sizeof(char));
    if (!matched_string) {
        regfree(&regex);
        return NULL;
    }

    memcpy(matched_string, string->data + start, match_length);
    matched_string[match_length] = '\0';

    MyString *to_return = create_my_string(matched_string);
    free(matched_string);
    regfree(&regex);
    return to_return;
}

MyStringList *my_string_regex_match_all(MyString *string, const char *pattern) {
    MyStringList *matches = create_my_string_list(string->length);
    if (!matches) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        my_string_list_free(matches);
        return NULL;
    }

    regmatch_t match;
    const char *search_start = string->data;

    while (regexec(&regex, search_start, 1, &match, 0) != REG_NOMATCH) {
        regoff_t start = match.rm_so;
        regoff_t end = match.rm_eo;

        size_t match_length = (size_t)end - start;

        char *matched_string = malloc((match_length + 1) * sizeof(char));
        if (!matched_string) {
            my_string_list_free(matches);
            regfree(&regex);
            return NULL;
        }

        memcpy(matched_string, search_start + start, match_length);
        matched_string[match_length] = '\0';

        MyString *to_push = create_my_string(matched_string);
        my_string_list_push(matches, to_push);

        free(matched_string);

        search_start += end;
    }

    regfree(&regex);
    return matches;
}


#endif