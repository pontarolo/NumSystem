#ifndef GUI_H
#define GUI_H

//------------------------------------------------------------------------------------
// Includes and Definitions
//------------------------------------------------------------------------------------

#include "raylib.h"
#include <stddef.h>

#ifndef SCREEN_WIDTH
    #define SCREEN_WIDTH 430
#endif 

#ifndef SCREEN_HEIGHT
    #define SCREEN_HEIGHT 530
#endif

#ifndef BUTTON_WIDTH
    #define BUTTON_WIDTH 60
#endif

#ifndef BUTTON_HEIGHT
    #define BUTTON_HEIGHT 60
#endif

#ifndef PADDING
    #define PADDING 10
#endif

#ifndef DISPLAY_HEIGHT
    #define DISPLAY_HEIGHT 80
#endif

#ifndef BUTTON_AREA_HEIGHT
    #define BUTTON_AREA_HEIGHT (6 * BUTTON_HEIGHT + 5 * PADDING)
#endif

#ifndef TOTAL_AREA_HEIGHT
    #define TOTAL_AREA_HEIGHT (DISPLAY_HEIGHT + PADDING + BUTTON_AREA_HEIGHT)
#endif

#ifndef OFFSET_X
    #define OFFSET_X ((SCREEN_WIDTH - (6 * BUTTON_WIDTH + 5 * PADDING)) / 2)
#endif

#ifndef OFFSET_Y
    #define OFFSET_Y ((SCREEN_HEIGHT - TOTAL_AREA_HEIGHT) / 2)
#endif

//------------------------------------------------------------------------------------
// Global Variables Definition
//------------------------------------------------------------------------------------

static Rectangle g_add_button = {OFFSET_X + (4 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (0 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT};
static Rectangle g_sub_button = {OFFSET_X + (4 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (1 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT};
static Rectangle g_mul_button = {OFFSET_X + (4 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (2 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT};
static Rectangle g_div_button = {OFFSET_X + (4 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (3 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT};
static Rectangle g_equal_button = {OFFSET_X + (1 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (5 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH * 2 + PADDING, BUTTON_HEIGHT};
static Rectangle g_clear_button = {OFFSET_X + (3 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (5 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH * 2 + PADDING, BUTTON_HEIGHT};
static Rectangle g_binary_button = {OFFSET_X + (5 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (0 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT};
static Rectangle g_octal_button = {OFFSET_X + (5 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (1 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT};
static Rectangle g_decimal_button = {OFFSET_X + (5 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (2 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT};
static Rectangle g_hexa_button = {OFFSET_X + (5 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (3 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT};
static Rectangle g_rparen_button = {OFFSET_X + (3 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (3 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT};
static Rectangle g_lparen_button = {OFFSET_X + (2 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (3 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT};
static Rectangle g_binary_output_button = {OFFSET_X + (2 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (4 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT};
static Rectangle g_octal_output_button = {OFFSET_X + (3 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (4 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT};
static Rectangle g_decimal_output_button = {OFFSET_X + (4 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (4 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT};
static Rectangle g_hexa_output_button = {OFFSET_X + (5 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (4 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT};
static Rectangle g_dot_button = {OFFSET_X + (1 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (4 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT};
static Rectangle g_del_button = {OFFSET_X + (5 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (5 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT};

static Rectangle g_hexa_buttons[6] = {
    {OFFSET_X + (0 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (0 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT},
    {OFFSET_X + (0 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (1 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT},
    {OFFSET_X + (0 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (2 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT},
    {OFFSET_X + (0 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (3 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT},
    {OFFSET_X + (0 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (4 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT},
    {OFFSET_X + (0 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (5 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT},
};

static Rectangle g_num_buttons[10] = {
    {OFFSET_X + (1 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (3 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT},
    {OFFSET_X + (1 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (0 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT},
    {OFFSET_X + (2 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (0 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT},
    {OFFSET_X + (3 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (0 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT},
    {OFFSET_X + (1 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (1 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT},
    {OFFSET_X + (2 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (1 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT},
    {OFFSET_X + (3 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (1 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT},
    {OFFSET_X + (1 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (2 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT},
    {OFFSET_X + (2 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (2 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT},
    {OFFSET_X + (3 * (BUTTON_WIDTH + PADDING)), OFFSET_Y + DISPLAY_HEIGHT + PADDING + (2 * (BUTTON_HEIGHT + PADDING)), BUTTON_WIDTH, BUTTON_HEIGHT},
};

//------------------------------------------------------------------------------------
// GUI Functions
//------------------------------------------------------------------------------------

#if defined(__cplusplus)
    extern "C" {            
#endif

// Static
static void draw_button(Rectangle, const char *, Color, Color);
static void animate_button(Rectangle button, char *text, Color hover_color, Color pressed_color);
static bool button_was_pressed(Rectangle);
static bool is_button_hovered(Rectangle);
static bool is_button_pressed(Rectangle);
static bool should_clear_output(bool);

#if defined(_cplusplus)
}
#endif

#endif
