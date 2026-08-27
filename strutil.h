#ifndef strutil
#define strutil

#include <stdlib.h>

int get_string_length(const char *string)
{
    int length = 0;
    while (*string != '\0')
    {
        length++;
        string++;
    }
    return length;
}

int string_to_integer(const char *string)
{
    int result = 0;
    int sign = 1;

    if (*string == '-')
    {
        sign = -1;
        string++;
    }

    while (*string >= '0' && *string <= '9')
    {
        result = result * 10 + (*string - '0');
        string++;
    }

    return result * sign;
}

char *combine_strings(char **strings, int num_strings)
{
    int length = 0;
    for (int i = 0; i < num_strings; i++)
    {
        length += get_string_length(strings[i]);
    }

    char *combined = (char *)malloc((length + 1) * sizeof(char));

    char *pointer = combined;
    for (int i = 0; i < num_strings; i++)
    {
        while (**strings != '\0')
        {
            *pointer = **strings;
            (*strings)++;
            pointer++;
        }
        strings++;
    }
    *pointer = '\0';

    return combined;
}

char *copy_string(const char *source)
{
    int length = get_string_length(source);

    char *string = (char *)malloc((length + 1) * sizeof(char));
    if (!string) {
        return NULL;
    }

    for (int i = 0; i < length; i++)
    {
        string[i] = source[i];
    }
    string[length] = '\0';
    return string;
}

char *remove_spaces(char *source) {
    int length = get_string_length(source);

    int non_space_count = 0;
    for (int i = 0; i < length; i++) {
        if (source[i] != ' ') {
            non_space_count++;
        }
    }

    char *new_string = (char *)malloc((non_space_count + 1) * sizeof(char));
    if (new_string == NULL) {
        return NULL;
    }

    char *pointer = new_string;
    for (int i = 0; i < length; i++) {
        if (source[i] != ' ') {
            *pointer = source[i];
            pointer++;
        }
    }
    *pointer = '\0';

    return new_string;
}

#endif