/*
 * EEPROM.c
 *
 * Created: 21/10/2024  9.07 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#include <avr/io.h>
#include "macro_function.h"

void EEPROM_write(uint16_t address, uint8_t data)  // Fixed: Proper types
{
    EEARL = (uint8_t)address;
    EEARH = (uint8_t)(address >> 8);
    EEDR = data;
    SET_BIT(EECR, EEMWE);
    SET_BIT(EECR, EEWE);
    while (READ_BIT(EECR, EEWE) == 1);
}

uint8_t EEPROM_read(uint16_t address)  // Fixed: Proper return type
{
    EEARL = (uint8_t)address;
    EEARH = (uint8_t)(address >> 8);
    SET_BIT(EECR, EERE);
    return EEDR;
}
