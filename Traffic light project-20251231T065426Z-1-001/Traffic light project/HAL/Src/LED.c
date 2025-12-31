/*
 * LED.c 
 * Created: 8/12/2024 4:34:35 PM
 *  Author:Embedcrest Technology Private Limited
 */

#include "LED.h"
#include "DIO.h"

// Initialize LED pin
void LED_init(unsigned char port, unsigned char pin)
{
    DIO_set_pin_dir(port, pin, 1);
}

// Turn LED ON
void LED_on(unsigned char port, unsigned char pin)
{
    DIO_write_pin(port, pin, 1);
}

// Turn LED OFF
void LED_off(unsigned char port, unsigned char pin)
{
    DIO_write_pin(port, pin, 0);
}

// Toggle LED
void LED_flip(unsigned char port, unsigned char pin)
{
    DIO_toggle_pin(port, pin);
}
