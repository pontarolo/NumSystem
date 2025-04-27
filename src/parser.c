//------------------------------------------------------------------------------------
// Includes and Definitions
//------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "util.h"

//------------------------------------------------------------------------------------
// Parser Functions Implementation (Static)
//------------------------------------------------------------------------------------

// Parser advance
static void _eat(Parser *parser, TokenType type) {
	if (parser->current_token.type == type) {
		free(parser->current_token.value);
		parser->current_token = _next(parser->lexer);
	} else
		throw("Can't eat the given token.", false);
}

// For parsing the number themselves
static double _parse_factor(Parser *parser) {
	Token token = parser->current_token;
	double result;

	if (token.type == TOKEN_LPAREN) {
		_eat(parser, TOKEN_LPAREN);
		result = parse_expression(parser);
		_eat(parser, TOKEN_RPAREN);
		return result;
	}

	_eat(parser, token.type);
	if ((token.type == TOKEN_BINARY || token.type == TOKEN_OCTAL || token.type == TOKEN_DECIMAL || token.type == TOKEN_HEXA) && !isnan(decimal(parser->current_token.value, token.type))) {
		result = decimal(parser->current_token.value, token.type);
		_eat(parser, TOKEN_NUMBER);
		return result;
	} else {
		throw("Invalid number.", false);
		return NAN;
	}
}

// For parsing multiplication and division
static double _parse_term(Parser *parser) {
	double result = _parse_factor(parser);

	while (parser->current_token.type == TOKEN_MUL || parser->current_token.type == TOKEN_DIV) {
		Token operand = parser->current_token;
		switch (operand.type) {
		case TOKEN_MUL:
			_eat(parser, TOKEN_MUL);
			result *= _parse_factor(parser);
			break;
		case TOKEN_DIV:
			_eat(parser, TOKEN_DIV);
			result /= _parse_factor(parser);

			if (result == INFINITY) throw("Division by zero", false);

			break;
		default:
			throw("Invalid term.", false);
			break;
		}
	}

	return result;
}

//------------------------------------------------------------------------------------
// Parser Functions Implementation (Normal)
//------------------------------------------------------------------------------------

// For parsing plus and minus
double parse_expression(Parser *parser) {
	double result = _parse_term(parser);

	if (result == INFINITY) return result;

	while (parser->current_token.type == TOKEN_PLUS || parser->current_token.type == TOKEN_MINUS) {
		Token operand = parser->current_token;
		switch (operand.type) {
		case TOKEN_PLUS:
			_eat(parser, TOKEN_PLUS);
			result += _parse_term(parser);
			break;
		case TOKEN_MINUS:
			_eat(parser, TOKEN_MINUS);
			result -= _parse_term(parser);
			break;
		default:
			throw("Invalid expression.", false);
			break;
		}
	}

	return result;
}