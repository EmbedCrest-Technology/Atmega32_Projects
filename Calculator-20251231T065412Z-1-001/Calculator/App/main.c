/*
 * Calculator.c
 *
 * Created: 1/12/2024 9:21:58 PM
 * Author : Embedcrest Technology Private Limited
 */

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LCD.h"
#include "KEYBAD.h"

#define MAX_DIGITS 4

int main(void)
{
    LCD_init();
    KEYBAD_init();

    long int num1, num2, result;
    char op;
    char num1_buf[MAX_DIGITS + 1];
    char num2_buf[MAX_DIGITS + 1];
    char key;
    char idx1, idx2;

    while (1)
    {
reset_all:
        idx1 = idx2 = 0;
        memset(num1_buf, 0, sizeof(num1_buf));
        memset(num2_buf, 0, sizeof(num2_buf));
        op = 0;

        LCD_clr_screen();
        LCD_send_cmd(CURSOR_ON_DISPLAY_ON);

        /* ------------------- Input Number 1 ------------------- */
        while (idx1 < MAX_DIGITS)
        {
            key = KEYBAD_check_press();

            if ((key >= '0' && key <= '9') || key == '.' ||
                ((key == '+' || key == '-') && idx1 == 0))
            {
                num1_buf[idx1++] = key;
                LCD_send_data(key);
                _delay_ms(250);
            }
            else if (key == '+' || key == '-' || key == '*' ||
                     key == '/' || key == '^' || key == 'S' || key == '%')
            {
                op = key;
                (op == 'S') ? LCD_send_string("Sqrt(") : LCD_send_data(op);
                break;
            }
            else if (key == 'A')
            {
                goto reset_all;
            }
        }

        num1_buf[idx1] = '\0';
        num1 = atoi(num1_buf);

        /* ------------------- Input Operation (if not yet given) ------------------- */
        if (op == 0)
        {
            while (1)
            {
                key = KEYBAD_check_press();
                if (key == '+' || key == '-' || key == '*' ||
                    key == '/' || key == '^' || key == 'S' || key == '%')
                {
                    op = key;
                    (op == 'S') ? LCD_send_string("Sqrt(") : LCD_send_data(op);
                    break;
                }
                else if (key == 'A')
                {
                    goto reset_all;
                }
            }
            _delay_ms(250);
        }

validate_input:
        if (((op == '*' || op == '/' || op == '^' || op == '%') && num1 == 0) ||
            (op == 'S' && num1 != 0))
        {
            LCD_clr_screen();
            LCD_send_string("Error");
            _delay_ms(1000);
            goto reset_all;
        }

        /* ------------------- Input Number 2 ------------------- */
        while (idx2 < MAX_DIGITS)
        {
            key = KEYBAD_check_press();

            if ((key >= '0' && key <= '9') || key == '.' ||
                ((key == '+' || key == '-') && idx2 == 0))
            {
                num2_buf[idx2++] = key;
                LCD_send_data(key);
                _delay_ms(250);
            }
            else if (key == '=')
            {
                break;
            }
            else if (key == 'A')
            {
                goto reset_all;
            }
        }

        num2_buf[idx2] = '\0';
        num2 = atoi(num2_buf);

        /* ------------------- Perform Calculation ------------------- */
        while (1)
        {
            key = KEYBAD_check_press();

            if (key == '=')
            {
                if (op == 'S')
                    LCD_send_data(')');

                LCD_send_data('=');

                switch (op)
                {
                    case '+': result = num1 + num2; break;
                    case '-': result = num1 - num2; break;
                    case '*': result = num1 * num2; break;

                    case '/':
                        if (num2 != 0)
                            result = num1 / num2;
                        else
                        {
                            LCD_clr_screen();
                            LCD_send_string("Error: Div by 0");
                            continue;
                        }
                        break;

                    case '^':
                        result = pow(num1, num2) + 1;
                        break;

                    case 'S':
                        if (num2 >= 0)
                            result = sqrt(num2);
                        else
                        {
                            LCD_clr_screen();
                            LCD_send_string("Error: Negative sqrt");
                            continue;
                        }
                        break;

                    case '%': result = num1 % num2; break;
                }

                char res_str[10];
                sprintf(res_str, "%ld", result);
                LCD_send_string(res_str);
                break;
            }
        }

        LCD_send_cmd(CURSOR_Off_DISPLAY_ON);
        _delay_ms(250);

        /* ------------------- Continue With Result (Ans) ------------------- */
        while (1)
        {
            key = KEYBAD_check_press();

            if (key == '+' || key == '-' || key == '*' || key == '/' ||
                key == '^' || key == 'S' || key == '%')
            {
                LCD_clr_screen();
                LCD_send_string("Ans");

                op = key;
                num1 = result;

                memset(num2_buf, 0, sizeof(num2_buf));
                idx2 = 0;

                (op == 'S') ? LCD_send_string("Sqrt(") : LCD_send_data(op);

                _delay_ms(250);
                goto validate_input;
            }
        }
    }
}
