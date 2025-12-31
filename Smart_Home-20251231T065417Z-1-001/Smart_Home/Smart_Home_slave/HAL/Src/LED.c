/*
 * LED.c
 *
 * Created: 20/10/2024  11.11 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#include "LED.h"
#include "DIO.h"

void LED_init(volatile uint8_t* port, uint8_t pin_number)
{
    DIO_set_pin_dir(port, pin_number, 1);
}

void LED_turn_on(volatile uint8_t* port, uint8_t pin_number)
{
    DIO_write_pin(port, pin_number, 1);
}

void LED_turn_off(volatile uint8_t* port, uint8_t pin_number)
{
    DIO_write_pin(port, pin_number, 0);
}

void LED_toggle(volatile uint8_t* port, uint8_t pin_number)
{
    DIO_toggle_pin(port, pin_number);
}

// Added helper function required by main.c
void LED_turn_on_off(volatile uint8_t* port, uint8_t pin_number, uint8_t state)
{
    if (state == 1) {
        LED_turn_on(port, pin_number);
    } else {
        LED_turn_off(port, pin_number);
    }
}
