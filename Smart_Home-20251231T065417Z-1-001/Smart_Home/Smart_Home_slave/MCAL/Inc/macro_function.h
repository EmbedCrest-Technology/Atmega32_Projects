/*
 * macro_function.h
 *
 * Created: 20/10/2024    12.34 PM
 *  Author: Embedcrest Technologo Private Limited
 */ 

#ifndef MACRO_FUNCTION_H_
#define MACRO_FUNCTION_H_

#define SET_BIT(port_register, bit_number)   port_register |= (1 << bit_number)  // Fixed: Added spaces
#define CLR_BIT(port_register, bit_number)   port_register &= (~(1 << bit_number))  // Fixed: Added spaces
#define TOG_BIT(port_register, bit_number)   port_register ^= (1 << bit_number)    // Fixed: Added spaces
#define READ_BIT(port_register, bit_number)  ((port_register & (1 << bit_number)) >> bit_number)  // Fixed: Added spaces

#endif /* MACRO_FUNCTION_H_ */
