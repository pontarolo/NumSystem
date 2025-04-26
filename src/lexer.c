#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "util.h"
#include "../lib/colors/colors.h"

//------------------------------------------------------------------------------------
// Lexer and Token Functions Implementation
//------------------------------------------------------------------------------------

// Initializes a new lexer
Lexer lexer(char *text) {
	Lexer lex = {text, 0};
	return lex;
}

// Tokenizer
Token next(Lexer *lex) {
	while (lex->text[lex->pos] != '\0') {
		char ch = lex->text[lex->pos];
		if (isspace(ch)) {
			lex->pos++;
			continue;
		}

		if (isdigit(ch) || ishexachar(ch) || isdot(ch)) {
			size_t num_start = lex->pos;
			char *value;

			while (isdigit(lex->text[lex->pos]) || ishexachar(lex->text[lex->pos]) || isdot(lex->text[lex->pos])) {
				lex->pos++;
			}

			size_t len = lex->pos - num_start;
			value = (char *)calloc(len + 1, sizeof(char));
			memcpy(value, &lex->text[num_start], len);
			value[len] = '\0';

			return (Token){TOKEN_NUMBER, value};
		}

		lex->pos++;

		switch (ch) {
		case '+':
			return (Token){TOKEN_PLUS, strdup("+")};
		case '-':
			return (Token){TOKEN_MINUS, strdup("-")};
		case '*':
			return (Token){TOKEN_MUL, strdup("*")};
		case '/':
			return (Token){TOKEN_DIV, strdup("/")};
		case '(':
			return (Token){TOKEN_LPAREN, strdup("(")};
		case ')':
			return (Token){TOKEN_RPAREN, strdup(")")};
		case 'b':
			return (Token){TOKEN_BINARY, strdup("b")};
		case 'o':
			return (Token){TOKEN_OCTAL, strdup("o")};
		case 'd':
			return (Token){TOKEN_DECIMAL, strdup("d")};
		case 'h':
			return (Token){TOKEN_HEXA, strdup("h")};
		default:
			return (Token){TOKEN_UNKNOWN, NULL};
		}
	}

	return (Token){TOKEN_END, strdup("END")};
}