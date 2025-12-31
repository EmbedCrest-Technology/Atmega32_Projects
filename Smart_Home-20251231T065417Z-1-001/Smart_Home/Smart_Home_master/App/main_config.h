/*
 * main_config.h
 *
 * Created: 21/10/2024  9.17 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#ifndef MAIN_CONFIG_H_
#define MAIN_CONFIG_H_

#define DUMMY_DATA      0xFF      // Fixed: Proper hex format
#define TIME_MAX        600

#define TRUE            1         // Fixed: Standard boolean (was inverted)
#define FALSE           0
#define PASS_SIZE       4
#define TRIES_ALLOWED   3
#define ADDRESS_TRIES   0x20
#define ADDRESS_TRIES_count 0x21
#define TIME_CLOSED     59
#define PASSWORD_SYMBOL '*'
#define ASCII_ZERO      '0'       // Fixed: Added space

#define PASS_NOT_SET    0xFF
#define PASS_SET        0x01

#define ADMIN_PASS_STATUS_ADDRESS 0x101
#define EEPROM_ADMIN_ADDRESS      0x102

#define ADMIN           '1'
#define GUEST           '2'
#define ADMIN_PORT      PORTB     // Fixed: Char literal ? AVR port register
#define GUEST_PORT      PORTB     // Fixed: Char literal ? AVR port register
#define ADMIN_PIN       0
#define GUEST_PIN       1

#define MORE_MENU            'A'
#define ROOM1_MENU           '1'
#define ROOM2_MENU           '2'
#define ROOM3_MENU           '3'
#define ROOM4_MENU           '4'
#define HOME_DOOR            '5'   // Fixed: Consistent naming
#define TV_MENU              '6'
#define AIRCONDITIONING_MENU '7'
#define CHANGE_PASS          '8'
#define TEMP_MENU            '9'
#define LED                  '1'   // Fixed: Added space after #define
#define FAN                  '2'   // Fixed: Added space after #define
#define ON                   1
#define OFF                  0  
#define ON_STATUS            '1'
#define OFF_STATUS           '2'
#define RET_STATUS           '0'

#endif /* MAIN_CONFIG_H_ */
