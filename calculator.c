#include <stdio.h>
#include <stdlib.h>

#include "strutil.h"
#include "stackutil.h"
#include "custom_string.h"

int ascii_to_number(char ascii)
{
    return ascii - '0';
}

char number_to_ascii(int number)
{
    return number + '0';
}

int is_number(char character)
{
    return character >= '0' && character <= '9';
}

int is_operator(char character)
{
    return character == '+' || character == '-' || character == '*' || character == '/' || character == '^';
}

int calculate_expression(char *source)
{
    int length = get_string_length(source);

    stack *operator_stack = create_stack(length);
    stack *evalution_stack = create_stack(length);

    free_stack(operator_stack);
    free_stack(evalution_stack);

    return 0;
}

int main(int argc, char **argv)
{
    // char *expression = remove_spaces(argv[1]);
    // if (expression == NULL) {
    //     return 1;
    // }

    char *expression = "4*5+(5+3)/2";

    int result = calculate_expression(expression);
    printf("Result:%d\n", result);

    return 0;
}