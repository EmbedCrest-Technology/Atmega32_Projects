/*
 * KEYBAD.c
 *
 *  Created: 1/12/2024 12:53:16 AM
 *  Author: Embedcrest Technology Private Limited
 */

#include "KEYBAD.h"
#include "DIO.h"
#include <string.h>
#include <stdio.h>

#define MAX_DIGITS   10     // New macro for digit limits
#define ROWS         4
#define COLS         6

// ==================== KEYPAD MAP ====================
static const char keypad_map[ROWS][COLS] = {
    {'A','7','8','9','*','/'},
    {'^','4','5','6','-','M'},
    {'%','1','2','3','+','B'},
    {'S','0','.','=','+','C'}
};

// ==================== INITIALIZATION ====================
void KEYBAD_init(void)
{
    // Set rows (output)
    for (uint8_t i = 0; i < 4; i++)
        DIO_set_pin_dir(PORT_11, i, 1);

    // Set columns (input + pull-ups)
    for (uint8_t i = 0; i < 6; i++) {
        DIO_set_pin_dir(PORT_22, i, 0);
        DIO_connect_pull_up(PORT_22, i, 1);
    }
}

// ==================== RESET FUNCTION (Cleaner) ====================
void reset_all(char *buffer)
{
    memset(buffer, 0, MAX_DIGITS);
}

// ==================== INPUT VALIDATOR ====================
uint8_t validate_input(char key)
{
    if ((key >= '0' && key <= '9') || key == '.') return 1;
    if (key == '+' || key == '-' || key == '*' || key == '/' || key == '%') return 1;
    if (key == '=' || key == 'C' || key == 'B' || key == 'S') return 1;
    return 0;   // Any unsupported key
}

// ==================== KEYPAD SCAN ====================
char KEYBAD_check_press(void)
{
    char pressed = NOT_pressed;

    for (uint8_t row = 0; row < ROWS; row++)
    {
        // Set all rows HIGH
        for (uint8_t i = 0; i < ROWS; i++)
            DIO_write_pin(PORT_11, i, 1);

        // Drive current row LOW
        DIO_write_pin(PORT_11, row, 0);

        // Check columns
        for (uint8_t col = 0; col < COLS; col++)
        {
            if (DIO_read_pin(PORT_22, col) == 0)
            {
                pressed = keypad_map[row][col];
                return pressed;  // FOUND → return immediately
            }
        }
    }
    return pressed;
}

// ==================== SAFE DIGIT APPEND ====================
uint8_t append_digit(char *buffer, char key)
{
    uint8_t len = strlen(buffer);

    if (len >= MAX_DIGITS)
        return 0;   // ERROR: digit limit exceeded

    buffer[len] = key;
    buffer[len + 1] = '\0';
    return 1;
}

// ==================== PRINT NUMBER USING sprintf() ====================
void print_number(char *dest, long num)
{
    sprintf(dest, "%ld", num);
}
