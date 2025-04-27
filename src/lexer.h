#ifndef LEXER_H
#define LEXER_H

//------------------------------------------------------------------------------------
// Includes and Definitions
//------------------------------------------------------------------------------------

// Nothing...

//----------------------------------------------------------------------------------
// Enumerators Definition
//----------------------------------------------------------------------------------

// Token identifiers
// NOTE: the base identifiers are organized by base value
#if !defined(TokenType)
	typedef enum {
		TOKEN_BINARY = 2,
		TOKEN_OCTAL = 8,
		TOKEN_DECIMAL = 10,
		TOKEN_HEXA = 16,
		TOKEN_PLUS,
		TOKEN_MINUS,
		TOKEN_MUL,
		TOKEN_DIV,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_NUMBER,
		TOKEN_UNKNOWN,
		TOKEN_END,
	} TokenType;
#endif

//----------------------------------------------------------------------------------
// Structures Definition
//----------------------------------------------------------------------------------

// Token struct
	#if !defined(Token)
	typedef struct {
		TokenType type;
		char *value;
	} Token;
#endif

// Lexer struct
#if !defined(Lexer)
	typedef struct {
		char *text;
		size_t pos;
	} Lexer;
#endif

//------------------------------------------------------------------------------------
// Lexer and Token Functions
//------------------------------------------------------------------------------------

#if defined(__cplusplus)
	extern "C" {            
#endif

// Don't call these directly
Token _next(Lexer *);

// Normal Functions
Lexer lexer(char *);

#if defined(_cplusplus)
}
#endif

#endif
