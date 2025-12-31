/*
 * TIMER.h
 * Created: 15/10/2024 12:48:58 AM
 *  Author: Embedcrest Technology Private Limited
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "macro_function.h"
#include <avr/interrupt.h>

/*  
   ISR variable names updated in main.c:
   - flag1  -> timer_counter
   - flag2  -> timeout_flag
*/

void TIMER0_normal_init_with_interrupt(void);
void TIMER0_CTC_init_with_interrupt(void);

void TIMER2_normal_init_with_interrupt(void);
void TIMER2_CTC_init_with_interrupt(void);

#endif /* TIMER_H_ */
