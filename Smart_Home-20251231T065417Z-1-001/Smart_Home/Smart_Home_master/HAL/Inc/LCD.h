/*
 * LCD.h
 *
 * Created: 21/10/2024  9.07 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#ifndef LCD_H_
#define LCD_H_

#define FOUR_BITS_MODE     // Fixed: Proper naming convention
#define PORT_1             PORTA   // Fixed: Char literal ? AVR port register
#define PORT_2             PORTA   // Fixed: Char literal ? AVR port register
#define CLR_SCREEN         0x01
#define CURSOR_ON_DISPLAY_ON 0x0E
#define CURSOR_OFF_DISPLAY_ON 0x0C  // Fixed: Consistent naming
#define RETURN_HOME        0x02
#define ENTRY_MODE         0x06

#if defined(EIGHT_BITS_MODE)
#define RS 0
#define RW 1
#define EN 2
#define EIGHT_BITS 0x38
#elif defined(FOUR_BITS_MODE)
#define RS 0
#define RW 1
#define EN 2
#define FOUR_BITS 0x28
#endif

void LCD_init(void);
void LCD_send_cmd(uint8_t cmd);           // Fixed: Standard AVR type
void LCD_send_data(uint8_t data);         // Fixed: Standard AVR type
void LCD_send_string(uint8_t* string);    // Fixed: Standard AVR type
void LCD_clr_screen(void);
void LCD_move_cursor(uint8_t row, uint8_t col);  // Fixed: Standard types, fixed typo

#endif /* LCD_H_ */
