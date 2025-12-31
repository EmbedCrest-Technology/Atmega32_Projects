/*
 * LCD.c 
 * Created: 8/12/2024 2:01:29 AM
 *  Author: Embedcrest Technology Private Limited
 */

#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "DIO.h"

static void lcd_enable_pulse(void)
{
    DIO_write_pin(PORT_2, EN, 1);
    _delay_ms(2);
    DIO_write_pin(PORT_2, EN, 0);
    _delay_ms(2);
}

void LCD_init(void)
{
    _delay_ms(150);

#if defined eight_bits_mode

    DIO_set_port_dir(PORT_1, 0xFF);
    DIO_set_pin_dir(PORT_2, EN, 1);
    DIO_set_pin_dir(PORT_2, RW, 1);
    DIO_set_pin_dir(PORT_2, RS, 1);

    DIO_write_pin(PORT_2, RW, 0);

    LCD_send_cmd(EIGHT_BITS);
    _delay_ms(2);
    LCD_send_cmd(CLR_SCREEN);
    _delay_ms(5);
    LCD_send_cmd(CURSOR_OFF_DISPLAY_ON);
    LCD_send_cmd(ENTRY_MODE);

#elif defined four_bits_mode

    DIO_set_pin_dir(PORT_1, 4, 1);
    DIO_set_pin_dir(PORT_1, 5, 1);
    DIO_set_pin_dir(PORT_1, 6, 1);
    DIO_set_pin_dir(PORT_1, 7, 1);

    DIO_set_pin_dir(PORT_2, EN, 1);
    DIO_set_pin_dir(PORT_2, RW, 1);
    DIO_set_pin_dir(PORT_2, RS, 1);

    DIO_write_pin(PORT_2, RW, 0);

    LCD_send_cmd(RETURN_HOME);
    _delay_ms(3);
    LCD_send_cmd(FOUR_BITS);
    LCD_send_cmd(CLR_SCREEN);
    _delay_ms(5);
    LCD_send_cmd(CURSOR_OFF_DISPLAY_ON);
    LCD_send_cmd(ENTRY_MODE);

#endif
}

void LCD_send_cmd(char cmd)
{
    DIO_write_pin(PORT_2, RS, 0);  // Command mode

#if defined eight_bits_mode

    DIO_write_port(PORT_1, cmd);
    lcd_enable_pulse();

#elif defined four_bits_mode

    DIO_write_high_nibble(PORT_1, cmd >> 4);
    lcd_enable_pulse();
    DIO_write_high_nibble(PORT_1, cmd);
    lcd_enable_pulse();

#endif

    _delay_ms(1);
}

void LCD_send_data(char data)
{
    DIO_write_pin(PORT_2, RS, 1);  // Data mode

#if defined eight_bits_mode

    DIO_write_port(PORT_1, data);
    lcd_enable_pulse();

#elif defined four_bits_mode

    DIO_write_high_nibble(PORT_1, data >> 4);
    lcd_enable_pulse();
    DIO_write_high_nibble(PORT_1, data);
    lcd_enable_pulse();

#endif
}

void LCD_send_string(char* str)
{
    while (*str)
    {
        LCD_send_data(*str++);
    }
}

void LCD_clr_screen(void)
{
    LCD_send_cmd(CLR_SCREEN);
    _delay_ms(2);
}

void LCD_move_cursor(char row, char col)
{
    char pos;

    if (row == 1)
        pos = 0x80 + (col - 1);
    else if (row == 2)
        pos = 0xC0 + (col - 1);
    else
        pos = 0x80;  // default

    LCD_send_cmd(pos);
}
