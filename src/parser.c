#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "util.h"

static void eat(Parser *parser, TokenType type)
{
	if (parser->current_token.type == type)
	{
		free(parser->current_token.value);
		parser->current_token = next(parser->lexer);
	}
	// implementar erro
}

static double parse_factor(Parser *parser)
{
	Token token = parser->current_token;
	double result;

	if (token.type == TOKEN_LPAREN)
	{
		eat(parser, TOKEN_LPAREN);
		result = parse_expression(parser);
		eat(parser, TOKEN_RPAREN);
		return result;
	}

	eat(parser, token.type);
	if (token.type == TOKEN_BINARY || token.type == TOKEN_OCTAL || token.type == TOKEN_DECIMAL || token.type == TOKEN_HEXA)
	{
		eat(parser, TOKEN_LPAREN);
		result = decimal(parser->current_token.value, token.type);
		eat(parser, TOKEN_NUMBER);
		eat(parser, TOKEN_RPAREN);
		return result;
	}

	// implementar erro
}

static double parse_term(Parser *parser)
{
	double result = parse_factor(parser);

	while (parser->current_token.type == TOKEN_MUL || parser->current_token.type == TOKEN_DIV)
	{
		Token operand = parser->current_token;
		switch (operand.type)
		{
		case TOKEN_MUL:
			eat(parser, TOKEN_MUL);
			result *= parse_factor(parser);
			break;
		case TOKEN_DIV:
			eat(parser, TOKEN_DIV);
			result /= parse_factor(parser);
			break;
		default:
			// implementar erro
			break;
		}
	}

	return result;
}

static double parse_expression(Parser *parser)
{
	double result = parse_term(parser);

	while (parser->current_token.type == TOKEN_PLUS || parser->current_token.type == TOKEN_MINUS)
	{
		Token operand = parser->current_token;
		switch (operand.type)
		{
		case TOKEN_PLUS:
			eat(parser, TOKEN_PLUS);
			result += parse_term(parser);
			break;
		case TOKEN_MINUS:
			eat(parser, TOKEN_MINUS);
			result -= parse_term(parser);
			break;
		default:
			// implementar erro
			break;
		}
	}

	return result;
}

int main()
{
	Lexer lex = lexer("h(BADCAFE.BAD)");
	Parser parser = {&lex, next(&lex)};
	double result = parse_expression(&parser);
	printf("%lf\n", result);

	printf("---------- TESTES ----------\n");

	printf("binary: %s \n", hexa("1011101011011100101011111110", TOKEN_BINARY));
}
