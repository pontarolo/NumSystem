//------------------------------------------------------------------------------------
// Includes and Definitions
//------------------------------------------------------------------------------------

#include "gui.h"
#include "../lexer.h"
#include "../parser.h"
#include "../util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------------------
// GUI Functions Implementation (Static)
//------------------------------------------------------------------------------------

static void draw_button(Rectangle button, const char *text, Color color, Color text_color) {
    DrawRectangleRec(button, color);
    DrawText(text, button.x + (button.width - MeasureText(text, 20)) / 2, button.y + (button.height - 20) / 2, 20, text_color);
}

static void animate_button(Rectangle button, char *text, Color hover_color, Color pressed_color) {
    if  (isButtonHovered(button)) {
        draw_button(button, text, hover_color, WHITE);
        if (isButtonPressed(button)) draw_button(button, text, pressed_color, WHITE);
    }
}

static bool buttonWasPressed(Rectangle button) {
    return (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}

static bool isButtonHovered(Rectangle button) {
    return (CheckCollisionPointRec(GetMousePosition(), button));
}

static bool isButtonPressed(Rectangle button) {
    return (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonDown(MOUSE_LEFT_BUTTON));
}

static bool shouldClearOutput(bool lastWasEqual) {
    return ((CheckCollisionPointRec(GetMousePosition(), add_button) ||
     CheckCollisionPointRec(GetMousePosition(), sub_button) ||
     CheckCollisionPointRec(GetMousePosition(), mul_button) ||
     CheckCollisionPointRec(GetMousePosition(), div_button) ||
     CheckCollisionPointRec(GetMousePosition(), binary_button) ||
     CheckCollisionPointRec(GetMousePosition(), octal_button) ||
     CheckCollisionPointRec(GetMousePosition(), decimal_button) ||
     CheckCollisionPointRec(GetMousePosition(), hexa_button) ||
     CheckCollisionPointRec(GetMousePosition(), rparen_button) ||
     CheckCollisionPointRec(GetMousePosition(), lparen_button) ||
     CheckCollisionPointRec(GetMousePosition(), dot_button) ||
     CheckCollisionPointRec(GetMousePosition(), num_buttons[0]) ||
     CheckCollisionPointRec(GetMousePosition(), num_buttons[1]) ||
     CheckCollisionPointRec(GetMousePosition(), num_buttons[2]) ||
     CheckCollisionPointRec(GetMousePosition(), num_buttons[3]) ||
     CheckCollisionPointRec(GetMousePosition(), num_buttons[4]) ||
     CheckCollisionPointRec(GetMousePosition(), num_buttons[5]) ||
     CheckCollisionPointRec(GetMousePosition(), num_buttons[6]) ||
     CheckCollisionPointRec(GetMousePosition(), num_buttons[7]) ||
     CheckCollisionPointRec(GetMousePosition(), num_buttons[8]) ||
     CheckCollisionPointRec(GetMousePosition(), num_buttons[9]))
    && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)
    && lastWasEqual);
}

