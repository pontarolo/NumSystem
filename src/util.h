#ifndef UTIL_H
#define UTIL_H


//------------------------------------------------------------------------------------
// Includes and Definitions
//------------------------------------------------------------------------------------

#include <ctype.h>
#include <stdbool.h>
#include <float.h>
#include "lexer.h"
#include "../lib/colors/colors.h"

#ifndef PRECISION
    #define PRECISION 8
#endif

#ifndef COMPLEMENT_SIZE
    #define COMPLEMENT_SIZE 16
#endif

//----------------------------------------------------------------------------------
// Structures Definition
//----------------------------------------------------------------------------------

// Floating point struct
#if !defined(FPoint)
    typedef struct {
        char *integer;
        char *decimal;
        bool has_decimal;
    } FloatingPoint;
#endif

//------------------------------------------------------------------------------------
// Global Variables Definition
//------------------------------------------------------------------------------------

static const char g_valid_hexa_chars[TOKEN_HEXA] = {
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
static bool is_valid_number(char *, TokenType);
static char *twos_complement(char *, unsigned short int, TokenType);

// Don't call these directly
static FloatingPoint _break_number(const char *, const char *);
static size_t _calculate_digits(double, TokenType);
static void _reverse_range(char *, size_t, size_t);
static void _append_char(char *, char);
static void _sucessive_divisions(unsigned int, char *, TokenType);
static void _floating_point(double, char *, TokenType);
static short int _char_to_digit(char);
static char *_pad_left(char *, unsigned short int);
char *_char_to_string(char);
char *_double_to_string(double);
bool _is_hexa_char(char);

// Normal Functions
void throw(char *, bool);
char *binary(char *, TokenType);
char *octal(char *, TokenType);
char *hexa(char *, TokenType);
char *string_in_given_base(char *, TokenType, TokenType);
double decimal(char *, TokenType);

#if defined(_cplusplus)
}
#endif

#endif