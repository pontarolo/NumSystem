#ifndef UTIL_H
#define UTIL_H

#include <ctype.h>
#include <stdbool.h>
#include "lexer.h"

static const char *hexa_chars = "ABCDEF";
static const char *delimiter_chars = ".,";
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
    "1111" 
};

static const char octal_to_bin[8][4] = {
    "000",
    "001",
    "010",
    "011",
    "100",
    "101",
    "110",
    "111" 
};

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
    'F'
};

bool ishexachar(char);
bool isdelimiter(char);
void append_char(char *, char);
void reverse_binary(char *); 
unsigned short int char_to_digit(char);
double floor(double);
double modulo(long long int);
double power(unsigned char, long long int);
char* any_to_binary(char *, TokenType) ;
double any_to_decimal(char *, TokenType);
char *string_in_given_base(const char *, TokenType, TokenType); 

#endif