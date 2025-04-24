#ifndef UTIL_H
#define UTIL_H

#include <ctype.h>
#include <stdbool.h>
#include "lexer.h"

#if !defined(FPoint)
typedef struct
{
    char *integer;
    char *decimal;
    bool hasDecimal;
    bool isNegative;
} FPoint;
#endif

#ifndef PRECISION
#define PRECISION 8
#endif

static const char *hexa_char = "ABCDEF";
static const char *dot_char = ".,";
static const char decimal_to_hexa[16] = {
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'A',
    'B',
    'C',
    'D',
    'E',
    'F'};

bool ishexachar(char);
bool isdot(char);
static void append_char(char *, char);
char *double_to_string(double);
static void reverse_range(char *, size_t, size_t);
static short int char_to_digit(char);
static FPoint break_str(const char *, const char *);
static size_t calculate_digits(double, TokenType);
char *octal(char *, TokenType);
char *hexa(char *, TokenType);
char *binary(char *, TokenType);
double decimal(char *, TokenType);
char *string_in_given_base(char *value, TokenType src, TokenType dest);
#endif