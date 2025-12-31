/*
 * LCD.c
 *
 * Created: 21/10/2024  9.07 AM
 *  Author: Embedcrest TEchnology Private Limited
 */ 

#define F_CPU 1000000UL  // Fixed: Matches main.c F_CPU
#include <util/delay.h>
#include "LCD.h"
#include "DIO.h"

void LCD_init(void)
{
    _delay_ms(200);
    
#if defined(EIGHT_BITS_MODE)
    DIO_set_port_dir(PORT_1, 0xFF);
    DIO_set_pin_dir(PORT_2, EN, 1);
    DIO_set_pin_dir(PORT_2, RW, 1);
    DIO_set_pin_dir(PORT_2, RS, 1);
    DIO_write_pin(PORT_2, RW, 0);
    
    LCD_send_cmd(EIGHT_BITS);
    _delay_ms(1);
    LCD_send_cmd(CLR_SCREEN);
    _delay_ms(10);
    LCD_send_cmd(CURSOR_OFF_DISPLAY_ON);
    _delay_ms(1);
    LCD_send_cmd(ENTRY_MODE);
    _delay_ms(1);
    
#elif defined(FOUR_BITS_MODE)
    // Data pins D4-D7 as output
    DIO_set_pin_dir(PORT_1, 4, 1);
    DIO_set_pin_dir(PORT_1, 5, 1);
    DIO_set_pin_dir(PORT_1, 6, 1);
    DIO_set_pin_dir(PORT_1, 7, 1);
    DIO_set_pin_dir(PORT_2, EN, 1);
    DIO_set_pin_dir(PORT_2, RW, 1);
    DIO_set_pin_dir(PORT_2, RS, 1);
    DIO_write_pin(PORT_2, RW, 0);
    
    LCD_send_cmd(RETURN_HOME);
    _delay_ms(10);
    LCD_send_cmd(FOUR_BITS);
    _delay_ms(1);
    LCD_send_cmd(CLR_SCREEN);
    _delay_ms(10);
    LCD_send_cmd(CURSOR_OFF_DISPLAY_ON);
    _delay_ms(1);
    LCD_send_cmd(ENTRY_MODE);
    _delay_ms(1);
#endif
}

static void enable(void)
{
    DIO_write_pin(PORT_2, EN, 1);
    _delay_ms(2);
    DIO_write_pin(PORT_2, EN, 0);
    _delay_ms(2);
}

void LCD_send_cmd(uint8_t cmd)  // Fixed: Parameter type matches LCD.h
{
    DIO_write_pin(PORT_2, RS, 0);
    
#if defined(EIGHT_BITS_MODE)
    DIO_write_port(PORT_1, cmd);
    enable();
#elif defined(FOUR_BITS_MODE)
    DIO_write_high_nibble(PORT_1, cmd >> 4);
    enable();
    DIO_write_high_nibble(PORT_1, cmd);
    enable();
#endif
    _delay_ms(1);
}

void LCD_send_data(uint8_t data)  // Fixed: Parameter type matches LCD.h
{
    DIO_write_pin(PORT_2, RS, 1);
    
#if defined(EIGHT_BITS_MODE)
    DIO_write_port(PORT_1, data);
    enable();
#elif defined(FOUR_BITS_MODE)
    DIO_write_high_nibble(PORT_1, data >> 4);
    enable();
    DIO_write_high_nibble(PORT_1, data);
    enable();
#endif
}

void LCD_send_string(uint8_t* string)  // Fixed: Parameter type matches LCD.h
{
    while (*string != '\0') {
        LCD_send_data(*string);
        string++;
    }
}

void LCD_clr_screen(void)
{
    LCD_send_cmd(CLR_SCREEN);
    _delay_ms(10);
}

void LCD_move_cursor(uint8_t row, uint8_t col)  // Fixed: Parameter types match LCD.h
{
    uint8_t data = 0x80;  // Default to line 1 position 1
    
    if (row > 2 || row < 1 || col > 16 || col < 1) {
        // Invalid position - stay at 0x80
    } else if (row == 1) {
        data = (0x80 + col - 1);
    } else if (row == 2) {
        data = (0xC0 + col - 1);
    }
    LCD_send_cmd(data);
    _delay_ms(1);
}

