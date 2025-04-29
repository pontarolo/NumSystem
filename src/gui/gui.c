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

// For drawing the calculator buttons
static void draw_button(Rectangle button, const char *text, Color color, Color text_color) {
    DrawRectangleRec(button, color);
    DrawText(text, button.x + (button.width - MeasureText(text, 20)) / 2, button.y + (button.height - 20) / 2, 20, text_color);
}

// For drawing text that fit in the screen size
static void draw_fitting_text(const char *text, int pos_x, int pos_y, int max_width, Color color) {
    int font_size = 20;
    int text_width = MeasureText(text, font_size);

    while (text_width > max_width && font_size > 5) {
        font_size--;
        text_width = MeasureText(text, font_size);
    }

    DrawText(text, pos_x, pos_y, font_size, color);
}

// Giving them some spice
static void animate_button(Rectangle button, const char *text, Color hover_color, Color pressed_color) {
    if  (is_button_hovered(button)) {
        draw_button(button, text, hover_color, WHITE);
        if (is_button_pressed(button)) draw_button(button, text, pressed_color, WHITE);
    }
}

// Checks if a certain button was pressed
static bool button_was_pressed(Rectangle button) {
    return (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}

// Checks if a certain button is being hovered
static bool is_button_hovered(Rectangle button) {
    return (CheckCollisionPointRec(GetMousePosition(), button));
}

// Checks if a certain buttos is being pressed
static bool is_button_pressed(Rectangle button) {
    return (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonDown(MOUSE_LEFT_BUTTON));
}

// Checks if it is time to clear the output string
static bool should_clear_output(bool last_was_equal) {
    return ((CheckCollisionPointRec(GetMousePosition(), g_add_button) ||
     CheckCollisionPointRec(GetMousePosition(), g_sub_button) ||
     CheckCollisionPointRec(GetMousePosition(), g_mul_button) ||
     CheckCollisionPointRec(GetMousePosition(), g_div_button) ||
     CheckCollisionPointRec(GetMousePosition(), g_binary_button) ||
     CheckCollisionPointRec(GetMousePosition(), g_octal_button) ||
     CheckCollisionPointRec(GetMousePosition(), g_decimal_button) ||
     CheckCollisionPointRec(GetMousePosition(), g_hexa_button) ||
     CheckCollisionPointRec(GetMousePosition(), g_rparen_button) ||
     CheckCollisionPointRec(GetMousePosition(), g_lparen_button) ||
     CheckCollisionPointRec(GetMousePosition(), g_dot_button) ||
     CheckCollisionPointRec(GetMousePosition(), g_num_buttons[0]) ||
     CheckCollisionPointRec(GetMousePosition(), g_num_buttons[1]) ||
     CheckCollisionPointRec(GetMousePosition(), g_num_buttons[2]) ||
     CheckCollisionPointRec(GetMousePosition(), g_num_buttons[3]) ||
     CheckCollisionPointRec(GetMousePosition(), g_num_buttons[4]) ||
     CheckCollisionPointRec(GetMousePosition(), g_num_buttons[5]) ||
     CheckCollisionPointRec(GetMousePosition(), g_num_buttons[6]) ||
     CheckCollisionPointRec(GetMousePosition(), g_num_buttons[7]) ||
     CheckCollisionPointRec(GetMousePosition(), g_num_buttons[8]) ||
     CheckCollisionPointRec(GetMousePosition(), g_num_buttons[9]))
    && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)
    && last_was_equal);
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
    bool last_was_equal = false;

    while (!WindowShouldClose()) {
        if (should_clear_output(last_was_equal)) {
            strcpy(output, "");
            last_was_equal = false;
        }

        if (button_was_pressed(g_add_button)) strcat(input, "+");
        else if (button_was_pressed(g_sub_button)) strcat(input, "-");
        else if (button_was_pressed(g_mul_button)) strcat(input, "*");
        else if (button_was_pressed(g_div_button)) strcat(input, "/");
        else if (button_was_pressed(g_binary_button)) strcat(input, "b");
        else if (button_was_pressed(g_octal_button)) strcat(input, "o");
        else if (button_was_pressed(g_decimal_button)) strcat(input, "d");
        else if (button_was_pressed(g_hexa_button)) strcat(input, "h");
        else if (button_was_pressed(g_del_button)) input[strlen(input) - 1] = '\0';
        else if (button_was_pressed(g_lparen_button)) strcat(input, "(");
        else if (button_was_pressed(g_rparen_button)) strcat(input, ")");
        else if (button_was_pressed(g_dot_button)) strcat(input, ".");
        else if (button_was_pressed(g_binary_output_button)) {
            strcpy(input, "");
            strcpy(output, "Changed output base to binary");
            throw("Changed output base to binary.", true);

            mode = TOKEN_BINARY;
            last_was_equal = true;
        } else if (button_was_pressed(g_octal_output_button)) {
            strcpy(input, "");
            strcpy(output, "Changed output base to octal.");
            throw("Changed output base to octal.", true);

            mode = TOKEN_OCTAL;
            last_was_equal = true;
        } else if (button_was_pressed(g_decimal_output_button)) {
            strcpy(input, "");
            strcpy(output, "Changed output base to decimal.");
            throw("Changed output base to decimal.", true);

            mode = TOKEN_DECIMAL;
            last_was_equal = true;
        } else if (button_was_pressed(g_hexa_output_button)) {
            strcpy(input, "");
            strcpy(output, "Changed output base to hexadecimal.");
            throw("Changed output base to hexadecimal.", true);

            mode = TOKEN_HEXA;
            last_was_equal = true;
        } else if (button_was_pressed(g_equal_button)) {
            last_was_equal = true;

            Lexer lex = lexer(input);
            Parser parser = {&lex, _next(&lex)};
            double result = parse_expression(&parser);

            strcpy(input, "");

            if (result == INFINITY) strcpy(output, "Division by zero");
            else if (isnan(result)) strcpy(output, "Invalid number.");
            else {
                throw(string_in_given_base(_double_to_string(result), TOKEN_DECIMAL, mode), true); 
                strcpy(output, string_in_given_base(_double_to_string(result), TOKEN_DECIMAL, mode));
            }
        } else if (button_was_pressed(g_clear_button)) {
            strcpy(output, "");
            strcpy(input, "");
        }

        for (unsigned short int i = 0; i < 10; i++)
            if (button_was_pressed(g_num_buttons[i])) strcat(input, _char_to_string(i + '0'));

        for (unsigned short int i = 10; i < 16; i++)
            if (button_was_pressed(g_hexa_buttons[i - 10])) strcat(input, _char_to_string(g_valid_hexa_chars[i]));

        BeginDrawing();
            ClearBackground(LIGHTGRAY);

            BeginScissorMode(OFFSET_X, OFFSET_Y, (6 * BUTTON_WIDTH + 5 * PADDING), DISPLAY_HEIGHT);

                DrawRectangle(OFFSET_X, OFFSET_Y, (6 * BUTTON_WIDTH + 5 * PADDING), DISPLAY_HEIGHT, WHITE);
                draw_fitting_text(input, OFFSET_X + PADDING, OFFSET_Y + PADDING, (6 * BUTTON_WIDTH + 5 * PADDING) - 2 * PADDING, BLACK);
                draw_fitting_text(output, OFFSET_X + PADDING, OFFSET_Y + PADDING, (6 * BUTTON_WIDTH + 5 * PADDING) - 2 * PADDING, BLACK);

            EndScissorMode();

            draw_button(g_add_button, "+", DARKBLUE, WHITE);
            animate_button(g_add_button, "+", BLUE, SKYBLUE);

            draw_button(g_sub_button, "-", DARKBLUE, WHITE);
            animate_button(g_sub_button, "-", BLUE, SKYBLUE);

            draw_button(g_mul_button, "*", DARKBLUE, WHITE);
            animate_button(g_mul_button, "*", BLUE, SKYBLUE);

            draw_button(g_div_button, "/", DARKBLUE, WHITE);
            animate_button(g_div_button, "/", BLUE, SKYBLUE);

            draw_button(g_equal_button, "=", GREEN, WHITE);
            animate_button(g_equal_button, "=", DARKGREEN, LIME);

            draw_button(g_clear_button, "C", RED, WHITE);
            animate_button(g_clear_button, "C", MAROON, (Color){139, 0, 0, 255});

            draw_button(g_binary_button, "B", DARKBLUE, WHITE);
            animate_button(g_binary_button, "B", BLUE, SKYBLUE);

            draw_button(g_octal_button, "O", DARKBLUE, WHITE);
            animate_button(g_octal_button, "O", BLUE, SKYBLUE);

            draw_button(g_decimal_button, "D", DARKBLUE, WHITE);
            animate_button(g_decimal_button, "D", BLUE, SKYBLUE);

            draw_button(g_hexa_button, "H", DARKBLUE, WHITE);
            animate_button(g_hexa_button, "H", BLUE, SKYBLUE);

            draw_button(g_rparen_button, ")", DARKBLUE, WHITE);
            animate_button(g_rparen_button, ")", BLUE, SKYBLUE);

            draw_button(g_lparen_button, "(", DARKBLUE, WHITE);
            animate_button(g_lparen_button, "(", BLUE, SKYBLUE);

            draw_button(g_dot_button, ".", DARKBLUE, WHITE);
            animate_button(g_dot_button, ".", BLUE, SKYBLUE);

            draw_button(g_binary_output_button, "B", DARKGRAY, WHITE);
            animate_button(g_binary_output_button, "B", GRAY, LIGHTGRAY);

            draw_button(g_octal_output_button, "O", DARKGRAY, WHITE);
            animate_button(g_octal_output_button, "O", GRAY, LIGHTGRAY);

            draw_button(g_decimal_output_button, "D", DARKGRAY, WHITE);
            animate_button(g_decimal_output_button, "D", GRAY, LIGHTGRAY);

            draw_button(g_hexa_output_button, "H", DARKGRAY, WHITE);
            animate_button(g_hexa_output_button, "H", GRAY, LIGHTGRAY);

            draw_button(g_del_button, "<", RED, WHITE);
            animate_button(g_del_button, "<", MAROON, (Color){139, 0, 0, 255});

            for (unsigned short int i = 0; i < 10; i++) {
                draw_button(g_num_buttons[i], _char_to_string(i + '0'), DARKBLUE, WHITE);
                animate_button(g_num_buttons[i], _char_to_string(i + '0'), BLUE, SKYBLUE);
            }

            for (unsigned short int i = 10; i < 16; i++) {
                draw_button(g_hexa_buttons[i - 10], _char_to_string(g_valid_hexa_chars[i]), DARKBLUE, WHITE);
                animate_button(g_hexa_buttons[i - 10], _char_to_string(g_valid_hexa_chars[i]), BLUE, SKYBLUE);
            }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
