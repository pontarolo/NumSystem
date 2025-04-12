#ifndef LEXER_H
#define LEXER_H

#if !defined(TokenType)
	typedef enum {
		TOKEN_PLUS,
		TOKEN_MINUS,
		TOKEN_MUL,
		TOKEN_DIV,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_NUMBER,
		TOKEN_BINARY = 2,
		TOKEN_OCTAL = 8,
		TOKEN_DECIMAL = 10,
		TOKEN_HEXA = 16,
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

Lexer lexer(char *);
Token next(Lexer *);


#endif
