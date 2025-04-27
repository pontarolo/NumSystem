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
static bool is_valid_number(char *value, TokenType base) {
    bool isValid = false;

    for (size_t i = 0; i < strlen(value); i++) {
        isValid = false;
        for (size_t j = 0; j < base; j++) if (value[i] == g_valid_hexa_chars[j] || value[i] == '.') isValid = true;
        if(!isValid) return false;
    }

    return true;
}

// Reverses an array in a given range
static void _reverse_range(char *str, size_t start, size_t end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Add a char to the end of a string
static void _append_char(char *str, char ch) {
    size_t len = strlen(str);
    str[len] = ch;
    str[len + 1] = '\0';
}

// Lower base conversions
static void _sucessive_divisions(unsigned int value, char *result, TokenType base) {
    if (value == 0) _append_char(result, '0');
    else for (size_t i = 0; value > 0; i++) {
        char ch = g_valid_hexa_chars[value % base];
        value /= base;
        _append_char(result, ch);
    }
}

// For dealing with the decimal part of a given number
static void _floating_point(double remainder, char *result, TokenType base) {
    for (size_t i = 0; (remainder != 0.0f || i == PRECISION); i++) {
        remainder *= base;
        char ch = g_valid_hexa_chars[(int)remainder];
        _append_char(result, ch);
        remainder -= floor(remainder);            
    }
}

// Transforms a char to a digit
static short int _char_to_digit(char ch) {
    if (isdigit(ch)) return ch - '0';
    if (ch >= 'A' && ch <= 'F') return 10 + (ch - 'A');
    if (ch >= 'a' && ch <= 'f') return 10 + (ch - 'a');
    return 0xFFFF;
}

// Needed for negative number representation
static char *twos_complement(char *value, unsigned short int size, TokenType base) {
    
    if (strlen(value) >= COMPLEMENT_SIZE) size *= 2;

    FloatingPoint bin = _break_number(value, ".");
    char *aux = (char *)calloc(size + PRECISION + 2, sizeof(char));

    strcpy(aux, _pad_left(bin.integer, size));

    size_t i = 0;

    for (i = strlen(aux); aux[i] != '1'; i--);

    i -= 1;

    for (i; i > 0; i--) {
        if (aux[i] == '1') aux[i] = '0';
        else aux[i] = '1';
    }

    if (bin.has_decimal) {
        _append_char(aux, '.');
        strcat(aux, bin.decimal);
    }

    aux[0] = (aux[0] == '1') ? '0' : '1';
    aux[strlen(aux)] = '\0';

    return aux;
}

// Stuffing
static char *_pad_left(char *value, unsigned short int size) {
    char *aux = (char *)calloc(size + 1, sizeof(char));

    memset(aux, '0', size);
    memcpy(aux + (size - strlen(value)), value, strlen(value));
    aux[strlen(aux)] = '\0';

    return aux;       
}

// Breaks the a given number in an integer part and a decimal part
static FloatingPoint _break_number(const char *value, const char *dot) {
    FloatingPoint number = {NULL, NULL, false};
    const char *pos = strchr(value, dot[0]);

    if (pos) {
        size_t int_len = pos - value;
        number.integer = strndup(value, int_len);
        number.decimal = strdup(pos + 1);
        number.has_decimal = true;
    } else {
        number.integer = strdup(value);
        number.decimal = NULL;
        number.has_decimal = false;
    }

    return number;
}

// Calculates the number of digits of a number in a given base
static size_t _calculate_digits(double number, TokenType base) {
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
bool _is_hexa_char(char ch) {
    for (unsigned short int i = 0; i < TOKEN_HEXA; i++) if (ch == g_valid_hexa_chars[i]) return true;
    return false;
}

// Transforms a char into a valid string
char *_char_to_string(char ch) {
    char *str = (char *)calloc(2, sizeof(char));
    str[0] = ch;
    str[1] = '\0';

    return str;
}

// Transforms any number in a binary string
char *binary(char *value, TokenType base) {
    bool is_negative = (value[0] == '-');
    if (is_negative) {
        value++;
        return twos_complement(binary(value, base), COMPLEMENT_SIZE, base);
    }

    FloatingPoint number = _break_number(value, ".");
    char *result = (char *)calloc(_calculate_digits(decimal(value, base), TOKEN_BINARY), sizeof(char));

    switch (base) {
        case TOKEN_DECIMAL:
            unsigned int integer_number = atoi(number.integer);
            _sucessive_divisions(integer_number, result, TOKEN_BINARY);
            _reverse_range(result, 0, strlen(result) - 1);

            if (number.has_decimal) {
                _append_char(result, '.');
                _floating_point(atoi(number.decimal) / pow(10, strlen(number.decimal)), result, TOKEN_BINARY);
            }

            return result;
        case TOKEN_OCTAL:
            return binary(_double_to_string(decimal(value, TOKEN_OCTAL)), TOKEN_DECIMAL);
        case TOKEN_HEXA:
            return binary(_double_to_string(decimal(value, TOKEN_HEXA)), TOKEN_DECIMAL);
        default: break;
    }
}

// Transforms any number in a octal string
char *octal(char *value, TokenType base) {
    bool is_negative = (value[0] == '-');
    if (is_negative) value++;

    FloatingPoint number = _break_number(value, ".");
    char *result = (char *)calloc(_calculate_digits(decimal(value, base), TOKEN_OCTAL), sizeof(char));

    switch (base) {
        case TOKEN_DECIMAL:
            unsigned int integer_number = atoi(number.integer);
            _sucessive_divisions(integer_number, result, TOKEN_OCTAL);
            if (is_negative) _append_char(result, '-');
            _reverse_range(result, 0, strlen(result) - 1);

            if (number.has_decimal) {
                _append_char(result, '.');
                _floating_point(atoi(number.decimal) / pow(10, strlen(number.decimal)), result, TOKEN_OCTAL);
            }

            return result;
        case TOKEN_BINARY:
            return octal(_double_to_string(decimal(value, TOKEN_BINARY)), TOKEN_DECIMAL);
        case TOKEN_HEXA:
            return octal(_double_to_string(decimal(value, TOKEN_HEXA)), TOKEN_DECIMAL);
        default: break;
    }
}

// Transforms any number in a hexadecimal string
char *hexa(char *value, TokenType base) {
    bool is_negative = (value[0] == '-');
    if (is_negative) value++;

    FloatingPoint number = _break_number(value, ".");
    char *result = (char *)calloc(_calculate_digits(decimal(value, base), TOKEN_HEXA), sizeof(char));


    switch (base) {
        case TOKEN_DECIMAL:
            unsigned int integer_number = atoi(number.integer);
            _sucessive_divisions(integer_number, result, TOKEN_HEXA);
            if(is_negative) _append_char(result, '-');
            _reverse_range(result, 0, strlen(result) - 1);

            if (number.has_decimal) {
                _append_char(result, '.');
                _floating_point(atoi(number.decimal) / pow(10, strlen(number.decimal)), result, TOKEN_HEXA);
            }

            return result;
        case TOKEN_BINARY:
            return hexa(_double_to_string(decimal(value, TOKEN_BINARY)), TOKEN_DECIMAL);
        case TOKEN_OCTAL:
            return hexa(_double_to_string(decimal(value, TOKEN_OCTAL)), TOKEN_DECIMAL);
        default: break;
    }
}

// Transforms a double in a valid string
char *_double_to_string(double number) {
    size_t size = snprintf(NULL, 0, "%f", number);
    if (size < 0) return NULL;

    char *str = (char *)calloc(size + 1, sizeof(char));
    if (!str) return NULL;
    
    snprintf(str, size + 1, "%f", number);

    FloatingPoint FloatingPoint = _break_number(str, ".");

    return (atoi(FloatingPoint.decimal) == 0) ? FloatingPoint.integer : str;
}

// Tranforms any number in any base to a number in any base
char *string_in_given_base(char *value, TokenType src, TokenType dest) {
    switch (dest) {
    case TOKEN_BINARY:
        return binary(value, src);
    case TOKEN_OCTAL:
        return octal(value, src);
    case TOKEN_DECIMAL:
        return _double_to_string(decimal(value, src));
    case TOKEN_HEXA:
        return hexa(value, src);
    default:
        throw("string_in_given_base, unknown base.", false);
        break;
    }
}

// Transforms any number in a decimal value
double decimal(char *value, TokenType base) {
    bool is_negative = (value[0] == '-');
    if (is_negative) value++;

    if (!is_valid_number(value, base)) return NAN;

    FloatingPoint number = _break_number(value, ".");
    double integer_sum = 0, decimal_sum = 0;

    for (size_t i = 0; i < strlen(number.integer); i++) {
        if (number.integer[i] == '0') continue;
        integer_sum += _char_to_digit(number.integer[i]) * pow(base, strlen(number.integer) - i - 1);
    }

    if (number.has_decimal)
        for (size_t i = 0; i < strlen(number.decimal); i++) {
            if (number.decimal[i] == '0') continue;
            decimal_sum += _char_to_digit(number.decimal[i]) * pow(base, -(int)(i + 1));
        }

    return is_negative ? -(integer_sum + decimal_sum) : integer_sum + decimal_sum;
}