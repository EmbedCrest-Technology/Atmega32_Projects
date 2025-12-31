/*
 * LCD.c
 *
 * Created: 8/10/2024 2:01:49 A
 * Author: Embedcrest Technology Private Limited
 */

#ifndef LCD_H_
#define LCD_H_

#include "DIO.h"

#define four_bits_mode
#define LCD_DATA_PORT   'A'
#define LCD_CTRL_PORT   'B'

#define LCD_CLR_SCREEN          0x01
#define LCD_CURSOR_ON           0x0E
#define LCD_CURSOR_OFF          0x0C
#define LCD_RETURN_HOME         0x02
#define LCD_ENTRY_MODE          0x06

#if defined eight_bits_mode
#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2
#define LCD_8BIT_MODE 0x38

#elif defined four_bits_mode
#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2
#define LCD_4BIT_MODE 0x28
#endif

void LCD_init(void);
void LCD_send_cmd(char cmd);
void LCD_send_data(char data);
void LCD_send_string(char* str);
void LCD_clear(void);
void LCD_move_cursor(char row, char col);

#endif /* LCD_H_ */
