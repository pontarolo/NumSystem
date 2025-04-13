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
} FPoint;
#endif

#ifndef PRECISION
#define PRECISION 8
#endif

static const char *hexa_char = "ABCDEF";
static const char *dot_char = ".,";
static const char hex_to_bin[16][5] = {
    "0000",
    "0001",
    "0010",
    "0011",
    "0100",
    "0101",
    "0110",
    "0111",
    "1000",
    "1001",
    "1010",
    "1011",
    "1100",
    "1101",
    "1110",
    "1111"};

static const char octal_to_bin[8][4] = {
    "000",
    "001",
    "010",
    "011",
    "100",
    "101",
    "110",
    "111"};

static const char decimal_to_hex[16] = {
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
static char *double_to_string(double);
static void reverse_range(char *, size_t, size_t);
static unsigned short int char_to_digit(char);
static FPoint break_str(const char *, const char *);
static size_t calculate_digits(double, TokenType);
char *hexa(char *, TokenType);
char *binary(char *, TokenType);
double decimal(char *, TokenType);
#endif