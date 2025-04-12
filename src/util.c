#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "util.h"

bool ishexachar(char ch)
{
    for (unsigned short int i = 0; i < strlen(hexa_chars); i++)
        if (ch == hexa_chars[i])
            return true;

    return false;
}

bool isdelimiter(char ch)
{
    for (unsigned short int i = 0; i < strlen(delimiter_chars); i++)
        if (ch == delimiter_chars[i])
            return true;

    return false;
}

void append_char(char *str, char ch)
{
    size_t len = strlen(str);
    str[len] = ch;
    str[len + 1] = '\0';

}

char *double_to_string(double number) {
    size_t size = snprintf(NULL, 0, "%f", number);
    if (size < 0) return NULL;

    char *str = malloc(size + 1);
    if (!str) return NULL;

    snprintf(str, size + 1, "%f", number);

    return str;
}

void reverse_range(char *str, size_t start, size_t end)
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

unsigned short int char_to_digit(char ch)
{
    if (isdigit(ch))
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return 10 + (ch - 'A');
    if (ch >= 'a' && ch <= 'f')
        return 10 + (ch - 'a');
    return 0xFFFF;
}

double floor(double number)
{
    unsigned int floor = (unsigned int)number;
    return floor;
}

double modulo(long long int number)
{
    return (number > 0) ? number : -number;
}

double power(unsigned char base, long long int exponent)
{
    double result = 1.0f;

    if (base == 0 && exponent == 0)
    {
        return 0;
    }
    else if ((base == 1 && exponent >= 0) || (base != 0 && exponent == 0))
    {
        return 1;
    }

    for (size_t i = 0; i < modulo(exponent); i++)
        result *= base;

    result = (exponent > 0) ? result : 1 / result;

    return result;
}

char *any_to_hexa(char *value, TokenType base)
{
    char *copy = strdup(value);
    if (!copy)
        return 0;

    char *integer = strtok(copy, ".");
    char *decimal = strtok(NULL, ".");

    char *result = (char *)calloc(strlen(value) * 2 + 2, sizeof(char));

    switch (base)
    {
    case TOKEN_BINARY:
        char bin_str[5];

        for (size_t i = 0; i < strlen(integer); i += 4)
        {
            size_t j;
            for (j = 0; j < 4 && (i + j) < strlen(integer); j++)
                bin_str[j] = integer[i + j];

            bin_str[j] = '\0';
            append_char(result, decimal_to_hex[(int)any_to_decimal(bin_str, 2)]);
        }

        if (decimal)
        {
            append_char(result, '.');
            for (size_t i = 0; i < strlen(decimal); i += 4)
            {
                size_t j;
                for (j = 0; j < 4 && (i + j) < strlen(decimal); j++)
                    bin_str[j] = decimal[i + j];

                bin_str[j] = '\0';
                append_char(result, decimal_to_hex[(int)any_to_decimal(bin_str, 2)]);
            }
        }

        break;

    case TOKEN_OCTAL:
        return any_to_hexa(any_to_binary(value, 8), 2);
    case TOKEN_DECIMAL:
        return any_to_hexa(any_to_binary(value, 10), 2);
    default:
        break;
    }

    return result;
}

char *any_to_binary(char *value, TokenType base)
{
    char *copy = strdup(value);
    if (!copy)
        return 0;

    char *integer = strtok(copy, ".");
    char *decimal = strtok(NULL, ".");

    size_t len = (decimal) ? strlen(decimal) : 0;
    unsigned short int dot = (decimal) ? 1 : 0;

    size_t capacity = (base == TOKEN_HEXA || base == TOKEN_DECIMAL) ? (strlen(integer) + len) * 4 + dot : (strlen(integer) + len) * 3 + dot;
    char *result = (char *)calloc(capacity, sizeof(char));

    switch (base)
    {
    case TOKEN_DECIMAL:
        unsigned int int_integer = atoi(integer);
        char ch;

        for (size_t i = 0; int_integer > 0; i++)
        {
            ch = (int_integer % 2) + '0';
            int_integer /= 2;

            append_char(result, ch);
        }

        if (decimal)
        {
            result[strlen(result)] = '.';

            unsigned int int_decimal = atoi(decimal);
            double remainder = int_decimal / power(10, strlen(decimal));

            for (size_t i = 0; i < strlen(decimal); i++)
            {
                remainder *= 2;
                ch = (int)remainder + '0';
                append_char(result, ch);
                remainder -= floor(remainder);

                if (remainder == 0.0f)
                    break;
            }
        }

        if (strchr(result, '.')) {
            size_t dot_pos = strchr(result, '.') - result;

            reverse_range(result, 0, dot_pos - 1);

            reverse_range(result, dot_pos + 1, strlen(result) - 1);
        } else 
            reverse_range(result, 0, strlen(result) - 1);
        break;
    case TOKEN_OCTAL:
        return any_to_binary(double_to_string(any_to_decimal(value, TOKEN_OCTAL)), TOKEN_DECIMAL);
    case TOKEN_HEXA:
            return any_to_binary(double_to_string(any_to_decimal(value, 16)), 2);
        break;
    default:
        break;
    }

    return result;
}

double any_to_decimal(char *value, TokenType base)
{
    double integer_result = 0.0f;
    double decimal_result = 0.0f;
    unsigned short int digit;

    char *copy = strdup(value);
    if (!copy)
        return 0;

    char *integer = strtok(copy, ".");
    char *decimal = strtok(NULL, ".");

    for (size_t i = 0; i < strlen(integer); i++)
    {
        digit = char_to_digit(integer[i]);
        if (digit >= 0 && digit < base)
            integer_result += digit * power(base, strlen(integer) - i - 1);
    }

    if (decimal)
        for (size_t i = 0; i < strlen(decimal); i++)
        {
            digit = char_to_digit(decimal[i]);
            if (digit >= 0 && digit < base)
                decimal_result += digit * power(base, -(i + 1));
        }

    free(copy);

    return integer_result + decimal_result;
}