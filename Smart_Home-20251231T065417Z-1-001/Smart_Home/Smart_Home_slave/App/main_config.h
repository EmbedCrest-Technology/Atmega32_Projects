/*
 * main_config.h
 *
 * Created: 20/10/2024   11.11 AM
 *  Author: Embedcrest Technology Private Limited
 */ 

#ifndef MAIN_CONFIG_H_
#define MAIN_CONFIG_H_

#define DUMMY_DATA      0xFF      // Fixed: Added space
#define ASCII_ZERO      '0'       // Fixed: Added space

#define ADDRESS_LED_1   0x21      // Fixed: Added spaces and 0x
#define ADDRESS_LED_2   0x22
#define ADDRESS_LED_3   0x23
#define ADDRESS_LED_4   0x24
#define ADDRESS_FAN_1   0x25
#define ADDRESS_FAN_2   0x26
#define ADDRESS_FAN_3   0x27
#define ADDRESS_FAN_4   0x28
#define ADDRESS_DOOR    0x29      // Fixed: Added space
#define ADDRESS_TV      0x30      // Fixed: Added space
#define ADDRESS_AIR_COND 0x31    // Fixed: Added space
#define ADDRESS_TEMP    0x32

#define ROOM1_MENU      '1'
#define ROOM2_MENU      '2'
#define ROOM3_MENU      '3'
#define ROOM4_MENU      '4'
#define HOME_DOOR_MENU  '5'
#define TV_MENU         '6'
#define AIRCONDITIONING_MENU '7'
#define TEMP_MENU       '9' 
#define LED             '1'       // Fixed: Added space
#define FAN             '2'       // Fixed: Added space  
#define ON_STATUS       '1'
#define OFF_STATUS      '2'
#define ON              1
#define OFF             0

#define AIR_COND_PIN    7         // Fixed: Added space
#define TV_PIN          6         // Fixed: Added space
#define led1_PIN        0         // Fixed: Added space
#define led2_PIN        1
#define led3_PIN        2
#define led4_PIN        3
#define fan1_PIN        4
#define fan2_PIN        5
#define fan3_PIN        6
#define fan4_PIN        7

#define AIR_COND_PORT   PORTD     // Fixed: 'D' -> PORTD
#define TV_PORT         PORTD     // Fixed: 'D' -> PORTD
#define DOOR_PORT       PORTD     // Fixed: 'D' -> PORTD
#define ROOM1_PORT      PORTC     // Fixed: 'C' -> PORTC
#define ROOM2_PORT      PORTC
#define ROOM3_PORT      PORTC
#define ROOM4_PORT      PORTC

#endif /* MAIN_CONFIG_H_ */
