/*
 * KEYBAD.h
 *
 * Created: 1/12/2024 12:53:46 AM
 *  Author: Embedcrest Technology Private Limited
 */ 


#ifndef KEYBAD_H_
#define KEYBAD_H_

#define PORT_11 'C'
#define PORT_22 'D'
#define NOT_pressed 0xff

void KEYBAD_init(void);


char KEYBAD_check_press(void);


#endif /* KEYBAD_H_ */
