#include <stdio.h>
#include <stdlib.h>

#include "my_string.h"
#include "my_dictionary.h"

int main(int argc, char **argv)
{
    MyDictionary *dictionary = create_my_dictionary(3);
    my_dictionary_add(dictionary, "a", 'c');
    my_dictionary_add(dictionary, "b", 'c');
    my_dictionary_add(dictionary, "c", 'c');
    my_dictionary_add(dictionary, "d", 'c');
    return EXIT_SUCCESS;
}