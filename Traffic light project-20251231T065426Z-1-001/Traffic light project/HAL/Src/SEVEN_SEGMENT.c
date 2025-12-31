/*
 * SEVEN_SEGMENT.c 
 * Created: 8/12/2024 10:01:44 PM
 *  Author: Embedcrest Technology Private Limited
 */

#include "SEVEN_SEGMENT.h"

// Initialize full port
void seven_segment_port_init(void)
{
    DIO_set_port_dir(seven_seg_port, 0xFF);
}

// Write number to full port (0–9)
void seven_segment_display_digit(unsigned char digit)
{
#ifdef CC
    unsigned char map[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x47,0x7F,0x6F};
    DIO_write_port(seven_seg_port, map[digit]);
#else
    unsigned char map[] = {~0x3F,~0x06,~0x5B,~0x4F,~0x66,~0x6D,~0x7D,~0x47,~0x7F,~0x6F};
    DIO_write_port(seven_seg_port, map[digit]);
#endif
}

// Initialize low nibble
void seven_segment_init_low(void)
{
    for (char i = 0; i < 4; i++)
        DIO_set_pin_dir(seven_seg_port, i, 1);
}

// Initialize high nibble
void seven_segment_init_high(void)
{
    for (char i = 4; i < 8; i++)
        DIO_set_pin_dir(seven_seg_port, i, 1);
}

// Write low nibble
void seven_segment_show_low(unsigned char value)
{
    DIO_write_low_nibble(seven_seg_port, value);
}

// Write high nibble
void seven_segment_show_high(unsigned char value)
{
    DIO_write_high_nibble(seven_seg_port, value);
}

// Generic 4-bit init
void seven_segment_init_nibble(unsigned char start_pin)
{
    for (char i = 0; i < 4; i++)
        DIO_set_pin_dir(seven_seg_port, start_pin + i, 1);
}

// Generic 4-bit write
void seven_segment_write_nibble(unsigned char start_pin, unsigned char value)
{
    for (char i = 0; i < 4; i++)
        DIO_write_pin(seven_seg_port, start_pin + i, READ_BIT(value, i));
}
