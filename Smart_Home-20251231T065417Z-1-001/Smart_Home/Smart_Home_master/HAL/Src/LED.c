/*
 * LED.c
 *
 * Created: 21/10/2024  9.07 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#include "LED.h"
#include "DIO.h"

void LED_init(volatile uint8_t* port, uint8_t pin_number)  // Fixed: Matches corrected LED.h
{
    DIO_set_pin_dir(port, pin_number, 1);
}

void LED_turn_on(volatile uint8_t* port, uint8_t pin_number)  // Fixed: Matches corrected LED.h
{
    DIO_write_pin(port, pin_number, 1);
}

void LED_turn_off(volatile uint8_t* port, uint8_t pin_number)  // Fixed: Matches corrected LED.h
{
    DIO_write_pin(port, pin_number, 0);
}

void LED_toggle(volatile uint8_t* port, uint8_t pin_number)  // Fixed: Matches corrected LED.h
{
    DIO_toggle_pin(port, pin_number);
}
