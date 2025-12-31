/*
 * LED.h
 *
 * Created: 21/10/2024  9.07 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#ifndef LED_H_
#define LED_H_

// Fixed: Updated to match corrected DIO.h for master (PORTB status LEDs)
void LED_init(volatile uint8_t* port, uint8_t pin_number);
void LED_turn_on(volatile uint8_t* port, uint8_t pin_number);
void LED_turn_off(volatile uint8_t* port, uint8_t pin_number);
void LED_toggle(volatile uint8_t* port, uint8_t pin_number);

#endif /* LED_H_ */
