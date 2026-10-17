#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "my_stack.h"
#include "my_string.h"

#define TOKENIZATION_REGEX_PATTERN "[0-9]+(\\.[0-9]+)?|[()^*/+-]|sqrt|sin|cos"

bool is_operator(MyString *string)
{
    return my_string_is_equal(string, "^") || my_string_is_equal(string, "*") || my_string_is_equal(string, "/") || my_string_is_equal(string, "+") || my_string_is_equal(string, "-");
}

bool is_function(MyString *string) {
    return my_string_is_equal(string, "sqrt") || my_string_is_equal(string, "sin") || my_string_is_equal(string, "cos");
}

bool is_left_parentheses(MyString *string)
{
    return my_string_is_equal(string, "(");
}

bool is_right_parentheses(MyString *string)
{
    return my_string_is_equal(string, ")");
}

int get_precedence(MyString *operator)
{
    return my_string_is_equal(operator, "^") ? 3 : (my_string_is_equal(operator, "*") || my_string_is_equal(operator, "/")) ? 2 : (my_string_is_equal(operator, "+") || my_string_is_equal(operator, "-")) ? 1 : 0;
}

bool is_right_associative(MyString *operator) {
    return my_string_is_equal(operator, "^");
}

double calculate_expression(const char *source) {
    MyString *expression = create_my_string(source);
    if (!expression) {
        printf("Error: Failed to create MyString for the expression.\n");
        return 0;
    }

    MyStringList *operator_stack = create_my_string_list(expression->length);
    if (!operator_stack) {
        my_string_free(expression);
        printf("Error: Failed to create operator stack.\n");
        return 0;
    }

    MyDoubleStack *evalution_stack = create_my_double_stack(expression->length);
    if (!evalution_stack) {
        my_string_free(expression);
        my_string_list_free(operator_stack);
        printf("Error: Failed to create evaluation stack.\n");
        return 0;
    }

    MyStringList *output_list = create_my_string_list(expression->length);
    if (!output_list) {
        my_string_free(expression);
        my_string_list_free(operator_stack);
        my_double_stack_free(evalution_stack);
        printf("Error: Failed to create output queue.\n");
        return 0;
    }

    MyStringList *token_list = my_string_regex_match_all(expression, TOKENIZATION_REGEX_PATTERN);
    if (!token_list) {
        my_string_free(expression);
        my_string_list_free(operator_stack);
        my_double_stack_free(evalution_stack);
        my_string_list_free(output_list);
        printf("Error: Failed to tokenize the expression.\n");
        return 0;
    }

    my_string_list_reverse(token_list);

    while (token_list->length > 0) {
        MyString *token = my_string_list_pop(token_list);

        if (my_string_is_number(token)) {
            my_string_list_push(output_list, token);
        }
        else if(is_operator(token)) {
            MyString *top_operator = my_string_list_peek(operator_stack);
            while (top_operator && !my_string_is_equal(top_operator, "(") && get_precedence(top_operator) >= get_precedence(token) && !is_right_associative(token)) {
                my_string_list_push(output_list, my_string_list_pop(operator_stack));
                top_operator = my_string_list_peek(operator_stack);
            }

            my_string_list_push(operator_stack, token);
        }
        else if (is_left_parentheses(token)) {
            my_string_list_push(operator_stack, token);
        }
        else if (is_right_parentheses(token)) {
            while (!my_string_is_equal(my_string_list_peek(operator_stack), "(")) {
                my_string_list_push(output_list, my_string_list_pop(operator_stack));
            }

           MyString* left_parentheses = my_string_list_pop(operator_stack);
           my_string_free(left_parentheses);
        }
    }

    while (operator_stack->length > 0) {
        my_string_list_push(output_list, my_string_list_pop(operator_stack));
    }

    for(int i = 0; i < output_list->length; i++) {
        MyString *string = output_list->strings[i];

        if (my_string_is_number(string)) {
            my_double_stack_push(evalution_stack, atof(string->data));
        }
        else if(is_operator(string)) {
            double right_operand = my_double_stack_pop(evalution_stack);
            double left_operand = my_double_stack_pop(evalution_stack);

            double local_result;
            if (my_string_is_equal(string, "^")) {
                local_result = pow(left_operand, right_operand);
            }
            else if (my_string_is_equal(string, "*")) {
                local_result = left_operand * right_operand;
            }
            else if (my_string_is_equal(string, "/")) {
                local_result = left_operand / right_operand;
            }
            else if (my_string_is_equal(string, "+")) {
                local_result = left_operand + right_operand;
            }
            else if (my_string_is_equal(string, "-")) {
                local_result = left_operand - right_operand;
            }

            my_double_stack_push(evalution_stack, local_result);
        }
    }

    double result = my_double_stack_peek(evalution_stack);

    my_string_free(expression);
    my_string_list_free(operator_stack);
    my_double_stack_free(evalution_stack);
    my_string_list_free(output_list);
    my_string_list_free(token_list);

    return result;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("You must pass in a single mathematical expression as a string!");
        return EXIT_FAILURE;
    }

    const char *source = argv[1];
    
    double result = calculate_expression(source);
    printf("Result:%f\n", result);

    return EXIT_SUCCESS;
}