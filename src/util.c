#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "util.h"

bool ishexachar(char ch)
{
    for (unsigned short int i = 0; i < strlen(hexa_char); i++)
        if (ch == hexa_char[i])
            return true;

    return false;
}

bool isdot(char ch)
{
    for (unsigned short int i = 0; i < strlen(dot_char); i++)
        if (ch == dot_char[i])
            return true;

    return false;
}

static void append_char(char *str, char ch)
{
    size_t len = strlen(str);
    str[len] = ch;
    str[len + 1] = '\0';
}

static char *double_to_string(double number)
{
    size_t size = snprintf(NULL, 0, "%f", number);
    if (size < 0)
        return NULL;

    char *str = malloc(size + 1);
    if (!str)
        return NULL;

    snprintf(str, size + 1, "%f", number);

    FPoint fpoint = break_str(str, ".");

    return (atoi(fpoint.decimal) == 0) ? fpoint.integer : str;
}

static void reverse_range(char *str, size_t start, size_t end)
{
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

static unsigned short int char_to_digit(char ch)
{
    if (isdigit(ch))
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return 10 + (ch - 'A');
    if (ch >= 'a' && ch <= 'f')
        return 10 + (ch - 'a');
    return 0xFFFF;
}

static FPoint break_str(const char *value, const char *dot)
{
    FPoint number;

    char *copy = strdup(value);
    if (!copy)
        return (FPoint){NULL, NULL, false};

    char *integer = strtok(copy, ".");
    char *decimal = strtok(NULL, ".");

    number.integer = strdup(integer);
    number.decimal = decimal ? strdup(decimal) : NULL;
    number.hasDecimal = decimal ? true : false;

    free(copy);

    return number;
}

static size_t calculate_digits(double number, TokenType base)
{
    return (size_t)ceil(log(number) / log(base)) + 1;
}

char *octal(char *value, TokenType base) {
    FPoint number = break_str(value, ".");
    char *result = (char *)calloc(calculate_digits(decimal(value, base), TOKEN_OCTAL), sizeof(char));
}

char *hexa(char *value, TokenType base)
{
    FPoint number = break_str(value, ".");
    char *result = (char *)calloc(calculate_digits(decimal(value, base), TOKEN_HEXA), sizeof(char));

    switch (base)
    {
    case TOKEN_DECIMAL:
        unsigned int integer_number = atoi(number.integer);
        char ch;

        for (size_t i = 0; integer_number > 0; i++)
        {
            ch = decimal_to_hexa[integer_number % TOKEN_HEXA];
            integer_number /= TOKEN_HEXA;

            append_char(result, ch);
        }

        reverse_range(result, 0, strlen(result)-1);

        if (number.hasDecimal)
        {
            unsigned int decimal_number = atoi(number.decimal);
            double remainder = decimal_number / pow(10, strlen(number.decimal));
            size_t counter = 0;

            append_char(result, '.');

            for (;;)
            {
                if (remainder == 0.0f || counter == PRECISION)
                    break;

                remainder *= TOKEN_HEXA;
                ch = decimal_to_hexa[(int)remainder];
                append_char(result, ch);
                remainder -= floor(remainder);

                counter++;
            }
        }

        return result;
    case TOKEN_BINARY:
        return hexa(double_to_string(decimal(value, TOKEN_BINARY)), TOKEN_DECIMAL);
    case TOKEN_OCTAL:
        return hexa(double_to_string(decimal(value, TOKEN_OCTAL)), TOKEN_DECIMAL);
    default:
        break;
    }
}

char *binary(char *value, TokenType base)
{

    FPoint number = break_str(value, ".");
    char *result = (char *)calloc(calculate_digits(decimal(value, base), TOKEN_BINARY), sizeof(char));

    switch (base)
    {
    case TOKEN_DECIMAL:
        unsigned int integer_number = atoi(number.integer);
        char ch;

        for (size_t i = 0; integer_number > 0; i++)
        {
            ch = (integer_number % TOKEN_BINARY) + '0';
            integer_number /= TOKEN_BINARY;

            append_char(result, ch);
        }

        reverse_range(result, 0, strlen(result) - 1);

        if (number.hasDecimal)
        {
            unsigned int decimal_number = atoi(number.decimal);
            double remainder = decimal_number / pow(10, strlen(number.decimal));
            size_t counter = 0;

            append_char(result, '.');

            for (;;)
            {
                if (remainder == 0.0f || counter == PRECISION)
                    break;

                remainder *= TOKEN_BINARY;
                ch = (int)remainder + '0';
                append_char(result, ch);
                remainder -= floor(remainder);

                counter++;
            }
        }

        return result;
    case TOKEN_OCTAL:
        return binary(double_to_string(decimal(value, TOKEN_OCTAL)), TOKEN_DECIMAL);
    case TOKEN_HEXA:
        return binary(double_to_string(decimal(value, TOKEN_HEXA)), TOKEN_DECIMAL);
    default:
        break;
    }
}

double decimal(char *value, TokenType base)
{
    FPoint number = break_str(value, ".");
    double integer_sum = 0, decimal_sum = 0;

    for (size_t i = 0; i < strlen(number.integer); i++)
    {
        if (number.integer[i] == '0')
            continue;
        integer_sum += char_to_digit(number.integer[i]) * pow(base, strlen(number.integer) - i - 1);
    }

    if (number.hasDecimal)
        for (size_t i = 0; i < strlen(number.decimal); i++)
        {
            if (number.decimal[i] == '0')
                continue;
            decimal_sum += char_to_digit(number.decimal[i]) * pow(base, -(int)(i + 1));
        }

    return (number.hasDecimal) ? integer_sum + decimal_sum / pow(10, strlen(number.decimal - 1)) : integer_sum;
}