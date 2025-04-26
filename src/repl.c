#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "util.h"
#include "../lib/colors/colors.h"

//------------------------------------------------------------------------------------
// Read Evaluate Print and Loop Implementation (REPL)
//------------------------------------------------------------------------------------


int main() {
    size_t capacity = 64;
    char *buffer = (char *)calloc(capacity, sizeof(char)); 
    unsigned short int mode = TOKEN_DECIMAL;

    for (;;) {
        printf("[NumSystem (%sinput%s)]: ", BLUE, RESET);
        fgets(buffer, capacity, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "quit") == 0) break;

        if (strcmp(buffer, "binary") == 0) {
            mode = TOKEN_BINARY;
            throw("Changed output base to binary.", true);
            continue;
        } else if (strcmp(buffer, "octal") == 0) {
            mode = TOKEN_OCTAL;
            throw("Changed output base to octal.", true);
            continue;
        } else if (strcmp(buffer, "hexa") == 0) {
            mode = TOKEN_HEXA;
            throw("Changed output base to hexadecimal.", true);
            continue;
        } else if (strcmp(buffer, "decimal") == 0) {
            mode = TOKEN_DECIMAL;
            throw("Changed output base to decimal.", true);
            continue;
        }

        Lexer lex = lexer(buffer);
	    Parser parser = {&lex, next(&lex)};
        double result = parse_expression(&parser);

        throw(string_in_given_base(double_to_string(result), TOKEN_DECIMAL, mode), true);
    }
    
    return 0;
}