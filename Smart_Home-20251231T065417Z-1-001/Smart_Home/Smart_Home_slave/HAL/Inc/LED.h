/*
 * LED.h
 *
 * Created: 20/11/2024   11.11 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#ifndef LED_H_
#define LED_H_

// Fixed: Changed parameter types to match main_config.h PORTC/PORTD usage
void LED_init(volatile uint8_t* port, uint8_t pin_number);
void LED_turn_on(volatile uint8_t* port, uint8_t pin_number);
void LED_turn_off(volatile uint8_t* port, uint8_t pin_number);
void LED_toggle(volatile uint8_t* port, uint8_t pin_number);

// Added helper function used in main.c
void LED_turn_on_off(volatile uint8_t* port, uint8_t pin_number, uint8_t state);

#endif /* LED_H_ */
