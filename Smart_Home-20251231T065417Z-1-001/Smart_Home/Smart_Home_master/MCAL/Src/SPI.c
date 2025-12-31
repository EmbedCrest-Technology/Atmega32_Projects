/*
 * SPI.c
 *
 * Created: 21/10/2024  9.07 AM
 *  Author: Embedcrest Technology Private Limited
 */
 
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL  // Fixed: Matches system F_CPU
#include <util/delay.h>
#include "SPI.h"

void SPI_master_init(void)
{
    SET_BIT(DDRB, PB4);  // SS as output
    SET_BIT(DDRB, PB5);  // MOSI as output
    SET_BIT(DDRB, PB7);  // SCK as output
    SET_BIT(PORTB, PB4); // SS high (not active)
    
    SPCR |= (1 << SPE);  // Enable SPI
    SPCR |= (1 << MSTR); // Master mode
    SPCR |= (1 << SPR0); // F_CPU/16
    SPCR &= ~(1 << SPR1);
}

void SPI_slave_init(void)
{
    SET_BIT(DDRB, PB6);  // MISO as output
    SPCR |= (1 << SPE);  // Enable SPI
    SPCR &= ~(1 << MSTR); // Slave mode
}

uint8_t SPI_master_transmit_and_receive_data(uint8_t data)
{
    PORTB &= ~(1 << PB4);  // SS low (active slave)
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));  // Wait for transfer complete
    PORTB |= (1 << PB4);  // SS high
    return SPDR;
}

void SPI_master_transmit_string(uint8_t *ptr)
{
    while (*ptr != '\0') {
        SPI_master_transmit_and_receive_data(*ptr);
        _delay_ms(300);
        ptr++;
    }
}

uint8_t SPI_slave_receive_and_transmit_data(uint8_t data)
{
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));
    return SPDR;
}

void SPI_master_init_with_interrupt(void)
{
    SET_BIT(DDRB, PB4);  // SS as output
    SET_BIT(DDRB, PB5);  // MOSI as output
    SET_BIT(DDRB, PB7);  // SCK as output
    SET_BIT(PORTB, PB4); // SS high
    
    SPCR |= (1 << SPE);  // Enable SPI
    SPCR |= (1 << MSTR); // Master mode
    SPCR |= (1 << SPR0); // F_CPU/16
    SPCR &= ~(1 << SPR1);
    
    sei();               // Global interrupt
    SPCR |= (1 << SPIE); // SPI interrupt
}
