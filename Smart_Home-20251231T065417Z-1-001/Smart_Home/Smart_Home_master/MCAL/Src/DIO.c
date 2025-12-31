/*
 * DIO.c
 *
 * Created: 21/10/2024  9.07 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#include <avr/io.h>
#include "macro_function.h"
#include "DIO.h"

void DIO_set_pin_dir(volatile uint8_t* port, uint8_t bit_number, uint8_t direction)
{
    if (direction == 1) {
        SET_BIT(*((volatile uint8_t*)(port + 1)), bit_number);  // DDRx = port + 1
    } else {
        CLR_BIT(*((volatile uint8_t*)(port + 1)), bit_number);
    }
}

void DIO_write_pin(volatile uint8_t* port, uint8_t bit_number, uint8_t output_value)
{
    if (output_value == 1) {
        SET_BIT(*port, bit_number);  // PORTx
    } else {
        CLR_BIT(*port, bit_number);
    }
}

void DIO_toggle_pin(volatile uint8_t* port, uint8_t bit_number)
{
    TOG_BIT(*port, bit_number);
}

uint8_t DIO_read_pin(volatile uint8_t* port, uint8_t bit_number)
{
    return READ_BIT(*((volatile uint8_t*)(port + 2)), bit_number);  // PINx = port + 2
}

void DIO_set_port_dir(volatile uint8_t* port, uint8_t direction)
{
    *((volatile uint8_t*)(port + 1)) = direction;  // DDRx
}

void DIO_write_port(volatile uint8_t* port, uint8_t output_value)
{
    *port = output_value;  // PORTx
}

void DIO_toggle_port(volatile uint8_t* port)
{
    *port = ~(*port);
}

uint8_t DIO_read_port(volatile uint8_t* port)
{
    return *((volatile uint8_t*)(port + 2));  // PINx
}

void DIO_connect_pull_up(volatile uint8_t* port, uint8_t pin_number, uint8_t connect_pull_up)
{
    if (connect_pull_up == 1) {
        SET_BIT(*port, pin_number);  // PORTx enables pull-up when DDRx=0
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
    number &= 0x0F;
    number <<= 4;
    *port &= 0x0F;
    *port |= number;
}
