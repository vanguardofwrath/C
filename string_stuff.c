#include <stdio.h>
#include <stdlib.h>
#include "custom_string.h"

int main()
{
    string *new_string = create_string("Woah");
    string *other_string = create_string("Stop");

    append_string(new_string, other_string);

    print_string(new_string);

    append_char(new_string, 'B');

    print_string(new_string);

    free_string(new_string);
    free_string(other_string);
    return 0;
}