//------------------------------------------------------------------------------------
// GUI Implementation
//------------------------------------------------------------------------------------

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "NumSystem");
    SetTargetFPS(60);

    char *input = (char *)calloc(64, sizeof(char));
    char *output = (char *)calloc(64, sizeof(char));
    unsigned short int mode = TOKEN_DECIMAL;
    bool lastWasEqual = false;

    while (!WindowShouldClose()) {
        if (shouldClearOutput(lastWasEqual)) {
            strcpy(output, "");
            lastWasEqual = false;
        }

        if (buttonWasPressed(add_button)) strcat(input, "+");
        else if (buttonWasPressed(sub_button)) strcat(input, "-");
        else if (buttonWasPressed(mul_button)) strcat(input, "*");
        else if (buttonWasPressed(div_button)) strcat(input, "/");
        else if (buttonWasPressed(binary_button)) strcat(input, "b");
        else if (buttonWasPressed(octal_button)) strcat(input, "o");
        else if (buttonWasPressed(decimal_button)) strcat(input, "d");
        else if (buttonWasPressed(hexa_button)) strcat(input, "h");
        else if (buttonWasPressed(del_button)) input[strlen(input) - 1] = '\0';
        else if (buttonWasPressed(lparen_button)) strcat(input, "(");
        else if (buttonWasPressed(rparen_button)) strcat(input, ")");
        else if (buttonWasPressed(dot_button)) strcat(input, ".");
        else if (buttonWasPressed(binary_output_button)) {
            strcpy(output, "Changed output base to binary");
            throw("Changed output base to binary.", true);

            mode = TOKEN_BINARY;
            lastWasEqual = true;
        } else if (buttonWasPressed(octal_output_button)) {
            strcpy(output, "Changed output base to octal.");
            throw("Changed output base to octal.", true);

            mode = TOKEN_OCTAL;
            lastWasEqual = true;
        } else if (buttonWasPressed(decimal_output_button)) {
            strcpy(output, "Changed output base to decimal.");
            throw("Changed output base to decimal.", true);

            mode = TOKEN_DECIMAL;
            lastWasEqual = true;
        } else if (buttonWasPressed(hexa_output_button)) {
            strcpy(output, "Changed output base to hexadecimal.");
            throw("Changed output base to hexadecimal.", true);

            mode = TOKEN_HEXA;
            lastWasEqual = true;
        } else if (buttonWasPressed(equal_button)) {
            lastWasEqual = true;

            Lexer lex = lexer(input);
            Parser parser = {&lex, next(&lex)};
            double result = parse_expression(&parser);

            strcpy(input, "");

            if (result == INFINITY) strcpy(output, "Division by zero");
            else if (result == DBL_MAX) strcpy(output, "Invalid number.");
            else {
                throw(string_in_given_base(double_to_string(result), TOKEN_DECIMAL, mode), true); 
                strcpy(output, string_in_given_base(double_to_string(result), TOKEN_DECIMAL, mode));
            }
        } else if (buttonWasPressed(clear_button)) {
            strcpy(output, "");
            strcpy(input, "");
        }

        for (unsigned short int i = 0; i < 10; i++)
            if (buttonWasPressed(num_buttons[i])) strcat(input, char_to_string(i + '0'));

        for (unsigned short int i = 10; i < 16; i++)
            if (buttonWasPressed(hexa_buttons[i - 10])) strcat(input, char_to_string(valid_hexa_chars[i]));

        BeginDrawing();
            ClearBackground(LIGHTGRAY);

            BeginScissorMode(OFFSET_X, OFFSET_Y, (6 * BUTTON_WIDTH + 5 * PADDING), DISPLAY_HEIGHT);

                DrawRectangle(OFFSET_X, OFFSET_Y, (6 * BUTTON_WIDTH + 5 * PADDING), DISPLAY_HEIGHT, WHITE);
                DrawText(input, OFFSET_X + PADDING, OFFSET_Y + PADDING, 20, BLACK);
                DrawText(output, OFFSET_X + PADDING, OFFSET_Y + PADDING, 20, BLACK);

            EndScissorMode();

            draw_button(add_button, "+", DARKBLUE, WHITE);
            animate_button(add_button, "+", BLUE, SKYBLUE);

            draw_button(sub_button, "-", DARKBLUE, WHITE);
            animate_button(sub_button, "-", BLUE, SKYBLUE);

            draw_button(mul_button, "*", DARKBLUE, WHITE);
            animate_button(mul_button, "*", BLUE, SKYBLUE);

            draw_button(div_button, "/", DARKBLUE, WHITE);
            animate_button(div_button, "/", BLUE, SKYBLUE);

            draw_button(equal_button, "=", GREEN, WHITE);
            animate_button(equal_button, "=", DARKGREEN, LIME);

            draw_button(clear_button, "C", RED, WHITE);
            animate_button(clear_button, "C", MAROON, (Color){139, 0, 0, 255});

            draw_button(binary_button, "B", DARKBLUE, WHITE);
            animate_button(binary_button, "B", BLUE, SKYBLUE);

            draw_button(octal_button, "O", DARKBLUE, WHITE);
            animate_button(octal_button, "O", BLUE, SKYBLUE);

            draw_button(decimal_button, "D", DARKBLUE, WHITE);
            animate_button(decimal_button, "D", BLUE, SKYBLUE);

            draw_button(hexa_button, "H", DARKBLUE, WHITE);
            animate_button(hexa_button, "H", BLUE, SKYBLUE);

            draw_button(rparen_button, ")", DARKBLUE, WHITE);
            animate_button(rparen_button, ")", BLUE, SKYBLUE);

            draw_button(lparen_button, "(", DARKBLUE, WHITE);
            animate_button(lparen_button, "(", BLUE, SKYBLUE);

            draw_button(dot_button, ".", DARKBLUE, WHITE);
            animate_button(dot_button, ".", BLUE, SKYBLUE);

            draw_button(binary_output_button, "B", DARKGRAY, WHITE);
            animate_button(binary_output_button, "B", GRAY, LIGHTGRAY);

            draw_button(octal_output_button, "O", DARKGRAY, WHITE);
            animate_button(octal_output_button, "O", GRAY, LIGHTGRAY);

            draw_button(decimal_output_button, "D", DARKGRAY, WHITE);
            animate_button(decimal_output_button, "D", GRAY, LIGHTGRAY);

            draw_button(hexa_output_button, "H", DARKGRAY, WHITE);
            animate_button(hexa_output_button, "H", GRAY, LIGHTGRAY);

            draw_button(del_button, "<", RED, WHITE);
            animate_button(del_button, "<", MAROON, (Color){139, 0, 0, 255});

            for (unsigned short int i = 0; i < 10; i++) {
                draw_button(num_buttons[i], char_to_string(i + '0'), DARKBLUE, WHITE);
                animate_button(num_buttons[i], char_to_string(i + '0'), BLUE, SKYBLUE);
            }

            for (unsigned short int i = 10; i < 16; i++) {
                draw_button(hexa_buttons[i - 10], char_to_string(valid_hexa_chars[i]), DARKBLUE, WHITE);
                animate_button(hexa_buttons[i - 10], char_to_string(valid_hexa_chars[i]), BLUE, SKYBLUE);
            }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
