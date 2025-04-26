#ifndef UTIL_H
#define UTIL_H

#include <ctype.h>
#include <stdbool.h>
#include "lexer.h"
#include "../lib/colors/colors.h"

#ifndef PRECISION
    #define PRECISION 8
#endif

//----------------------------------------------------------------------------------
// Structures Definition
//----------------------------------------------------------------------------------

// Floating point struct
#if !defined(FPoint)
    typedef struct {
        char *integer;
        char *decimal;
        bool hasDecimal;
    } FPoint;
#endif

//------------------------------------------------------------------------------------
// Global Variables Definition
//------------------------------------------------------------------------------------

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
    'F'
};

//------------------------------------------------------------------------------------
// Utilitary Functions
//------------------------------------------------------------------------------------

#if defined(__cplusplus)
    extern "C" {            
#endif

// Static Functions

static void reverse_range(char *, size_t, size_t);
static void append_char(char *, char);
static void *twos(char *);
static short int char_to_digit(char);
static FPoint break_str(const char *, const char *);
static size_t calculate_digits(double, TokenType);

// Normal Functions
void throw(char *, bool);
bool ishexachar(char);
bool isdot(char);
char *binary(char *, TokenType);
char *octal(char *, TokenType);
char *hexa(char *, TokenType);
char *double_to_string(double);
char *string_in_given_base(char *value, TokenType src, TokenType dest);
double decimal(char *, TokenType);

#if defined(_cplusplus)
}
#endif

#endif