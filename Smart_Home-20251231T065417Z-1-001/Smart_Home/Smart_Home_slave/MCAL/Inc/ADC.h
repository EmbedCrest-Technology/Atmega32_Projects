/*
 * ADC.h
 *
 * Created: 20/10/2024  11.11 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#ifndef ADC_H_
#define ADC_H_

#define REFERENCE_VOLTAGE 2.56     // Fixed: Proper naming convention
#define PRECISION         1024     // Fixed: Proper naming convention
#define ADC_RESOLUTION    (REFERENCE_VOLTAGE / PRECISION)  // Fixed: Matches main.c usage

void ADC_init(void);
unsigned int ADC_u16read(void);  // Fixed: Changed to unsigned int for consistency with main.c

#endif /* ADC_H_ */
