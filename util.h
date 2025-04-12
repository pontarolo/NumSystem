#ifndef UTIL_H
#define UTIL_H

#include <ctype.h>
#include <stdbool.h>
#include "lexer.h"

static const char* hexa_chars = "ABCDEF";
static const char* delimiter_chars = ".,";
    
bool ishexachar(char);
bool isdelimiter(char);
unsigned short int char_to_digit(char);
double modulo(long long int);
double power(unsigned char, long long int);
double binary_to_decimal(char *value);
double octal_to_decimal(char *value);
double any_to_decimal(char *, TokenType);
char *string_in_given_base(const char *, TokenType, TokenType); 

#endif