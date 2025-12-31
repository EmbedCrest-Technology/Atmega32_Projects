/*
 * voting_machine.c
 *
 * Created: 10/12/2024 11:30:06 PM
 * Author : Embedcrest Technology Private Limited
 */

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "LCD.h"
#include "BUTTON.h"
#include "LED.h"

int main(void)
{
    LCD_init();

    // ---- Buttons ----
    BUTTON_init_with_pull_up('B',0);
    BUTTON_init_with_pull_up('B',1);
    BUTTON_init_with_pull_up('B',2);
    BUTTON_init_with_pull_up('B',3);
    BUTTON_init_with_pull_up('B',4);

    BUTTON_init('A',0);      // Admin validate
    BUTTON_init('A',1);      // Reset system

    // ---- LEDs ----
    LED_init('C',0); // A indicator
    LED_init('C',1); // B indicator
    LED_init('C',2); // C indicator
    LED_init('C',3); // D indicator
    LED_init('C',4); // Ready LED
    LED_init('C',5); // Voting LED
    LED_init('C',6); // Lock LED

    // ---- Counters ----
    char countA = 0, countB = 0, countC = 0, countD = 0;

    char prevA, prevB, prevC, prevD;
    char selA = 0, selB = 0, selC = 0, selD = 0;

    char allowVote = 0;
    char enterPressed = 0;

    // Start LCD
    LCD_send_string("A=0");
    LCD_move_cursor(1,12);
    LCD_send_string("B=0");
    LCD_move_cursor(2,1);
    LCD_send_string("C=0");
    LCD_move_cursor(2,12);
    LCD_send_string("D=0");

    while (1)
    {
        selA = selB = selC = selD = 0;
        prevA = countA;
        prevB = countB;
        prevC = countC;
        prevD = countD;

        // ==================== WAIT FOR ADMIN ====================
        do
        {
            LED_turn_off('C', 5);
            LED_turn_on('C', 4);

            // Reset button (A1)
            if (BUTTON_read('A',1) == 1)
            {
                LED_turn_off('C', 6);
                countA = countB = countC = countD = 0;

                LCD_clr_screen();
                LCD_send_string("A=0");
                LCD_move_cursor(1,12);
                LCD_send_string("B=0");
                LCD_move_cursor(2,1);
                LCD_send_string("C=0");
                LCD_move_cursor(2,12);
                LCD_send_string("D=0");
            }

            // Admin authorization (A0 button)
            allowVote = BUTTON_read('A',0);
            if (allowVote == 1)
            {
                LED_turn_off('C', 4);
                LED_turn_on('C', 5);
            }

        } while (allowVote == 0);

start_vote:

        // ==================== HANDLE VOTING ====================
        do
        {
            // Candidate A
            if (BUTTON_read('B',0) == 0)
            {
                if (selA == 0)
                {
                    if (selB) { countB--; selB = 0; LED_turn_off('C',1); }
                    if (selC) { countC--; selC = 0; LED_turn_off('C',2); }
                    if (selD) { countD--; selD = 0; LED_turn_off('C',3); }

                    countA++;
                    selA = 1;
                    LED_turn_on('C',0);
                }
                else
                {
                    countA--;
                    selA = 0;
                    LED_turn_off('C',0);
                }
            }

            // Candidate B
            else if (BUTTON_read('B',1) == 0)
            {
                if (selB == 0)
                {
                    if (selA) { countA--; selA = 0; LED_turn_off('C',0); }
                    if (selC) { countC--; selC = 0; LED_turn_off('C',2); }
                    if (selD) { countD--; selD = 0; LED_turn_off('C',3); }

                    countB++;
                    selB = 1;
                    LED_turn_on('C',1);
                }
                else
                {
                    countB--;
                    selB = 0;
                    LED_turn_off('C',1);
                }
            }

            // Candidate C
            else if (BUTTON_read('B',2) == 0)
            {
                if (selC == 0)
                {
                    if (selA) { countA--; selA = 0; LED_turn_off('C',0); }
                    if (selB) { countB--; selB = 0; LED_turn_off('C',1); }
                    if (selD) { countD--; selD = 0; LED_turn_off('C',3); }

                    countC++;
                    selC = 1;
                    LED_turn_on('C',2);
                }
                else
                {
                    countC--;
                    selC = 0;
                    LED_turn_off('C',2);
                }
            }

            // Candidate D
            else if (BUTTON_read('B',3) == 0)
            {
                if (selD == 0)
                {
                    if (selA) { countA--; selA = 0; LED_turn_off('C',0); }
                    if (selB) { countB--; selB = 0; LED_turn_off('C',1); }
                    if (selC) { countC--; selC = 0; LED_turn_off('C',2); }

                    countD++;
                    selD = 1;
                    LED_turn_on('C',3);
                }
                else
                {
                    countD--;
                    selD = 0;
                    LED_turn_off('C',3);
                }
            }

            _delay_ms(200);

            // ENTER button
            enterPressed = BUTTON_read('B',4);

            if (enterPressed == 0 &&
                prevA == countA && prevB == countB &&
                prevC == countC && prevD == countD)
            {
                LCD_clr_screen();
                LCD_send_string("please vote");
                _delay_ms(1500);

                LCD_clr_screen();
                LCD_move_cursor(1,1);
                LCD_send_string("A=");
                LCD_send_data((countA/10) + 48);
                LCD_send_data((countA%10) + 48);

                LCD_move_cursor(1,12);
                LCD_send_string("B=");
                LCD_send_data((countB/10) + 48);
                LCD_send_data((countB%10) + 48);

                LCD_move_cursor(2,1);
                LCD_send_string("C=");
                LCD_send_data((countC/10) + 48);
                LCD_send_data((countC%10) + 48);

                LCD_move_cursor(2,12);
                LCD_send_string("D=");
                LCD_send_data((countD/10) + 48);
                LCD_send_data((countD%10) + 48);

                goto start_vote;
            }

            if (enterPressed == 0)
            {
                LED_turn_off('C',0);
                LED_turn_off('C',1);
                LED_turn_off('C',2);
                LED_turn_off('C',3);
                LED_turn_on('C',6);
            }

        } while (enterPressed == 1);

        // ==================== Update LCD Live Counts ====================
        LCD_move_cursor(1,3);
        LCD_send_data((countA/10)+48);
        LCD_send_data((countA%10)+48);

        LCD_move_cursor(1,14);
        LCD_send_data((countB/10)+48);
        LCD_send_data((countB%10)+48);

        LCD_move_cursor(2,3);
        LCD_send_data((countC/10)+48);
        LCD_send_data((countC%10)+48);

        LCD_move_cursor(2,14);
        LCD_send_data((countD/10)+48);
        LCD_send_data((countD%10)+48);
    }
}
