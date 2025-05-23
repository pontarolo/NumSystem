#ifndef PARSER_H
#define PARSER_H

//------------------------------------------------------------------------------------
// Includes and Definitions
//------------------------------------------------------------------------------------

#include <stdlib.h>
#include <math.h>
#include "lexer.h"

//----------------------------------------------------------------------------------
// Structures Definition
//----------------------------------------------------------------------------------

// Parser struct
#if !defined(Parser)
	typedef struct {
		Lexer *lexer;
		Token current_token;
	} Parser;
#endif

//------------------------------------------------------------------------------------
// Parser Functions
//------------------------------------------------------------------------------------

#if defined(__cplusplus)
	extern "C" {            
#endif

// Don't call these directly
static void _eat(Parser *, TokenType);
static double _parse_factor(Parser *);
static double _parse_term(Parser *);

// Normal Functions
double parse_expression(Parser *);

#if defined(_cplusplus)
}
#endif

#endif