/*
 * KEYPAD.c
 *
 * Created: 8/10/2024 12:53:46 AM
 * Author: Embedcrest Technology Private Limited
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "DIO.h"

#define KEYPAD_PORT_OUT   'C'
#define KEYPAD_PORT_IN    'C'
#define KEY_NOT_PRESSED   0xFF

void KEYPAD_init(void);
char KEYPAD_get_key(void);

#endif /* KEYPAD_H_ */
