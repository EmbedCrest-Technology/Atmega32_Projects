/*
 * EEPROM.c
 *
 * Created: 21/10/2024  9.17 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#include <avr/io.h>
#include "EEPROM.h"

void EEPROM_write(uint16_t address, uint8_t data)
{
    EEARL = (uint8_t)address;
    EEARH = (uint8_t)(address >> 8);
    EEDR = data;
    EECR |= (1 << EEMPE);  // Fixed: Direct bit set
    EECR |= (1 << EEWE);
    while (EECR & (1 << EEWE));  // Fixed: Direct bit check
}

uint8_t EEPROM_read(uint16_t address)
{
    EEARL = (uint8_t)address;
    EEARH = (uint8_t)(address >> 8);
    EECR |= (1 << EERE);
    return EEDR;
}
