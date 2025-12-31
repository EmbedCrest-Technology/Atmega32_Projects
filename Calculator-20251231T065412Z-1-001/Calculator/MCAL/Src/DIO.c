/*
 * DIO.c
 *
 *Created: 3/12/2024 12:49:24 AM
 *  Author:Embedcrest Technology Private Limited
 */

#include <avr/io.h>
#include "DIO.h"
#include "macro_function.h"

#define CASE_PORT(letter, upper, lower) case upper: case lower

/* ===================== INTERNAL HELPERS ====================== */

static volatile uint8_t* get_ddr(char port)
{
    switch (port)
    {
        CASE_PORT(port, 'A', 'a'): return &DDRA;
        CASE_PORT(port, 'B', 'b'): return &DDRB;
        CASE_PORT(port, 'C', 'c'): return &DDRC;
        CASE_PORT(port, 'D', 'd'): return &DDRD;
        default: return 0;
    }
}

static volatile uint8_t* get_port(char port)
{
    switch (port)
    {
        CASE_PORT(port, 'A', 'a'): return &PORTA;
        CASE_PORT(port, 'B', 'b'): return &PORTB;
        CASE_PORT(port, 'C', 'c'): return &PORTC;
        CASE_PORT(port, 'D', 'd'): return &PORTD;
        default: return 0;
    }
}

static volatile uint8_t* get_pin(char port)
{
    switch (port)
    {
        CASE_PORT(port, 'A', 'a'): return &PINA;
        CASE_PORT(port, 'B', 'b'): return &PINB;
        CASE_PORT(port, 'C', 'c'): return &PINC;
        CASE_PORT(port, 'D', 'd'): return &PIND;
        default: return 0;
    }
}

/* ======================== PUBLIC API ========================= */

void DIO_set_pin_dir(char port, uint8_t bit, uint8_t dir)
{
    volatile uint8_t* ddr = get_ddr(port);
    if (!ddr) return;

    if (dir) SET_BIT(*ddr, bit);
    else     CLR_BIT(*ddr, bit);
}

void DIO_write_pin(char port, uint8_t bit, uint8_t value)
{
    volatile uint8_t* reg = get_port(port);
    if (!reg) return;

    if (value) SET_BIT(*reg, bit);
    else       CLR_BIT(*reg, bit);
}

uint8_t DIO_read_pin(char port, uint8_t bit)
{
    volatile uint8_t* reg = get_pin(port);
    if (!reg) return 0;

    return READ_BIT(*reg, bit);
}

void DIO_toggle_pin(char port, uint8_t bit)
{
    volatile uint8_t* reg = get_port(port);
    if (!reg) return;

    TOG_BIT(*reg, bit);
}

void DIO_set_port_dir(char port, uint8_t dir)
{
    volatile uint8_t* ddr = get_ddr(port);
    if (ddr) *ddr = dir;
}

void DIO_write_port(char port, uint8_t value)
{
    volatile uint8_t* reg = get_port(port);
    if (reg) *reg = value;
}

void DIO_toggle_port(char port)
{
    volatile uint8_t* reg = get_port(port);
    if (reg) *reg ^= 0xFF;
}

uint8_t DIO_read_port(char port)
{
    volatile uint8_t* reg = get_pin(port);
    return reg ? *reg : 0;
}

void DIO_connect_pull_up(char port, uint8_t bit, uint8_t en)
{
    volatile uint8_t* reg = get_port(port);
    if (!reg) return;

    if (en) SET_BIT(*reg, bit);
    else    CLR_BIT(*reg, bit);
}

void DIO_write_low_nibble(char port, uint8_t value)
{
    volatile uint8_t* reg = get_port(port);
    if (!reg) return;

    value &= 0x0F;
    *reg = (*reg & 0xF0) | value;
}

void DIO_write_high_nibble(char port, uint8_t value)
{
    volatile uint8_t* reg = get_port(port);
    if (!reg) return;

    value <<= 4;
    *reg = (*reg & 0x0F) | value;
}
