#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "util.h"

bool ishexachar(char ch) {
	for (unsigned short int i = 0; i < strlen(hexa_chars); i++)
		if (ch == hexa_chars[i]) return true;

	return false;
}

bool isdelimiter(char ch) {
    for (unsigned short int i = 0; i < strlen(delimiter_chars); i++)
		if (ch == delimiter_chars[i]) return true;

	return false;
}

void append_char(char *str, char ch) {
    str[strlen(str)] = ch;
    str[strlen(str)+1] = '\0';
}

void reverse_binary(char *str) {

}

unsigned short int char_to_digit(char ch) {
    if (isdigit(ch)) return ch - '0';
    if (ch >= 'A' && ch <= 'F') return 10 + (ch - 'A');
    if (ch >= 'a' && ch <= 'f') return 10 + (ch - 'a');
    return 0xFFFF;
}

double floor(double number) {
    unsigned int floor = (unsigned int)number;
    return floor;
}

double modulo(long long int number) {
    return (number > 0) ? number : -number;
}

double power(unsigned char base, long long int exponent) {
    double result = 1.0f;

    if (base == 0 && exponent == 0) {
        return 0;
    } else if ((base == 1 && exponent >= 0) || (base != 0 && exponent == 0)) {
        return 1;
    }

    for (size_t i = 0; i < modulo(exponent); i++)
            result *= base;

    result = (exponent > 0) ? result : 1/result;

    return result;
}

char *any_to_hexa(char *value, TokenType base) {
    
}

char* any_to_binary(char *value, TokenType base) {
    char *copy = strdup(value);
    if (!copy) return 0;

    char *integer = strtok(copy, ".");
    char *decimal = strtok(NULL, ".");

    size_t len = (decimal) ? strlen(decimal) : 0;
    unsigned short int dot = (decimal) ? 1 : 0;

    size_t capacity = (base == TOKEN_HEXA || base == TOKEN_DECIMAL) ? (strlen(integer)+len)*4+dot : (strlen(integer)+len)*3+dot;
    char* result = (char *)calloc(capacity, sizeof(char));

    switch (base) {
        case TOKEN_HEXA:
            for (size_t i = 0; i < strlen(integer); i++)
                strcat(result, hex_to_bin[char_to_digit(integer[i])]);

            if (decimal) {
                result[strlen(result)] = '.';

                for (size_t i = 0; i < strlen(decimal); i++)
                    strcat(result, hex_to_bin[char_to_digit(decimal[i])]);
            }

            break;
        case TOKEN_OCTAL:
            for (size_t i = 0; i < strlen(integer); i++)
                strcat(result, octal_to_bin[char_to_digit(integer[i])]);

            if (decimal) {
                result[strlen(result)] = '.';

                for (size_t i = 0; i < strlen(decimal); i++)
                    strcat(result, octal_to_bin[char_to_digit(decimal[i])]);
            }

            break;
        case TOKEN_DECIMAL:
            unsigned int int_integer = atoi(integer);
            char ch;

            for (size_t i = 0; int_integer > 0; i++) {
                ch = (int_integer % 2) + '0';
                int_integer /= 2;

                append_char(result, ch);
            }

            if (decimal) {
                result[strlen(result)] = '.';
                
                unsigned int int_decimal = atoi(decimal);
                double remainder = int_decimal/power(10, strlen(decimal));

                for (size_t i = 0; i < strlen(decimal) + 4; i++) {
                    remainder *= 2;
                    ch = (int)remainder + '0';
                    append_char(result, ch);
                    remainder -= floor(remainder);

                    if (remainder == 0.0f) break;
                }
            }

            break;
        default:
            break;
    }

    return result;
}

double any_to_decimal(char *value, TokenType base) {
    double integer_result = 0.0f;
    double decimal_result = 0.0f;
    unsigned short int digit;

    char *copy = strdup(value);
    if (!copy) return 0;

    char *integer = strtok(copy, ".");
    char *decimal = strtok(NULL, ".");

    if (base == TOKEN_HEXA) {
        return any_to_decimal(any_to_binary(value, 16), 2);
    }

    for (size_t i = 0; i < strlen(integer); i++) {
        digit = char_to_digit(integer[i]);
        if (digit >= 0 && digit < base) integer_result += digit * power(base, strlen(integer)- i - 1);
    }

    if (decimal)
        for (size_t i = 0; i < strlen(decimal); i++) {
            digit = char_to_digit(decimal[i]);
            if (digit >= 0 && digit < base) decimal_result += digit * power(base, -(i+1));
        }

    free(copy);
    
    return integer_result + decimal_result;
}


char *string_in_given_base(const char *value, TokenType src, TokenType dest) {
	
}