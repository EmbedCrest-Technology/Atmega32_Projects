/*
 * TIMER.c
 *
 * Created:21/10/2024  9.17 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "TIMER.h"

void TIMER0_CTC_init_with_interrupt(void)
{
    // CTC mode
    TCCR0 &= ~(1 << WGM00);
    TCCR0 |= (1 << WGM01);
    
    OCR0 = 80;  // Compare match value
    
    // Prescaler 1024
    TCCR0 |= (1 << CS00);
    TCCR0 &= ~(1 << CS01);
    TCCR0 |= (1 << CS02);
    
    // Enable interrupt
    sei();
    TIMSK |= (1 << OCIE0);
    // 10ms interrupt period @ 1MHz / 1024
}
