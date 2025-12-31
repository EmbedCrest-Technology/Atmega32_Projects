/*
 * UART.h
 *
 * Created: 16/12/2024 11:55:06 AM
 *  Author: Embedcrest Technology Private Limited
 */ 


#ifndef UART_H_
#define UART_H_

void UART_init(unsigned long baud);

void UART_send_data(char data);

void UART_send_string(char *ptr);

char UART_receive_data(void);

#endif /* UART_H_ */
