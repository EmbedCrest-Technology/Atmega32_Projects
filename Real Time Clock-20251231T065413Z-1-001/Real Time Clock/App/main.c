/*
 * Real_time_clock.c
 *
 * Created: 16/12/2024 12:48:38 PM
 * Author : Embedcrest Technology Private Limited
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "macro_function.h"
#include "LCD.h"
#include "KEYBAD.h"
#include "SEVEN_SEGMENT.h"
#include "TIMER.h"

void display_clock(void);

volatile unsigned char sec_counter = 0;
unsigned char min_counter = 0, hour_counter = 0;

unsigned char key_pressed;
unsigned char digit_count;
unsigned char digit_high, digit_low;

int main(void)
{
    LCD_init();
    KEYBAD_init();
    seven_seg_init_port();
    TIMER2_normal_init_with_interrupt();

    SET_BIT(DDRC,PC0);
    SET_BIT(DDRC,PC1);
    SET_BIT(DDRC,PC2);
    SET_BIT(DDRC,PC3);
    SET_BIT(DDRC,PC4);
    SET_BIT(DDRC,PC5);

    LCD_send_string("   press A");
    LCD_move_cursor(2,1);
    LCD_send_string("   to set clock");

    while(1)
    {
        key_pressed = KEYBAD_check_press();

        if(key_pressed == 'A')
        {
            // ===========================
            // Set Hours
            // ===========================
            LCD_clr_screen();
            LCD_send_string(" Hour=--");
            LCD_move_cursor(1,7);

            do 
            {
                key_pressed = KEYBAD_check_press();
                if(key_pressed >= '0' && key_pressed <= '9')
                {
                    if(digit_count == 0)
                    {
                        digit_high = key_pressed;
                        LCD_send_data(key_pressed);
                        digit_count++;
                        _delay_ms(200);
                    }
                    else
                    {
                        digit_low = key_pressed;
                        LCD_send_data(key_pressed);
                        digit_count++;
                    }
                }
                display_clock();
            } while(digit_count < 2);

            _delay_ms(200);

            if(((digit_high - 48) * 10 + (digit_low - 48)) < 24)
            {
                hour_counter = (digit_high - 48) * 10 + (digit_low - 48);
            }

            digit_high = digit_low = '0';
            digit_count = 0;

            // ===========================
            // Set Minutes
            // ===========================
            LCD_clr_screen();
            LCD_send_string("Minute=--");
            LCD_move_cursor(1,8);

            do 
            {
                key_pressed = KEYBAD_check_press();
                if(key_pressed >= '0' && key_pressed <= '9')
                {
                    if(digit_count == 0)
                    {
                        digit_high = key_pressed;
                        LCD_send_data(key_pressed);
                        digit_count++;
                        _delay_ms(200);
                    }
                    else
                    {
                        digit_low = key_pressed;
                        LCD_send_data(key_pressed);
                        digit_count++;
                    }
                }
                display_clock();
            } while(digit_count < 2);

            _delay_ms(200);

            if((digit_high - 48) * 10 < 60)
            {
                min_counter = (digit_high - 48) * 10 + (digit_low - 48);
            }

            digit_high = digit_low = '0';
            digit_count = 0;

            // ===========================
            // Set Seconds
            // ===========================
            LCD_clr_screen();
            LCD_send_string("Second=--");
            LCD_move_cursor(1,8);

            do 
            {
                key_pressed = KEYBAD_check_press();
                if(key_pressed >= '0' && key_pressed <= '9')
                {
                    if(digit_count == 0)
                    {
                        digit_high = key_pressed;
                        LCD_send_data(key_pressed);
                        digit_count++;
                        _delay_ms(200);
                    }
                    else
                    {
                        digit_low = key_pressed;
                        LCD_send_data(key_pressed);
                        digit_count++;
                    }
                }
                display_clock();
            } while(digit_count < 2);

            _delay_ms(200);

            if((digit_high - 48) * 10 < 60)
            {
                sec_counter = (digit_high - 48) * 10 + (digit_low - 48);
            }

            digit_high = digit_low = '0';
            digit_count = 0;

            LCD_clr_screen();
            LCD_send_string("   press A");
            LCD_move_cursor(2,1);
            LCD_send_string("   to set clock");
        }

        display_clock();
    }
}

ISR(TIMER2_OVF_vect)
{
    sec_counter++;
}

void display_clock(void)
{
    // 6-digit multiplexing (HH:MM:SS)
    
    CLR_BIT(PORTC,PC0);
    SET_BIT(PORTC,PC1);
    SET_BIT(PORTC,PC2);
    SET_BIT(PORTC,PC3);
    SET_BIT(PORTC,PC4);
    SET_BIT(PORTC,PC5);
    seven_seg_write_port(hour_counter/10);
    _delay_ms(5);

    SET_BIT(PORTC,PC0);
    CLR_BIT(PORTC,PC1);
    SET_BIT(PORTC,PC2);
    SET_BIT(PORTC,PC3);
    SET_BIT(PORTC,PC4);
    SET_BIT(PORTC,PC5);
    seven_seg_write_port(hour_counter%10);
    _delay_ms(5);

    SET_BIT(PORTC,PC0);
    SET_BIT(PORTC,PC1);
    CLR_BIT(PORTC,PC2);
    SET_BIT(PORTC,PC3);
    SET_BIT(PORTC,PC4);
    SET_BIT(PORTC,PC5);
    seven_seg_write_port(min_counter/10);
    _delay_ms(5);

    SET_BIT(PORTC,PC0);
    SET_BIT(PORTC,PC1);
    SET_BIT(PORTC,PC2);
    CLR_BIT(PORTC,PC3);
    SET_BIT(PORTC,PC4);
    SET_BIT(PORTC,PC5);
    seven_seg_write_port(min_counter%10);
    _delay_ms(5);

    SET_BIT(PORTC,PC0);
    SET_BIT(PORTC,PC1);
    SET_BIT(PORTC,PC2);
    SET_BIT(PORTC,PC3);
    CLR_BIT(PORTC,PC4);
    SET_BIT(PORTC,PC5);
    seven_seg_write_port(sec_counter/10);
    _delay_ms(5);

    SET_BIT(PORTC,PC0);
    SET_BIT(PORTC,PC1);
    SET_BIT(PORTC,PC2);
    SET_BIT(PORTC,PC3);
    SET_BIT(PORTC,PC4);
    CLR_BIT(PORTC,PC5);
    seven_seg_write_port(sec_counter%10);
    _delay_ms(5);

    if(sec_counter == 60)
    {
        sec_counter = 0;
        min_counter++;
    }
    if(min_counter == 60)
    {
        min_counter = 0;
        hour_counter++;
    }
    if(hour_counter == 24)
    {
        hour_counter = 0;
    }
}
