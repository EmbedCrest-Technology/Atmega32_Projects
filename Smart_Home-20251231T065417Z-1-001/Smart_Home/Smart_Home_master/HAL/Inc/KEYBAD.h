/*
 * KEYBAD.h
 *
 * Created: 21/10/2024  9.07 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#ifndef KEYBAD_H_
#define KEYBAD_H_

#define PORT_11     PORTC   // Fixed: Char literal ? AVR port register
#define PORT_22     PORTC   // Fixed: Char literal ? AVR port register
#define NOT_pressed 0xFF

void KEYBAD_init(void);
uint8_t KEYBAD_check_press(void);  // Fixed: Standard AVR return type

#endif /* KEYBAD_H_ */
