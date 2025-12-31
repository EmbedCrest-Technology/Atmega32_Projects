/*
 * EEPROM.h
 *
 * Created: 20/10/2024   11.11 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#ifndef EEPROM_H_
#define EEPROM_H_

void EEPROM_write(uint16_t address, uint8_t data);      // Fixed: Standard AVR types
uint8_t EEPROM_read(uint16_t address);                 // Fixed: Standard AVR types

#endif /* EEPROM_H_ */
