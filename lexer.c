#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

static const char* hexa_chars = "ABCDEF";

#if !defined(TokenType)
	typedef enum {
		TOKEN_PLUS,
		TOKEN_MINUS,
		TOKEN_MUL,
		TOKEN_DIV,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_NUMBER,
		TOKEN_BINARY,
		TOKEN_OCTAL,
		TOKEN_DECIMAL,
		TOKEN_HEXA,
		TOKEN_UNKNOWN,
		TOKEN_END,
	} TokenType;
#endif

#if !defined(Token)
	typedef struct {
		TokenType type;
		char *value;
	} Token;

#endif

#if !defined(Lexer)
	typedef struct {
		char *text;
		size_t pos;
	} Lexer;
#endif

static unsigned short int ishexachar(char ch) {
	for (unsigned short int i = 0; i < strlen(hexa_chars); i++)
		if (ch == hexa_chars[i]) return 1;

	return 0;
}

Lexer lexer(char *text) {
	Lexer lex = {text, 0};
	return lex;
}

Token next(Lexer *lex) {
	while (lex->text[lex->pos] != '\0') {
		char ch = lex->text[lex->pos];
		if (isspace(ch)) {
			lex->pos++;
			continue;
		}

		if (isdigit(ch) || ishexachar(ch)) {
			size_t num_start = lex->pos;
			char *value;

			while (isdigit(lex->text[lex->pos]) || ishexachar(lex->text[lex->pos])) {
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
			case '+': return (Token){TOKEN_PLUS, strdup("+")};
			case '-': return (Token){TOKEN_MINUS, strdup("-")};
			case '*': return (Token){TOKEN_MUL, strdup("*")};
			case '/': return (Token){TOKEN_DIV, strdup("/")};
			case '(': return (Token){TOKEN_LPAREN, strdup("(")};
			case ')': return (Token){TOKEN_RPAREN, strdup(")")};
			case 'b': return (Token){TOKEN_BINARY, strdup("b")};
			case 'o': return (Token){TOKEN_OCTAL, strdup("o")};
			case 'd': return (Token){TOKEN_DECIMAL, strdup("d")};
			case 'h': return (Token){TOKEN_HEXA, strdup("h")};
			default: return (Token){TOKEN_UNKNOWN, NULL};
		}
	}

	return (Token){TOKEN_END, strdup("END")};
}

int main() {
	Lexer lex = lexer("b(010001110)+d(55)*o(21)/h(BADCAFE)");
	Token token;

	do {
		token = next(&lex);
		printf("Type: %d, Value: %s\n", token.type, token.value);
		free(token.value);
	} while (token.type != TOKEN_END);
}
