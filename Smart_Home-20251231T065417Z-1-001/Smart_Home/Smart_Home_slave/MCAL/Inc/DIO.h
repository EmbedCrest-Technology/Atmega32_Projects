/*
 * DIO.h
 *
 * Created: 20/10/2024   11.11 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#ifndef DIO_H_
#define DIO_H_

// Fixed: Changed to match LED.c (volatile uint8_t* port) and main_config.h PORTC/PORTD
void DIO_set_pin_dir(volatile uint8_t* port, uint8_t bit_number, uint8_t direction);
void DIO_write_pin(volatile uint8_t* port, uint8_t bit_number, uint8_t output_value);
void DIO_toggle_pin(volatile uint8_t* port, uint8_t bit_number);
uint8_t DIO_read_pin(volatile uint8_t* port, uint8_t bit_number);

void DIO_set_port_dir(volatile uint8_t* port, uint8_t direction);
void DIO_write_port(volatile uint8_t* port, uint8_t output_value);
void DIO_toggle_port(volatile uint8_t* port);
uint8_t DIO_read_port(volatile uint8_t* port);

void DIO_connect_pull_up(volatile uint8_t* port, uint8_t pin_number, uint8_t connect_pull_up);
void DIO_write_low_nibble(volatile uint8_t* port, uint8_t number);
void DIO_write_high_nibble(volatile uint8_t* port, uint8_t number);

#endif /* DIO_H_ */
