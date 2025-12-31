/*
 * macro_function.h
 * Created: 15/10/2024 12:48:58 AM
 *  Author: Embedcrest Technology Private Limited
*/

#ifndef MACRO_FUNCTION_H_
#define MACRO_FUNCTION_H_

#define SET_BIT(reg, bit)       (reg |= (1 << bit))
#define CLR_BIT(reg, bit)       (reg &= ~(1 << bit))
#define TOG_BIT(reg, bit)       (reg ^= (1 << bit))
#define READ_BIT(reg, bit)      ((reg >> bit) & 1)

#endif /* MACRO_FUNCTION_H_ */
