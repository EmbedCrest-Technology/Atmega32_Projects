/*
 * LCD.c
 * Created: 1/12/2024 2:01:29 AM
 *  Author: Embedcrest Technology Private Limited
 */

#define F_CPU 8000000UL
#include <util/delay.h>
#include <string.h>
#include <stdio.h>

#include "LCD.h"
#include "DIO.h"

// =============================
//     INTERNAL FUNCTIONS
// =============================
static void lcd_enable(void)
{
    DIO_write_pin(PORT_2, EN, 1);
    _delay_ms(1);
    DIO_write_pin(PORT_2, EN, 0);
    _delay_ms(1);
}

// =============================
//       LCD INITIALIZATION
// =============================
void LCD_init(void)
{
    _delay_ms(100);

#if defined eight_bits_mode
    DIO_set_port_dir(PORT_1, 0xFF);
    DIO_set_pin_dir(PORT_2, EN, 1);
    DIO_set_pin_dir(PORT_2, RW, 1);
    DIO_set_pin_dir(PORT_2, RS, 1);
    DIO_write_pin(PORT_2, RW, 0);

    LCD_send_cmd(EIGHT_BITS);
    _delay_ms(1);

#elif defined four_bits_mode
    // High nibble pins
    DIO_set_pin_dir(PORT_1, 4, 1);
    DIO_set_pin_dir(PORT_1, 5, 1);
    DIO_set_pin_dir(PORT_1, 6, 1);
    DIO_set_pin_dir(PORT_1, 7, 1);

    DIO_set_pin_dir(PORT_2, EN, 1);
    DIO_set_pin_dir(PORT_2, RW, 1);
    DIO_set_pin_dir(PORT_2, RS, 1);
    DIO_write_pin(PORT_2, RW, 0);

    LCD_send_cmd(RETURN_HOME);
    _delay_ms(2);

    LCD_send_cmd(FOUR_BITS);
    _delay_ms(1);
#endif

    LCD_clr_screen();
    LCD_send_cmd(CURSOR_ON_DISPLAY_ON);
    LCD_send_cmd(ENTRY_MODE);
}

// =============================
//       SEND COMMAND
// =============================
void LCD_send_cmd(char cmd)
{
    DIO_write_pin(PORT_2, RS, 0);

#if defined eight_bits_mode
    DIO_write_port(PORT_1, cmd);
    lcd_enable();

#elif defined four_bits_mode
    DIO_write_high_nibble(PORT_1, cmd >> 4);
    lcd_enable();
    DIO_write_high_nibble(PORT_1, cmd);
    lcd_enable();
#endif
}

// =============================
//       SEND DATA
// =============================
void LCD_send_data(char data)
{
    DIO_write_pin(PORT_2, RS, 1);

#if defined eight_bits_mode
    DIO_write_port(PORT_1, data);
    lcd_enable();

#elif defined four_bits_mode
    DIO_write_high_nibble(PORT_1, data >> 4);
    lcd_enable();
    DIO_write_high_nibble(PORT_1, data);
    lcd_enable();
#endif
}

// =============================
//       SEND STRING
// =============================
void LCD_send_string(const char *string)
{
    while (*string)
        LCD_send_data(*string++);
}

// =============================
//     CLEAR SCREEN
// =============================
void LCD_clr_screen(void)
{
    LCD_send_cmd(CLR_SCREEN);
    _delay_ms(2);
}

// =============================
//    CURSOR POSITIONING
// =============================
void LCD_move_cursor(char row, char column)
{
    // Clean, short conditions
    if (row == 1 && column >= 1 && column <= 16)
        LCD_send_cmd(0x80 + (column - 1));
    else if (row == 2 && column >= 1 && column <= 16)
        LCD_send_cmd(0xC0 + (column - 1));
    else
        LCD_send_cmd(0x80); // default position

    _delay_ms(1);
}

// =============================
//   PRINT NUMBER USING sprintf()
// =============================
void LCD_print_number(long num)
{
    char buffer[12];   // Enough for -2,147,483,648
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "%ld", num);
    LCD_send_string(buffer);
}
