/*
 * DIO.c
 *
 * Created: 21/10/2024  9.00 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#include <avr/io.h>
#include "macro_function.h"

// Fixed: Updated ALL functions to use volatile uint8_t* port (matches corrected DIO.h)
void DIO_set_pin_dir(volatile uint8_t* port, uint8_t bit_number, uint8_t direction)
{
    if (direction == 1) {
        SET_BIT(*port, bit_number);  // Fixed: Direct register access
    } else {
        CLR_BIT(*port, bit_number);
    }
}

void DIO_write_pin(volatile uint8_t* port, uint8_t bit_number, uint8_t output_value)
{
    if (output_value == 1) {
        SET_BIT(*port, bit_number);  // Fixed: PORTx register direct access
    } else {
        CLR_BIT(*port, bit_number);
    }
}

void DIO_toggle_pin(volatile uint8_t* port, uint8_t bit_number)
{
    TOG_BIT(*port, bit_number);  // Fixed: PORTx register direct access
}

uint8_t DIO_read_pin(volatile uint8_t* port, uint8_t bit_number)
{
    return READ_BIT(*port, bit_number);  // Fixed: PINx register access
}

void DIO_set_port_dir(volatile uint8_t* ddr_port, uint8_t direction)
{
    *ddr_port = direction;  // Fixed: Direct DDRx access
}

void DIO_write_port(volatile uint8_t* port, uint8_t output_value)
{
    *port = output_value;  // Fixed: Direct PORTx access
}

void DIO_toggle_port(volatile uint8_t* port)
{
    *port = ~(*port);  // Fixed: Direct PORTx access
}

uint8_t DIO_read_port(volatile uint8_t* pin_port)
{
    return *pin_port;  // Fixed: Direct PINx access
}

void DIO_connect_pull_up(volatile uint8_t* port, uint8_t pin_number, uint8_t connect_pull_up)
{
    if (connect_pull_up == 1) {
        SET_BIT(*port, pin_number);
    } else {
        CLR_BIT(*port, pin_number);
    }
}

void DIO_write_low_nibble(volatile uint8_t* port, uint8_t value)
{
    value &= 0x0F;
    *port &= 0xF0;
    *port |= value;
}

void DIO_write_high_nibble(volatile uint8_t* port, uint8_t number)
{
    number <<= 4;
    *port &= 0x0F;
    *port |= number;
}
