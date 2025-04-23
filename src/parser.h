#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <stdlib.h>

#if !defined(Parser)
typedef struct
{
    Lexer *lexer;
    Token current_token;
} Parser;
#endif

static void eat(Parser *, TokenType);
static double parse_factor(Parser *);
static double parse_term(Parser *);
double parse_expression(Parser *);

#endif
