#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
unsigned short int char_to_digit(char ch) {
    if (isdigit(ch)) return ch - '0';
    if (ch >= 'A' && ch <= 'F') return 10 + (ch - 'A');
    if (ch >= 'a' && ch <= 'f') return 10 + (ch - 'a');
    return 0xFFFF;
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

double any_to_decimal(char *value, TokenType base) {
    double integer_result = 0.0f;
    double decimal_result = 0.0f;
    unsigned short int digit;

    char *copy = strdup(value);
    if (!copy) return 0;

    char *integer = strtok(copy, ".");
    char *decimal = strtok(NULL, ".");

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