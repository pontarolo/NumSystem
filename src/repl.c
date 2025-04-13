#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

int main() {
    size_t capacity = 64;
    char *buffer = (char *)calloc(capacity, sizeof(char)); 

    for (;;) {
        printf("NumSystem >> ");
        fgets(buffer, capacity, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "quit") == 0) break;

        Lexer lex = lexer(buffer);
	    Parser parser = {&lex, next(&lex)};
	    double result = parse_expression(&parser);
	    printf("%lf\n", result);
    }
    return 0;
}