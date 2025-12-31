/*
 * SPI.h
 *
 * Created: 21/10/2024  9.07 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#ifndef SPI_H_
#define SPI_H_

void SPI_master_init(void);
void SPI_slave_init(void);
uint8_t SPI_master_transmit_and_receive_data(uint8_t data);       // Fixed: Standard types
void SPI_master_transmit_string(uint8_t *ptr);                    // Fixed: Standard type
uint8_t SPI_slave_receive_and_transmit_data(uint8_t data);        // Fixed: Standard type
void SPI_master_init_with_interrupt(void);

#endif /* SPI_H_ */
