/*
 * CFile1.c -> SPI.c
 *
 * Created: 21/10/2024  9.07 AM
 *  Author: Embedcrest Technology Private Limited
 */
 
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL  // Fixed: Matches main.c F_CPU
#include <util/delay.h>
#include "macro_function.h"

void SPI_master_init(void)
{
    // SS,MOSI,SCK AS output and MISO AS input
    SET_BIT(DDRB, PB4);  // SS as output
    SET_BIT(DDRB, PB5);  // MOSI as output
    SET_BIT(DDRB, PB7);  // SCK as output
    SET_BIT(PORTB, PB4); // Not active slave
    
    // Enable SPI, Master mode, F_CPU/16
    SET_BIT(SPCR, SPE);
    SET_BIT(SPCR, MSTR);
    SET_BIT(SPCR, SPR0);
    CLR_BIT(SPCR, SPR1);
}

void SPI_slave_init(void)
{
    // MISO as output, others input
    SET_BIT(DDRB, PB6);  // MISO as output
    
    // Enable SPI, Slave mode
    SET_BIT(SPCR, SPE);
    CLR_BIT(SPCR, MSTR);
}

uint8_t SPI_master_transmit_and_receive_data(uint8_t data)  // Fixed: Proper type
{
    CLR_BIT(PORTB, PB4);  // Activate slave
    SPDR = data;
    while (READ_BIT(SPSR, SPIF) == 0);
    return SPDR;
}

void SPI_master_transmit_string(uint8_t *ptr)  // Fixed: Proper type
{
    while (*ptr != '\0') {
        SPI_master_transmit_and_receive_data(*ptr);
        _delay_ms(300);
        ptr++;
    }
}

uint8_t SPI_slave_receive_and_transmit_data(uint8_t data)  // Fixed: Proper type
{
    SPDR = data;
    while (READ_BIT(SPSR, SPIF) == 0);
    return SPDR;
}

void SPI_master_init_with_interrupt(void)
{
    SPI_master_init();  // Reuse master init
    sei();              // Global interrupt enable
    SET_BIT(SPCR, SPIE); // SPI interrupt enable
}
