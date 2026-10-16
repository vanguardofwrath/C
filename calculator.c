#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#include "my_stack.h"
#include "my_string.h"

static inline int character_to_number(char character)
{
    return character - '0';
}

static inline int is_number(char character)
{
    return character >= '0' && character <= '9';
}

static inline int is_operator(char character)
{
    return character == '+' || character == '-' || character == '*' || character == '/';
}

static inline int get_precedence(char operator)
{
    return (operator == '*' || operator == '/') ? 2 : (operator == '+' || operator == '-') ? 1 : 0;
}

#define NUMBER_REGEX_PATTERN "^\\d*\\.?\\d+$"

double calculate_expression(const char *source) {
    MyString *expression = create_my_string(source);

    MyCharStack *operator_stack = create_my_char_stack(expression->length);
    MyDoubleStack *evalution_stack = create_my_double_stack(expression->length);

    MyStringList *output_list = create_my_string_list(expression->length);

    for (int i = 0; i < expression->length; i++)
    {;
        MyString *string = my_string_regex_match(expression, NUMBER_REGEX_PATTERN);
        if (string) {
            printf("%s\n", string->data);
        }
        // if (is_number(source[i]))
        // {
        //     append_char(output_string, source[i]);

        //     while (i + 1 < source_length && is_number(source[i + 1]))
        //     {
        //         append_char(output_string, source[i + 1]);
        //         i++;
        //     }

        //     append_char(output_string, ',');
        // }
        // else if (is_operator(source[i]))
        // {
        //     while (char_stack_peek(operator_stack) != '(' && get_precedence(char_stack_peek(operator_stack)) >= get_precedence(source[i]))
        //     {
        //         append_char(output_string, char_stack_pop(operator_stack));
        //         append_char(output_string, ',');
        //     }
        //     char_stack_push(operator_stack, source[i]);
        // }
        // else if (source[i] == '(')
        // {
        //     char_stack_push(operator_stack, source[i]);
        // }
        // else if (source[i] == ')')
        // {
        //     while (!char_stack_is_empty(operator_stack) && char_stack_peek(operator_stack) != '(')
        //     {
        //         append_char(output_string, char_stack_pop(operator_stack));
        //         append_char(output_string, ',');
        //     }

        //     if (char_stack_peek(operator_stack) == '(')
        //     {
        //         char_stack_pop(operator_stack);
        //     }
        // }
    }

    // while (!char_stack_is_empty(operator_stack) && char_stack_peek(operator_stack) != '(')
    // {
    //     append_char(output_string, char_stack_pop(operator_stack));
    //     append_char(output_string, ',');
    // }

    // for (int i = 0; i < output_string->length; i++)
    // {
    //     char character = output_string->data[i];

    //     if (is_number(character))
    //     {
    //         double number = character_to_number(character);

    //         while (i + 1 < output_string->length && is_number(output_string->data[i + 1]))
    //         {
    //             number *= 10;
    //             number += character_to_number(output_string->data[i + 1]);
    //             i++;
    //         }

    //         double_stack_push(evalution_stack, number);
    //     }
    //     else if (is_operator(character))
    //     {
    //         double right_operand = double_stack_pop(evalution_stack);
    //         double left_operand = double_stack_pop(evalution_stack);

    //         double result = 0;

    //         switch (character)
    //         {
    //         case '+':
    //             result += left_operand + right_operand;
    //             break;
    //         case '-':
    //             result += left_operand - right_operand;
    //             break;
    //         case '*':
    //             result += left_operand * right_operand;
    //             break;
    //         case '/':
    //             result += left_operand / right_operand;
    //             break;
    //         }

    //         double_stack_push(evalution_stack, result);
    //     }
    // }

    // double final_result = double_stack_pop(evalution_stack);

    // free_char_stack(operator_stack);
    // free_double_stack(evalution_stack);

    // free_string(output_string);

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