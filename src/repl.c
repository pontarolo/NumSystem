#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "util.h"
#include "../lib/colors/colors.h"

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
            printf("%soutput%s ~ Changed output base to binary.\n", GREEN, RESET);
            continue;
        } else if (strcmp(buffer, "octal") == 0) {
            mode = TOKEN_OCTAL;
            printf("%soutput%s ~ Changed output base to octal.\n", GREEN, RESET);
            continue;
        } else if (strcmp(buffer, "hexa") == 0) {
            mode = TOKEN_HEXA;
            printf("%soutput%s ~ Changed output base to hexadecimal.\n", GREEN, RESET);
            continue;
        } else if (strcmp(buffer, "decimal") == 0) {
            mode = TOKEN_DECIMAL;
            printf("%soutput%s ~ Changed output base to decimal.\n", GREEN, RESET);
            continue;
        }

        Lexer lex = lexer(buffer);
	    Parser parser = {&lex, next(&lex)};
        double result = parse_expression(&parser);

        printf("%soutput%s ~ %s\n", GREEN, RESET, string_in_given_base(double_to_string(result), TOKEN_DECIMAL, mode));
    }
    return 0;
}