/*
 * Simple_MathGame.c
 *
 * created: 8/11/2024 12:01:40 PM
 * Author : Embedcrest Technology Private Limited
 */

#include <avr/io.h>
#include <stdlib.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "LCD.h"
#include "KEYBAD.h"
#include "TIMER.h"

volatile int timer_counter = 0;
int timeout_flag = 0;

/* ---------------------- HELPER FUNCTION ---------------------- */

int get_user_number(uint8_t cursor_pos, char *buffer)
{
    uint8_t index = 0;
    char key;
    timer_counter = 0;
    timeout_flag = 0;

    while (1)
    {
        key = KEYBAD_check_press();

        if (key == '=')
            break;

        if (key >= '0' && key <= '9')
        {
            if (index == 0)
            {
                LCD_move_cursor(1, cursor_pos);
                LCD_send_string("  ");
                LCD_move_cursor(1, cursor_pos);
            }

            LCD_send_data(key);
            buffer[index++] = key;
            _delay_ms(250);
        }

        if (timer_counter >= 1000)
        {
            timeout_flag = 1;
            break;
        }
    }

    buffer[index] = '\0';
    return atoi(buffer);
}

/* ---------------------------- MAIN --------------------------- */

int main(void)
{
    LCD_init();
    KEYBAD_init();
    TIMER0_CTC_init_with_interrupt();

    char key;
    char ans_buf1[4], ans_buf2[4], ans_buf3[4];
    int ans1, ans2, ans3;

start_game:

    /* --------- Level 1 --------- */
    LCD_clr_screen();
    LCD_send_string("8+?? =13");

    ans1 = get_user_number(3, ans_buf1);

    if (timeout_flag)
    {
        LCD_clr_screen();
        LCD_send_string("   Time over");
        LCD_move_cursor(2, 4);
        LCD_send_string("Score:0/10");
        while (1);
    }
    else if (ans1 == 5)
    {
        LCD_clr_screen();
        LCD_send_string("   Well Done");
        LCD_move_cursor(2, 4);
        LCD_send_string("Score:2/10");
        _delay_ms(1000);
    }
    else
    {
        LCD_clr_screen();
        LCD_send_string(" Wrong Answer ");
        LCD_move_cursor(2, 4);
        LCD_send_string("Score:0/10");
        while (1);
    }

    LCD_clr_screen();
    LCD_send_string("   Next Level");
    _delay_ms(1000);


    /* --------- Level 2 --------- */
    LCD_clr_screen();
    LCD_send_string("68+?? =100");

    ans2 = get_user_number(4, ans_buf2);

    if (timeout_flag)
    {
        LCD_clr_screen();
        LCD_send_string("   Time over");
        LCD_move_cursor(2, 4);
        LCD_send_string("Score:2/10");
        while (1);
    }
    else if (ans2 == 32)
    {
        LCD_clr_screen();
        LCD_send_string("   Well Done");
        LCD_move_cursor(2, 4);
        LCD_send_string("Score:6/10");
        _delay_ms(1000);
    }
    else
    {
        LCD_clr_screen();
        LCD_send_string(" Wrong Answer ");
        LCD_move_cursor(2, 4);
        LCD_send_string("Score:2/10");
        while (1);
    }

    LCD_clr_screen();
    LCD_send_string("   Next Level");
    _delay_ms(1000);


    /* --------- Level 3 --------- */
    LCD_clr_screen();
    LCD_send_string("150+?? =322");

    ans3 = get_user_number(5, ans_buf3);

    if (timeout_flag)
    {
        LCD_clr_screen();
        LCD_send_string("   Time over");
        LCD_move_cursor(2, 4);
        LCD_send_string("Score:6/10");
        while (1);
    }
    else if (ans3 == 172)
    {
        LCD_clr_screen();
        LCD_send_string("   Well Done");
        LCD_move_cursor(2, 4);
        LCD_send_string("Score:10/10");
        _delay_ms(1000);
        LCD_clr_screen();
        LCD_send_string(" Congratulation");
        while (1);
    }
    else
    {
        LCD_clr_screen();
        LCD_send_string(" Wrong Answer ");
        LCD_move_cursor(2, 4);
        LCD_send_string("Score:6/10");
        while (1);
    }

    return 0;
}

/* ------------------------ TIMER ISR -------------------------- */
ISR(TIMER0_COMP_vect)
{
    timer_counter++;
}
