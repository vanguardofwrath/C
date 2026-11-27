#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "string.h"

#define STRING_EXTRA_CAPACITY 12

String *create_string(const char *source)
{
    String *string = (String *)malloc(sizeof(String));
    if (!string)
    {
        return NULL;
    }

    string->length = strlen(source);
    string->capacity = string->length + STRING_EXTRA_CAPACITY;

    string->data = (char *)malloc(string->capacity);
    if (!string->data)
    {
        free(string);
        return NULL;
    }

    memcpy(string->data, source, string->length + 1);
    return string;
}

void string_replace(String *string, const char *to_replace, const char *replacement)
{
    uint64_t to_replace_length = strlen(to_replace);
    uint64_t replacement_length = strlen(replacement);

    char *occurence = strstr(string->data, to_replace);
    while (occurence)
    {
        uint64_t start_index = occurence - string->data;
        uint64_t end_index = start_index + to_replace_length;

        memmove(string->data + start_index, string->data + end_index, string->length - end_index + 1);

        string_insert(string, replacement, start_index);

        occurence = strstr(string->data + start_index + replacement_length, to_replace);
    }
}

void string_insert(String *string, const char *to_insert, uint64_t index)
{
    uint64_t to_insert_length = strlen(to_insert);
    uint64_t new_length = string->length + to_insert_length;

    if (new_length >= string->capacity)
    {
        uint64_t new_capacity = string->capacity * 2;
        while (new_capacity < new_length + 1)
        {
            new_capacity *= 2;
        }

        char *temp = (char *)realloc(string->data, new_capacity * sizeof(char));
        if (!temp)
        {
            return;
        }

        string->capacity = new_capacity;
        string->data = temp;
    }

    memmove(string->data + index + to_insert_length, string->data + index, string->length - index + 1);
    memcpy(string->data + index, to_insert, to_insert_length);

    string->length = new_length;
}

void string_concat(String *string, const char *to_concat) {
    string_insert(string, to_concat, string->length);
}

bool string_is_equal(String *string, const char *to_compare)
{
    int i = 0;
    while (string->data[i] != '\0' || to_compare[i] != '\0')
    {
        if (string->data[i] != to_compare[i])
        {
            return 0;
        }
        i++;
    }
    return 1;
}

bool string_is_number(String *string)
{
    char *endptr;
    strtod(string->data, &endptr);
    return (endptr != string->data && *endptr == '\0');
}

void string_free(String *string)
{
    free(string->data);
    free(string);
}

// --------------------------------------------------------------------------------------

StringList *create_string_list(uint64_t capacity)
{
    StringList *new_list = (StringList *)malloc(sizeof(StringList));
    if (!new_list)
    {
        return NULL;
    }

    new_list->strings = (String **)malloc(capacity * sizeof(String *));
    if (!new_list->strings)
    {
        free(new_list);
        return NULL;
    }

    new_list->capacity = capacity;
    new_list->length = 0;
    return new_list;
}

void string_list_push(StringList *string_list, String *string)
{
   if (string_list->length == string_list->capacity)
    {
        uint64_t new_capacity = string_list->capacity * 2;

        String **temp = (String **)realloc(string_list->strings, new_capacity * sizeof(String *));
        if (!temp)
        {
            return;
        }

        string_list->capacity = new_capacity;
        string_list->strings = temp;
    }

    string_list->strings[string_list->length++] = string;
}

String *string_list_peek(StringList *string_list)
{
    if (string_list->length == 0)
    {
        return NULL;
    }

    return string_list->strings[string_list->length - 1];
}

String *string_list_pop(StringList *string_list)
{
    if (string_list->length == 0)
    {
        return NULL;
    }

    String *string = string_list->strings[--string_list->length];
    string_list->strings[string_list->length] = NULL;
    return string;
}

void string_list_reverse(StringList *string_list)
{
    if (string_list->length <= 1)
    {
        return;
    }

    int left = 0, right = string_list->length - 1;

    while (left < right)
    {
        String *temp = string_list->strings[left];
        string_list->strings[left] = string_list->strings[right];
        string_list->strings[right] = temp;

        left++;
        right--;
    }
}

void string_list_free(StringList *string_list)
{
    for (uint64_t i = 0; i < string_list->length; i++)
    {
        string_free(string_list->strings[i]);
    }

    free(string_list->strings);
    free(string_list);
}

// --------------------------------------------------------------------------------------

bool string_regex_contains(String *string, const char *pattern)
{
    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED))
    {
        return false;
    }

    int result = regexec(&regex, string->data, 0, NULL, 0);
    regfree(&regex);

    return result != REG_NOMATCH;
}

String *string_regex_match(String *string, const char *pattern)
{
    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED))
    {
        return NULL;
    }

    regmatch_t match;
    if (regexec(&regex, string->data, 1, &match, 0) == REG_NOMATCH)
    {
        regfree(&regex);
        return NULL;
    }

    regoff_t start = match.rm_so;
    regoff_t end = match.rm_eo;

    uint64_t match_length = (uint64_t)end - start;

    char *matched_string = malloc((match_length + 1) * sizeof(char));
    if (!matched_string)
    {
        regfree(&regex);
        return NULL;
    }

    memcpy(matched_string, string->data + start, match_length);
    matched_string[match_length] = '\0';

    String *to_return = create_string(matched_string);
    free(matched_string);
    regfree(&regex);
    return to_return;
}

StringList *string_regex_match_all(String *string, const char *pattern)
{
    StringList *matches = create_string_list(string->length);
    if (!matches)
    {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED))
    {
        string_list_free(matches);
        return NULL;
    }

    regmatch_t match;
    const char *search_start = string->data;

    while (regexec(&regex, search_start, 1, &match, 0) != REG_NOMATCH)
    {
        regoff_t start = match.rm_so;
        regoff_t end = match.rm_eo;

        uint64_t match_length = (uint64_t)end - start;

        char *matched_string = malloc((match_length + 1) * sizeof(char));
        if (!matched_string)
        {
            string_list_free(matches);
            regfree(&regex);
            return NULL;
        }

        memcpy(matched_string, search_start + start, match_length);
        matched_string[match_length] = '\0';

        String *to_push = create_string(matched_string);
        string_list_push(matches, to_push);

        free(matched_string);

        search_start += end;
    }

    regfree(&regex);
    return matches;
}