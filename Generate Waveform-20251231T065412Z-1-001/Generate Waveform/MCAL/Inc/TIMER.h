/*
 * TIMER.h
 *
 * Created: 8/12/2024 4:08:00 PM
 *  Author: Embedcrest Technology Private Limited
 */ 

#ifndef TIMER_H_
#define TIMER_H_

#include "macro_function.h"
#include <avr/interrupt.h>

/* Updated Function Names */
void setup_timer0_ctc_wave(void);
void setup_timer1_fast_pwm8(void);
void setup_timer2_phase_correct_pwm(void);

/* Other Existing Functions (Not Requested to Change) */
void TIMER0_fast_pwm_wave(void);
void TIMER0_phase_correct_pwm_wave(void);

void TIMER2_CTC_wave_nonpwm(void);
void TIMER2_fast_pwm_wave(void);

#endif /* TIMER_H_ */
