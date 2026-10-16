#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <regex.h>

#include "my_stack.h"
#include "my_string.h"

#define TOKENIZATION_REGEX_PATTERN "[0-9]+\\.?[0-9]*|[[:punct:]]"
#define NUMBER_REGEX_PATTERN "^[0-9]+(?:\\.[0-9]+)?$"

bool is_number(MyString *string) {
    return my_string_regex_contains(string, NUMBER_REGEX_PATTERN);
}

bool is_operator(MyString *string)
{
    return my_string_is_equal(string, "*") || my_string_is_equal(string, "/") || my_string_is_equal(string, "+") || my_string_is_equal(string, "-");
}

bool is_left_parentheses(MyString *string)
{
    return my_string_is_equal(string, "(")
}

bool is_right_parentheses(MyString *string)
{
    return my_string_is_equal(string, ")")
}

int get_precedence(MyString *operator)
{
    return (my_string_is_equal(operator, "*") || y_string_is_equal(operator, "/")) ? 2 : (my_string_is_equal(operator, "+") || y_string_is_equal(operator, "-")) ? 1 : 0
}

double calculate_expression(const char *source) {
    MyString *expression = create_my_string(source);
    if (!expression) {
        printf("Error: Failed to create MyString for the expression.\n");
        return 0;
    }

    MyCharStack *operator_stack = create_my_char_stack(expression->length);
    if (!operator_stack) {
        my_string_free(expression);
        printf("Error: Failed to create operator stack.\n");
        return 0;
    }

    MyDoubleStack *evalution_stack = create_my_double_stack(expression->length);
    if (!evalution_stack) {
        my_string_free(expression);
        my_char_stack_free(operator_stack);
        printf("Error: Failed to create evaluation stack.\n");
        return 0;
    }

    MyStringList *token_list = my_string_regex_match_all(expression, TOKENIZATION_REGEX_PATTERN);
    if (!token_list) {
        my_string_free(expression);
        my_char_stack_free(operator_stack);
        my_double_stack_free(evalution_stack);
        printf("Error: Failed to tokenize the expression.\n");
        return 0;
    }

    for (int i = 0; i < token_list->length; i++) {
        MyString *token = token_list->strings[i];

        if (is_number(token)) {

        }
        else if(is_operator(token)) {

        }
        else if (is_left_parentheses(token)) {

        }
        else if (is_right_parentheses(token)) {

        }
    }


    return 1;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("You must pass in a single mathematical expression as a string!");
        return EXIT_FAILURE;
    }

    const char *source = argv[1];
    
    double result = calculate_expression(source);
    printf("Result:%d\n", result);

    return EXIT_SUCCESS;
}