#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "util.h"

//------------------------------------------------------------------------------------
// Utilitary Functions Implementation (Static)
//------------------------------------------------------------------------------------

static void reverse_range(char *str, size_t start, size_t end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

static void append_char(char *str, char ch) {
    size_t len = strlen(str);
    str[len] = ch;
    str[len + 1] = '\0';
}

static void *twos(char *value) {
    size_t aux = strlen(value);

    while (value[aux] != '1')
        aux--;

    aux -= 1;

    for (aux; aux > 0; aux--) {
        if (value[aux] == '1')
            value[aux] = '0';
        else
            value[aux] = '1';
    }

    value[0] = (value[0] == '1') ? '0' : '1';

    return value;
}

static short int char_to_digit(char ch) {
    if (isdigit(ch))
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return 10 + (ch - 'A');
    if (ch >= 'a' && ch <= 'f')
        return 10 + (ch - 'a');
    return 0xFFFF;
}

static FPoint break_str(const char *value, const char *dot) {
    FPoint number;

    char *copy = strdup(value);
    if (!copy) return (FPoint){NULL, NULL, false};

    char *integer = strtok(copy, ".");
    char *decimal = strtok(NULL, ".");

    number.integer = strdup(integer);
    number.decimal = decimal ? strdup(decimal) : NULL;
    number.hasDecimal = decimal ? true : false;

    free(copy);

    return number;
}

static size_t calculate_digits(double number, TokenType base) {
    return (number == 0) ? 1 : (size_t)ceil(log(number) / log(base)) + 1;
}

//------------------------------------------------------------------------------------
// Utilitary Functions Implementation (Normal)
//------------------------------------------------------------------------------------

void throw(char *message, bool sucess) {
    if (sucess)
        printf("%soutput%s ~ %s\n", GREEN, RESET, message);
    else
        printf("%soutput%s ~ %s\n", RED, RESET, message);
}

bool ishexachar(char ch) {
    for (unsigned short int i = 0; i < strlen(hexa_char); i++)
        if (ch == hexa_char[i]) return true;

    return false;
}

bool isdot(char ch) {
    for (unsigned short int i = 0; i < strlen(dot_char); i++)
        if (ch == dot_char[i]) return true;

    return false;
}

char *binary(char *value, TokenType base) {
    bool isNegative = (value[0] == '-');
    if (isNegative) {
        value++;
        FPoint number_aux = break_str(binary(value, base), ".");
        char *aux = (char *)calloc(34, sizeof(char));

        memset(aux, '0', 16);

        if (strcmp(number_aux.integer, "0") != 0) {
            memcpy(aux + (16 - strlen(number_aux.integer)), number_aux.integer, strlen(number_aux.integer));
            twos(aux);
        }

        if (number_aux.hasDecimal) {
            append_char(aux, '.');
            strcat(aux, number_aux.decimal);
        }

        aux[strlen(aux)] = '\0';

        return aux;        
    }

    FPoint number = break_str(value, ".");
    char *result = (char *)calloc(calculate_digits(decimal(value, base), TOKEN_BINARY), sizeof(char));

    switch (base) {
    case TOKEN_DECIMAL:
        unsigned int integer_number = atoi(number.integer);
        char ch;

        if (integer_number == 0) append_char(result, '0');
        else for (size_t i = 0; integer_number > 0; i++) {
                ch = (integer_number % TOKEN_BINARY) + '0';
                integer_number /= TOKEN_BINARY;

                append_char(result, ch);
        }

        reverse_range(result, 0, strlen(result) - 1);

        if (number.hasDecimal) {
            unsigned int decimal_number = atoi(number.decimal);
            double remainder = decimal_number / pow(10, strlen(number.decimal));
            size_t counter = 0;

            append_char(result, '.');

            for (;;) {
                if (remainder == 0.0f || counter == PRECISION) break;

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
    default: break;
    }
}

char *octal(char *value, TokenType base) {
    bool isNegative = (value[0] == '-');
    if (isNegative) value++;

    FPoint number = break_str(value, ".");
    char *result = (char *)calloc(calculate_digits(decimal(value, base), TOKEN_OCTAL), sizeof(char));

    switch (base) {
    case TOKEN_DECIMAL:
        unsigned int integer_number = atoi(number.integer);
        char ch;

        if (integer_number == 0) append_char(result, '0');
        else for (size_t i = 0; integer_number > 0; i++) {
                ch = (integer_number % TOKEN_OCTAL) + '0';
                integer_number /= TOKEN_OCTAL;

                append_char(result, ch);
        }

        if (isNegative) append_char(result, '-');

        reverse_range(result, 0, strlen(result) - 1);

        if (number.hasDecimal) {
            unsigned int decimal_number = atoi(number.decimal);
            double remainder = decimal_number / pow(10, strlen(number.decimal));
            size_t counter = 0;

            append_char(result, '.');

            for (;;) {
                if (remainder == 0.0f || counter == PRECISION) break;

                remainder *= TOKEN_OCTAL;
                ch = (int)remainder + '0';
                append_char(result, ch);
                remainder -= floor(remainder);

                counter++;
            }
        }

        return result;
    case TOKEN_BINARY:
        return octal(double_to_string(decimal(value, TOKEN_BINARY)), TOKEN_DECIMAL);
    case TOKEN_HEXA:
        return octal(double_to_string(decimal(value, TOKEN_HEXA)), TOKEN_DECIMAL);
    default: break;
    }
}

char *hexa(char *value, TokenType base) {
    bool isNegative = (value[0] == '-');
    if (isNegative) value++;

    FPoint number = break_str(value, ".");
    char *result = (char *)calloc(calculate_digits(decimal(value, base), TOKEN_HEXA), sizeof(char));


    switch (base) {
    case TOKEN_DECIMAL:
        unsigned int integer_number = atoi(number.integer);
        char ch;

        if (integer_number == 0) append_char(result, '0');
        else for (size_t i = 0; integer_number > 0; i++) {
                ch = decimal_to_hexa[integer_number % TOKEN_HEXA];
                integer_number /= TOKEN_HEXA;

                append_char(result, ch);
        }

        if(isNegative) append_char(result, '-');

        reverse_range(result, 0, strlen(result) - 1);

        if (number.hasDecimal) {
            unsigned int decimal_number = atoi(number.decimal);
            double remainder = decimal_number / pow(10, strlen(number.decimal));
            size_t counter = 0;

            append_char(result, '.');

            for (;;) {
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
    default: break;
    }
}

char *double_to_string(double number) {
    size_t size = snprintf(NULL, 0, "%f", number);
    if (size < 0) return NULL;

    char *str = malloc(size + 1);
    if (!str) return NULL;

    snprintf(str, size + 1, "%f", number);

    FPoint fpoint = break_str(str, ".");

    return (atoi(fpoint.decimal) == 0) ? fpoint.integer : str;
}

char *string_in_given_base(char *value, TokenType src, TokenType dest) {
    switch (dest) {
    case TOKEN_BINARY:
        return binary(value, src);
    case TOKEN_OCTAL:
        return octal(value, src);
    case TOKEN_DECIMAL:
        return double_to_string(decimal(value, src));
    case TOKEN_HEXA:
        return hexa(value, src);
    default:
        throw("string_in_given_base, unknown base.", false);
        break;
    }
}

double decimal(char *value, TokenType base) {
    bool isNegative = (value[0] == '-');
    if (isNegative) value++;

    FPoint number = break_str(value, ".");
    double integer_sum = 0, decimal_sum = 0;

    for (size_t i = 0; i < strlen(number.integer); i++) {
        if (number.integer[i] == '0') continue;
        integer_sum += char_to_digit(number.integer[i]) * pow(base, strlen(number.integer) - i - 1);
    }

    if (number.hasDecimal)
        for (size_t i = 0; i < strlen(number.decimal); i++) {
            if (number.decimal[i] == '0') continue;
            decimal_sum += char_to_digit(number.decimal[i]) * pow(base, -(int)(i + 1));
        }

    double result = (number.hasDecimal) ? integer_sum + decimal_sum / pow(10, strlen(number.decimal - 1)) : integer_sum;

    return isNegative ? -result : result;
}