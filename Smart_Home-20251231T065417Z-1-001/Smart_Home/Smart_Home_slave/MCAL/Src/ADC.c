/*
 * ADC.c
 *
 * Created: 21/10/2024   9.00 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#include <avr/io.h>
#include "macro_function.h"

void ADC_init(void)
{
    // Enable ADC
    SET_BIT(ADCSRA, ADEN);
    
    // Determine pin connected ADC PA0 (ADC0)
    CLR_BIT(ADMUX, MUX0);
    CLR_BIT(ADMUX, MUX1);
    CLR_BIT(ADMUX, MUX2);
    CLR_BIT(ADMUX, MUX3);
    CLR_BIT(ADMUX, MUX4);
    
    // Configuration voltage internal 2.56V
    SET_BIT(ADMUX, REFS0);
    SET_BIT(ADMUX, REFS1);
    
    // Configuration clock 1MHz/64 = 15.625KHz (proper for 1MHz F_CPU)
    CLR_BIT(ADCSRA, ADPS0);
    SET_BIT(ADCSRA, ADPS1);
    SET_BIT(ADCSRA, ADPS2);
}

uint16_t ADC_u16read(void)  // Fixed: Return type matches ADC.h
{
    uint16_t ret_read;
    SET_BIT(ADCSRA, ADSC);  // Start conversion
    while (READ_BIT(ADCSRA, ADSC) == 1);  // Fixed: Proper polling
    
    ret_read = ADCL | (ADCH << 8);  // Fixed: Proper ADC reading order
    return ret_read;
}

