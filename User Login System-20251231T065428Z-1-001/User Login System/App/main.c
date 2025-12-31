/*
 * user_login_system_refactored.c
 *
 * Created: 15/12/2024 2:20:56 AM
 * Author : Embedcrest Technology Private Limited
 */

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "I2C.h"
#include "UART.h"

// EEPROM Constants
#define EEPROM_INIT_VAL              0xFF
#define EEPROM_STATUS_ADDR           0x00
#define EEPROM_PASS_ADDR             0x21
#define EEPROM_NAME_ADDR             0x25

// Sizes
#define USERNAME_LEN 5
#define PASSWORD_LEN 4

// I2C EEPROM Device Address
#define EEPROM_DEV_ADDR 0b1010000

// ----------------------- Function Prototypes -----------------------
void eeprom_write_byte(uint8_t location, uint8_t data);
uint8_t eeprom_read_byte(uint8_t location);
void save_user_name(const char *name);
void save_user_password(const char *pass);
void read_user_name(char *name);
void read_user_password(char *pass);

// ------------------------------------------------------------------

int main(void)
{
	uint8_t index;
	char rxChar;
	char storedName[USERNAME_LEN];
	char inputName[USERNAME_LEN];
	char storedPass[PASSWORD_LEN];
	char inputPass[PASSWORD_LEN];

	LCD_init();
	UART_init(9600);
	I2C_master_init(50000);
	_delay_ms(300);

	// ----------------------- Check EEPROM Status -----------------------
	rxChar = eeprom_read_byte(EEPROM_STATUS_ADDR);

	if (rxChar == EEPROM_INIT_VAL)
	{
		// ----------------------- Create Username -----------------------
		LCD_send_string("   Create name");
		_delay_ms(1000);
		LCD_clr_screen();
		LCD_send_string("user name:");

		for (index = 0; index < USERNAME_LEN; index++)
		{
			LCD_move_cursor(1, 11 + index);
			rxChar = UART_receive_data();
			LCD_send_data(rxChar);
			inputName[index] = rxChar;
			eeprom_write_byte(EEPROM_NAME_ADDR + index, rxChar);
		}

		UART_receive_data(); // Consume ENTER
		_delay_ms(500);

		// ----------------------- Create Password -----------------------
		LCD_clr_screen();
		LCD_send_string("password:");

		for (index = 0; index < PASSWORD_LEN; index++)
		{
			rxChar = UART_receive_data();
			LCD_send_data(rxChar);
			_delay_ms(300);
			LCD_move_cursor(1, 10 + index);
			LCD_send_data('*');

			inputPass[index] = rxChar;
			eeprom_write_byte(EEPROM_PASS_ADDR + index, rxChar);
		}

		// Mark EEPROM initialized
		eeprom_write_byte(EEPROM_STATUS_ADDR, 0);
	}

	UART_receive_data(); // Consume ENTER
	_delay_ms(500);

	// ----------------------- USER LOGIN -----------------------
	LCD_clr_screen();
	LCD_send_string("user login ");
	_delay_ms(1000);
	LCD_clr_screen();
	LCD_send_string("user name:");

	for (index = 0; index < USERNAME_LEN; index++)
	{
		LCD_move_cursor(1, 11 + index);
		rxChar = UART_receive_data();
		LCD_send_data(rxChar);
		inputName[index] = rxChar;

		// fetch stored name
		storedName[index] = eeprom_read_byte(EEPROM_NAME_ADDR + index);
	}

	_delay_ms(500);

	// Compare Name
	for (index = 0; index < USERNAME_LEN; index++)
	{
		if (storedName[index] != inputName[index])
		{
			LCD_clr_screen();
			LCD_send_string("user not exist!");
			while (1);
		}
	}

	UART_receive_data(); // ENTER
	_delay_ms(500);

	// ----------------------- PASSWORD VALIDATION -----------------------
	LCD_clr_screen();
	LCD_send_string("password:");

	for (index = 0; index < PASSWORD_LEN; index++)
	{
		rxChar = UART_receive_data();
		LCD_send_data(rxChar);
		_delay_ms(300);
		LCD_move_cursor(1, 10 + index);
		LCD_send_data('*');

		inputPass[index] = rxChar;
		storedPass[index] = eeprom_read_byte(EEPROM_PASS_ADDR + index);
	}

	_delay_ms(500);

	// Compare Password
	for (index = 0; index < PASSWORD_LEN; index++)
	{
		if (storedPass[index] != inputPass[index])
		{
			LCD_clr_screen();
			LCD_send_string("Wrong Password!");
			while (1);
		}
	}

	UART_receive_data(); // ENTER

	// ----------------------- Login Success -----------------------
	LCD_clr_screen();
	LCD_send_string("Login Successful!");
	_delay_ms(1000);
	LCD_move_cursor(2, 1);
	LCD_send_string("press 1 to set");

	rxChar = UART_receive_data();

	if (rxChar == '1')
	{
		UART_receive_data(); // ENTER
		LCD_clr_screen();
		LCD_send_string("1-change pass");
		LCD_move_cursor(2, 1);
		LCD_send_string("2-change name");

		rxChar = UART_receive_data();

		// -------------------- Change Password --------------------
		if (rxChar == '1')
		{
			UART_receive_data();
			_delay_ms(500);
			LCD_clr_screen();
			LCD_send_string("password:");

			for (index = 0; index < PASSWORD_LEN; index++)
			{
				rxChar = UART_receive_data();
				LCD_send_data(rxChar);
				_delay_ms(300);
				LCD_move_cursor(1, 10 + index);
				LCD_send_data('*');

				eeprom_write_byte(EEPROM_PASS_ADDR + index, rxChar);
			}

			LCD_clr_screen();
			LCD_send_string("password changed");
			_delay_ms(1000);
			LCD_clr_screen();
			LCD_send_string("    welcome");
		}

		// -------------------- Change Username --------------------
		else if (rxChar == '2')
		{
			UART_receive_data();
			LCD_clr_screen();
			LCD_send_string("new name:");

			for (index = 0; index < USERNAME_LEN; index++)
			{
				LCD_move_cursor(1, 11 + index);
				rxChar = UART_receive_data();
				LCD_send_data(rxChar);

				eeprom_write_byte(EEPROM_NAME_ADDR + index, rxChar);
			}

			LCD_clr_screen();
			LCD_send_string("name changed");
			_delay_ms(1000);
			LCD_clr_screen();
			LCD_send_string("    welcome");
		}
	}
}


// ----------------------- EEPROM Helper Functions -----------------------

void eeprom_write_byte(uint8_t location, uint8_t data)
{
	I2C_start();
	I2C_master_send_address_transmitter_mode(EEPROM_DEV_ADDR);
	I2C_master_transmit_data(location);
	I2C_master_transmit_data(data);
	I2C_stop();
}

uint8_t eeprom_read_byte(uint8_t location)
{
	uint8_t value;
	I2C_start();
	I2C_master_send_address_transmitter_mode(EEPROM_DEV_ADDR);
	I2C_master_transmit_data(location);
	I2C_repeated_start();
	I2C_master_send_address_receiver_mode(EEPROM_DEV_ADDR);
	value = I2C_master_receive_data_with_not_ACK();
	I2C_stop();
	return value;
}
