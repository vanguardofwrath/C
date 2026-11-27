#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "common/stack.h"
#include "common/string.h"

#define TOKENIZATION_REGEX_PATTERN "[0-9]+(\\.[0-9]+)?|[()^*/+-]"

bool is_operator(String *string)
{
    return string_is_equal(string, "^") ||
           string_is_equal(string, "*") ||
           string_is_equal(string, "/") ||
           string_is_equal(string, "+") ||
           string_is_equal(string, "-");
}

bool is_left_parentheses(String *string)
{
    return string_is_equal(string, "(");
}

bool is_right_parentheses(String *string)
{
    return string_is_equal(string, ")");
}

int get_precedence(String *operator)
{
    return string_is_equal(operator, "^") ? 3
    : (string_is_equal(operator, "*") || string_is_equal(operator, "/")) ? 2
    : (string_is_equal(operator, "+") || string_is_equal(operator, "-")) ? 1 : 0;
}

bool is_right_associative(String *operator)
{
    return string_is_equal(operator, "^");
}

double calculate_expression(const char *source)
{
    String *expression = create_string(source);
    if (!expression)
    {
        printf("Error: Failed to create String for the expression.\n");
        return 0;
    }

    StringList *operator_stack = create_string_list(expression->length);
    if (!operator_stack)
    {
        string_free(expression);
        printf("Error: Failed to create operator stack.\n");
        return 0;
    }

    DoubleStack *evalution_stack = create_double_stack(expression->length);
    if (!evalution_stack)
    {
        string_free(expression);
        string_list_free(operator_stack);
        printf("Error: Failed to create evaluation stack.\n");
        return 0;
    }

    StringList *output_list = create_string_list(expression->length);
    if (!output_list)
    {
        string_free(expression);
        string_list_free(operator_stack);
        double_stack_free(evalution_stack);
        printf("Error: Failed to create output queue.\n");
        return 0;
    }

    StringList *token_list = string_regex_match_all(expression, TOKENIZATION_REGEX_PATTERN);
    if (!token_list)
    {
        string_free(expression);
        string_list_free(operator_stack);
        double_stack_free(evalution_stack);
        string_list_free(output_list);
        printf("Error: Failed to tokenize the expression.\n");
        return 0;
    }

    string_list_reverse(token_list);

    while (token_list->length > 0)
    {
        String *token = string_list_pop(token_list);

        if (string_is_number(token))
        {
            string_list_push(output_list, token);
        }
        else if (is_operator(token))
        {
            String *top_operator = string_list_peek(operator_stack);
            while (top_operator && !is_left_parentheses(top_operator) && 
            (get_precedence(top_operator) >= get_precedence(token) || 
            get_precedence(top_operator) == get_precedence(token) && !is_right_associative(token)))
            {
                string_list_push(output_list, string_list_pop(operator_stack));
                top_operator = string_list_peek(operator_stack);
            }

            string_list_push(operator_stack, token);
        }
        else if (is_left_parentheses(token))
        {
            string_list_push(operator_stack, token);
        }
        else if (is_right_parentheses(token))
        {
            while (!is_left_parentheses(string_list_peek(operator_stack)))
            {
                string_list_push(output_list, string_list_pop(operator_stack));
            }

            String *left_parentheses = string_list_pop(operator_stack);
            string_free(left_parentheses);
        }
    }

    while (operator_stack->length > 0)
    {
        string_list_push(output_list, string_list_pop(operator_stack));
    }

    for (int i = 0; i < output_list->length; i++)
    {
        String *string = output_list->strings[i];

        if (string_is_number(string))
        {
            double_stack_push(evalution_stack, atof(string->data));
        }
        else if (is_operator(string))
        {
            double right_operand = double_stack_pop(evalution_stack);
            double left_operand = double_stack_pop(evalution_stack);

            double local_result;

            if (string_is_equal(string, "^"))
            {
                local_result = pow(left_operand, right_operand);
            }
            else if (string_is_equal(string, "*"))
            {
                local_result = left_operand * right_operand;
            }
            else if (string_is_equal(string, "/"))
            {
                local_result = left_operand / right_operand;
            }
            else if (string_is_equal(string, "+"))
            {
                local_result = left_operand + right_operand;
            }
            else if (string_is_equal(string, "-"))
            {
                local_result = left_operand - right_operand;
            }

            double_stack_push(evalution_stack, local_result);
        }
    }

    double final_result = double_stack_peek(evalution_stack);

    string_free(expression);
    string_list_free(operator_stack);
    double_stack_free(evalution_stack);
    string_list_free(output_list);
    string_list_free(token_list);

    return final_result;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("You must pass in a single mathematical expression as a string!");
        return EXIT_FAILURE;
    }

    const char *source = argv[1];

    double result = calculate_expression(source);
    printf("Result:%g\n", result);

    return EXIT_SUCCESS;
}