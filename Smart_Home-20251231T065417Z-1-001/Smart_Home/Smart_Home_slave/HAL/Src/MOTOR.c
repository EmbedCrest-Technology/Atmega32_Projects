/*
 * DC_MOTOR.c
 *
 * Created: 20/10/2024  11.11 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#include <avr/io.h>
#include "macro_function.h"

void Servo_motor_with_TIMER1_fast_pwm_ICRA_wave(double angle)
{
    //determine Fast PWM mode with ICR1 as TOP (WGM13:0 = 14)
    CLR_BIT(TCCR1A, WGM10);
    SET_BIT(TCCR1A, WGM11);
    SET_BIT(TCCR1B, WGM12);
    SET_BIT(TCCR1B, WGM13);
    
    //determine prescaler=1, timer1_clock=(cpu_clock/prescaler)  cpu_clock=1MHZ
    SET_BIT(TCCR1B, CS10);
    CLR_BIT(TCCR1B, CS11);
    CLR_BIT(TCCR1B, CS12);
    
    //set OC1A as output pin to generation wave
    SET_BIT(DDRD, PD5);
    
    //clear OC1A on compare match and set OC1A at bottom=0 (non-inverting mode)
    CLR_BIT(TCCR1A, COM1A0);
    SET_BIT(TCCR1A, COM1A1);
    
    //load value in OCR1A to compare match
    OCR1A = (1.5 + (0.5/90.0) * angle) * 1000;
    
    //load value in ICR1=top define the TOP value for the PWM period (20ms)
    ICR1 = 19999; 

    /*
    on_pulse repeated every 20ms or cycle repeated every 20ms
    on_pulse=1ms,angle=-90 and on_pulse=1.5ms,angle=0 and on_pulse=2ms,angle=+90
    timer_tick_time=(1/timer1_clock)=0.000001s=.001ms
    on_pulse repeated every 0.001ms*OCR1=??ms,cycle repeated every 0.001ms*ICR1=20 ms
    */
}
