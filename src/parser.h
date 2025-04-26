#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
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

// Static Functions
static void eat(Parser *, TokenType);
static double parse_factor(Parser *);
static double parse_term(Parser *);

// Normal Functions
double parse_expression(Parser *);

#if defined(_cplusplus)
}
#endif

#endif