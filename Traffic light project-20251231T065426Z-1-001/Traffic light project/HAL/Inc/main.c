/*
 * Traffic_Controller.c
 *
 * Created: 8/12/2024 9:41:33 PM
 * Author : Embedcrest Technology Private Limited
 */

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "macro_function.h"
#include "LCD.h"
#include "LED.h"
#include "SEVEN_SEGMENT.h"
#include "TIMER.h"

volatile uint8_t tick_counter = 0;

// New function name
void show_time_on_display(uint8_t t)
{
    seven_seg_write_low_nibble(t / 10);
    seven_seg_write_high_nibble(t % 10);
}

int main(void)
{
    LCD_init();
    seven_seg_init_low_nibble();
    seven_seg_init_high_nibble();
    TIMER0_CTC_init_with_interrupt();

    LED_init('C', 0);   // Green
    LED_init('C', 1);   // Yellow
    LED_init('C', 2);   // Red

    uint8_t g_time, y_time, r_time;

    while (1)
    {
        // Updated variable names
        g_time = 30;
        y_time = 5;
        r_time = 20;

        // GREEN light
        LED_turn_on('C', 0);
        LCD_clr_screen();
        LCD_send_string("     MOVE");

        while (g_time)
        {
            if (tick_counter >= 100)
            {
                tick_counter = 0;
                g_time--;
                show_time_on_display(g_time);
            }
        }
        LED_turn_off('C', 0);
        _delay_ms(10);

        // YELLOW light
        LED_turn_on('C', 1);
        LCD_clr_screen();
        LCD_send_string("   BE READY");

        while (y_time)
        {
            if (tick_counter >= 100)
            {
                tick_counter = 0;
                y_time--;
                show_time_on_display(y_time);
            }
        }
        LED_turn_off('C', 1);
        _delay_ms(10);

        // RED light
        LED_turn_on('C', 2);
        LCD_clr_screen();
        LCD_send_string("     STOP!");

        while (r_time)
        {
            if (tick_counter >= 100)
            {
                tick_counter = 0;
                r_time--;
                show_time_on_display(r_time);
            }
        }

        LED_turn_off('C', 2);
    }
}

ISR(TIMER0_COMP_vect)
{
    tick_counter++;
}
