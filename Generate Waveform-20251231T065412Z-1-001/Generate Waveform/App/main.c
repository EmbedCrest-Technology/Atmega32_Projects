/*
 * Generate_Waveforms.c
 *
 * Created: 8/12/2024 1:43:36 AM
 * Author :Embedcrest Technology Private Limited
 */ 

#include <avr/io.h>
#include "TIMER.h"

int main(void)
{
    setup_timer0_ctc_wave();
    setup_timer1_fast_pwm8();
    setup_timer2_phase_correct_pwm();
}
