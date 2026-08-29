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
    return character == '+' || character == '-' || character == '*' || character == '/';
}

int get_precedence(char operator)
{
    if (operator == '*' || operator == '/')
    {
        return 2;
    }

    if (operator == '+' || operator == '-')
    {
        return 1;
    }
}

double calculate_expression(char *source)
{
    int length = get_string_length(source);

    char_stack *operator_stack = create_char_stack(length);
    double_stack *evalution_stack = create_double_stack(length);

    string *output_string = create_string(NULL);

    for (int i = 0; i < length; i++)
    {
        if (is_number(source[i]))
        {
            append_char(output_string, source[i]);

            while (i + 1 < length && is_number(source[i + 1]))
            {
                append_char(output_string, source[i + 1]);
                i++;
            }

            append_char(output_string, ',');
        }
        else if (is_operator(source[i]))
        {
            while (char_stack_peek(operator_stack) != '(' && get_precedence(char_stack_peek(operator_stack)) >= get_precedence(source[i]))
            {
                append_char(output_string, char_stack_pop(operator_stack));
                append_char(output_string, ',');
            }
            char_stack_push(operator_stack, source[i]);
        }
        else if (source[i] == '(')
        {
            char_stack_push(operator_stack, source[i]);
        }
        else if (source[i] == ')')
        {
            while (!char_stack_is_empty(operator_stack) && char_stack_peek(operator_stack) != '(')
            {
                append_char(output_string, char_stack_pop(operator_stack));
                append_char(output_string, ',');
            }

            if (char_stack_peek(operator_stack) == '(')
            {
                char_stack_pop(operator_stack);
            }
        }
    }

    while (!char_stack_is_empty(operator_stack) && char_stack_peek(operator_stack) != '(')
    {
        append_char(output_string, char_stack_pop(operator_stack));
        append_char(output_string, ',');
    }

    print_string(output_string);

    for (int i = 0; i < output_string->length; i++)
    {
        char character = output_string->data[i];

        if (is_number(character))
        {
            double number = ascii_to_number(character);

            while (i + 1 < output_string->length && is_number(output_string->data[i + 1]))
            {
                number *= 10;
                number += ascii_to_number(output_string->data[i + 1]);
                i++;
            }

            double_stack_push(evalution_stack, number);
        }
        else if (is_operator(character))
        {
            double right_operand = double_stack_pop(evalution_stack);
            double left_operand = double_stack_pop(evalution_stack);

            printf("%g %c %g\n", left_operand, character, right_operand);

            double result = 0;

            switch (character)
            {
            case '+':
                result += left_operand + right_operand;
                break;
            case '-':
                result += left_operand - right_operand;
                break;
            case '*':
                result += left_operand * right_operand;
                break;
            case '/':
                result += left_operand / right_operand;
                break;
            }

            double_stack_push(evalution_stack, result);
        }
    }

    double final_result = double_stack_pop(evalution_stack);

    free_char_stack(operator_stack);
    free_double_stack(evalution_stack);

    free_string(output_string);

    return final_result;
}

int main(int argc, char **argv)
{
    char *expression = remove_spaces(argv[1]);
    if (expression == NULL) {
        return 1;
    }

    double result = calculate_expression(expression);
    printf("Result:%f\n", result);

    return 0;
}