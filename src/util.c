//------------------------------------------------------------------------------------
// Includes and Definitions
//------------------------------------------------------------------------------------

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "util.h"

//------------------------------------------------------------------------------------
// Utilitary Functions Implementation (Static)
//------------------------------------------------------------------------------------

// Checks if a number contains only valid chars
static bool isValidNumber(char *value, TokenType base) {
    bool isValid = false;

    for (size_t i = 0; i < strlen(value); i++) {
        isValid = false;
        for (size_t j = 0; j < base; j++) if (value[i] == valid_hexa_chars[j] || value[i] == '.') isValid = true;
        if(!isValid) return false;
    }

    return true;
}

// Reverses an array in a given range
static void reverse_range(char *str, size_t start, size_t end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Add a char to the end of a string
static void append_char(char *str, char ch) {
    size_t len = strlen(str);
    str[len] = ch;
    str[len + 1] = '\0';
}

// Lower base conversions
static void sucessive_divisions(unsigned int value, char *result, TokenType base) {
    if (value == 0) append_char(result, '0');
    else for (size_t i = 0; value > 0; i++) {
        char ch = valid_hexa_chars[value % base];
        value /= base;
        append_char(result, ch);
    }
}

// For dealing with the decimal part of a given number
static void floating_point(double remainder, char *result, TokenType base) {
    for (size_t i = 0; (remainder != 0.0f || i == PRECISION); i++) {
        remainder *= base;
        char ch = valid_hexa_chars[(int)remainder];
        append_char(result, ch);
        remainder -= floor(remainder);            
    }
}

// Transforms a char to a digit
static short int char_to_digit(char ch) {
    if (isdigit(ch)) return ch - '0';
    if (ch >= 'A' && ch <= 'F') return 10 + (ch - 'A');
    if (ch >= 'a' && ch <= 'f') return 10 + (ch - 'a');
    return 0xFFFF;
}

// Needed for negative number representation
static char *twos_complement(char *value, unsigned short int size, TokenType base) {
    printf("%s\n", value);

    FPoint bin = break_str(value, ".");

    char *aux = (char *)calloc(size + PRECISION + 2, sizeof(char));

    strcpy(aux, pad_right(bin.integer, size));

    size_t i = 0;

    for (i = strlen(aux); aux[i] != '1'; i--);

    i -= 1;

    for (i; i > 0; i--) {
        if (aux[i] == '1') aux[i] = '0';
        else aux[i] = '1';
    }

    if (bin.hasDecimal) {
        printf("bin.decimal: %s\n", bin.decimal);
        append_char(aux, '.');
        strcat(aux, bin.decimal);
    }

    aux[0] = (aux[0] == '1') ? '0' : '1';
    aux[strlen(aux)] = '\0';

    return aux;
}

// Stuffing
static char *pad_right(char *value, unsigned short int size) {
        char *aux = (char *)calloc(size + 1, sizeof(char));

        memset(aux, '0', size);
        memcpy(aux + (size - strlen(value)), value, strlen(value));
        aux[strlen(aux)] = '\0';

        return aux;       
}

// Breaks the a given number in an integer part and a decimal part
static FPoint break_str(const char *value, const char *dot) {
    FPoint number = {NULL, NULL, false};
    const char *pos = strchr(value, dot[0]);

    if (pos) {
        size_t int_len = pos - value;
        number.integer = strndup(value, int_len);
        number.decimal = strdup(pos + 1);
        number.hasDecimal = true;
    } else {
        number.integer = strdup(value);
        number.decimal = NULL;
        number.hasDecimal = false;
    }

    return number;
}

// Calculates the number of digits of a number in a given base
static size_t calculate_digits(double number, TokenType base) {
    return (number == 0) ? 1 : (size_t)ceil(log(number) / log(base)) + 1;
}

//------------------------------------------------------------------------------------
// Utilitary Functions Implementation (Normal)
//------------------------------------------------------------------------------------

// Displays a message to the user
void throw(char *message, bool sucess) {
    if (sucess) printf("%soutput%s ~ %s\n", TEXT_GREEN, RESET, message);
    else printf("%soutput%s ~ %s\n", TEXT_RED, RESET, message);
}

// Checks if a given char is a hexadecimal digit
bool isHexaChar(char ch) {
    for (unsigned short int i = 0; i < TOKEN_HEXA; i++) if (ch == valid_hexa_chars[i]) return true;
    return false;
}

// Transforms a char into a valid string
char *char_to_string(char ch) {
    char *str = (char *)calloc(2, sizeof(char));
    str[0] = ch;
    str[1] = '\0';

    return str;
}

// Transforms any number in a binary string
char *binary(char *value, TokenType base) {
    bool isNegative = (value[0] == '-');
    if (isNegative) {
        value++;
        return twos_complement(binary(value, base), 16, base);
    }

    FPoint number = break_str(value, ".");
    char *result = (char *)calloc(calculate_digits(decimal(value, base), TOKEN_BINARY), sizeof(char));

    switch (base) {
        case TOKEN_DECIMAL:
            unsigned int integer_number = atoi(number.integer);
            sucessive_divisions(integer_number, result, TOKEN_BINARY);
            reverse_range(result, 0, strlen(result) - 1);

            if (number.hasDecimal) {
                append_char(result, '.');
                floating_point(atoi(number.decimal) / pow(10, strlen(number.decimal)), result, TOKEN_BINARY);
            }

            return result;
        case TOKEN_OCTAL:
            return binary(double_to_string(decimal(value, TOKEN_OCTAL)), TOKEN_DECIMAL);
        case TOKEN_HEXA:
            return binary(double_to_string(decimal(value, TOKEN_HEXA)), TOKEN_DECIMAL);
        default: break;
    }
}

// Transforms any number in a octal string
char *octal(char *value, TokenType base) {
    bool isNegative = (value[0] == '-');
    if (isNegative) value++;

    FPoint number = break_str(value, ".");
    char *result = (char *)calloc(calculate_digits(decimal(value, base), TOKEN_OCTAL), sizeof(char));

    switch (base) {
        case TOKEN_DECIMAL:
            unsigned int integer_number = atoi(number.integer);
            sucessive_divisions(integer_number, result, TOKEN_OCTAL);
            if (isNegative) append_char(result, '-');
            reverse_range(result, 0, strlen(result) - 1);

            if (number.hasDecimal) {
                append_char(result, '.');
                floating_point(atoi(number.decimal) / pow(10, strlen(number.decimal)), result, TOKEN_OCTAL);
            }

            return result;
        case TOKEN_BINARY:
            return octal(double_to_string(decimal(value, TOKEN_BINARY)), TOKEN_DECIMAL);
        case TOKEN_HEXA:
            return octal(double_to_string(decimal(value, TOKEN_HEXA)), TOKEN_DECIMAL);
        default: break;
    }
}

// Transforms any number in a hexadecimal string
char *hexa(char *value, TokenType base) {
    bool isNegative = (value[0] == '-');
    if (isNegative) value++;

    FPoint number = break_str(value, ".");
    char *result = (char *)calloc(calculate_digits(decimal(value, base), TOKEN_HEXA), sizeof(char));


    switch (base) {
        case TOKEN_DECIMAL:
            unsigned int integer_number = atoi(number.integer);
            sucessive_divisions(integer_number, result, TOKEN_HEXA);
            if(isNegative) append_char(result, '-');
            reverse_range(result, 0, strlen(result) - 1);

            if (number.hasDecimal) {
                append_char(result, '.');
                floating_point(atoi(number.decimal) / pow(10, strlen(number.decimal)), result, TOKEN_HEXA);
            }

            return result;
        case TOKEN_BINARY:
            return hexa(double_to_string(decimal(value, TOKEN_BINARY)), TOKEN_DECIMAL);
        case TOKEN_OCTAL:
            return hexa(double_to_string(decimal(value, TOKEN_OCTAL)), TOKEN_DECIMAL);
        default: break;
    }
}

// Transforms a double in a valid string
char *double_to_string(double number) {
    size_t size = snprintf(NULL, 0, "%f", number);
    if (size < 0) return NULL;

    char *str = malloc(size + 1);
    if (!str) return NULL;
    
    snprintf(str, size + 1, "%f", number);

    FPoint fpoint = break_str(str, ".");

    return (atoi(fpoint.decimal) == 0) ? fpoint.integer : str;
}

// Tranforms any number in any base to a number in any base
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

// Transforms any number in a decimal value
double decimal(char *value, TokenType base) {
    bool isNegative = (value[0] == '-');
    if (isNegative) value++;

    if (!isValidNumber(value, base)) return NAN;

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

    return isNegative ? -(integer_sum + decimal_sum) : integer_sum + decimal_sum;
}