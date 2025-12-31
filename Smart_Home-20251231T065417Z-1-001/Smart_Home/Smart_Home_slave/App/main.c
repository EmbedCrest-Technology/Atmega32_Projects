/*
 * Smart_Home_slave.c
 *
 * Created: 20/10/2024  11.11AM
 * Author :Embedcrest Technology Private Limited
 */


#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADC.h"
#include "LED.h"
#include "MOTOR.h"
#include "EEPROM.h"
#include "SPI.h"
#include "main_config.h"

#define ADC_RESOLUTION 500  // Fixed: Added missing resolution definition

unsigned char led_R1, led_R2, led_R3, led_R4;
unsigned char fan_R1, fan_R2, fan_R3, fan_R4;
unsigned char tv, air_cond, door;
unsigned char volt;
unsigned int temp_value;  // Fixed: Changed from unsigned short to unsigned int

int main(void)
{
    // Initialize LEDs, fans, and other components
    LED_init(ROOM1_PORT, led1_PIN);
    LED_init(ROOM2_PORT, led2_PIN);
    LED_init(ROOM3_PORT, led3_PIN);
    LED_init(ROOM4_PORT, led4_PIN);
    LED_init(ROOM1_PORT, fan1_PIN);
    LED_init(ROOM2_PORT, fan2_PIN);
    LED_init(ROOM3_PORT, fan3_PIN);
    LED_init(ROOM4_PORT, fan4_PIN);
    LED_init(TV_PORT, TV_PIN);
    LED_init(AIR_COND_PORT, AIR_COND_PIN);
    ADC_init();
    SPI_slave_init();

    // Read initial states from EEPROM (fixed temperature read)
    led_R1 = EEPROM_read(ADDRESS_LED_1);
    led_R2 = EEPROM_read(ADDRESS_LED_2);
    led_R3 = EEPROM_read(ADDRESS_LED_3);
    led_R4 = EEPROM_read(ADDRESS_LED_4);
    fan_R1 = EEPROM_read(ADDRESS_FAN_1);
    fan_R2 = EEPROM_read(ADDRESS_FAN_2);
    fan_R3 = EEPROM_read(ADDRESS_FAN_3);
    fan_R4 = EEPROM_read(ADDRESS_FAN_4);
    door = EEPROM_read(ADDRESS_DOOR);
    tv = EEPROM_read(ADDRESS_TV);
    air_cond = EEPROM_read(ADDRESS_AIR_COND);
    temp_value = EEPROM_read(ADDRESS_TEMP) | (EEPROM_read(ADDRESS_TEMP+1) << 8);

    // Transmit initial states via SPI (send low byte only)
    SPI_slave_receive_and_transmit_data(led_R1);
    SPI_slave_receive_and_transmit_data(led_R2);
    SPI_slave_receive_and_transmit_data(led_R3);
    SPI_slave_receive_and_transmit_data(led_R4);
    SPI_slave_receive_and_transmit_data(fan_R1);
    SPI_slave_receive_and_transmit_data(fan_R2);
    SPI_slave_receive_and_transmit_data(fan_R3);
    SPI_slave_receive_and_transmit_data(fan_R4);
    SPI_slave_receive_and_transmit_data(door);
    SPI_slave_receive_and_transmit_data(tv);
    SPI_slave_receive_and_transmit_data(air_cond);
    SPI_slave_receive_and_transmit_data((unsigned char)temp_value);

    unsigned char object, device, status;
    while (1)
    {
        // Receive and process commands from SPI master
        object = SPI_slave_receive_and_transmit_data(DUMMY_DATA);
        switch (object)
        {
            case ROOM1_MENU:
            {
                device = SPI_slave_receive_and_transmit_data(DUMMY_DATA);
                status = SPI_slave_receive_and_transmit_data(DUMMY_DATA);
                if (device == LED)
                {
                    if (status == ON_STATUS) { LED_turn_on(ROOM1_PORT, led1_PIN); led_R1 = ON; }
                    else { LED_turn_off(ROOM1_PORT, led1_PIN); led_R1 = OFF; }
                    EEPROM_write(ADDRESS_LED_1, led_R1);
                }
                else if (device == FAN)
                {
                    if (status == ON_STATUS) { LED_turn_on(ROOM1_PORT, fan1_PIN); fan_R1 = ON; }
                    else { LED_turn_off(ROOM1_PORT, fan1_PIN); fan_R1 = OFF; }
                    EEPROM_write(ADDRESS_FAN_1, fan_R1);
                }
                break;
            }
            case ROOM2_MENU:
            {
                device = SPI_slave_receive_and_transmit_data(DUMMY_DATA);
                status = SPI_slave_receive_and_transmit_data(DUMMY_DATA);
                if (device == LED)
                {
                    if (status == ON_STATUS) { LED_turn_on(ROOM2_PORT, led2_PIN); led_R2 = ON; }
                    else { LED_turn_off(ROOM2_PORT, led2_PIN); led_R2 = OFF; }
                    EEPROM_write(ADDRESS_LED_2, led_R2);
                }
                else if (device == FAN)
                {
                    if (status == ON_STATUS) { LED_turn_on(ROOM2_PORT, fan2_PIN); fan_R2 = ON; }
                    else { LED_turn_off(ROOM2_PORT, fan2_PIN); fan_R2 = OFF; }
                    EEPROM_write(ADDRESS_FAN_2, fan_R2);
                }
                break;
            }
            case ROOM3_MENU:
            {
                device = SPI_slave_receive_and_transmit_data(DUMMY_DATA);
                status = SPI_slave_receive_and_transmit_data(DUMMY_DATA);
                if (device == LED)
                {
                    if (status == ON_STATUS) { LED_turn_on(ROOM3_PORT, led3_PIN); led_R3 = ON; }
                    else { LED_turn_off(ROOM3_PORT, led3_PIN); led_R3 = OFF; }
                    EEPROM_write(ADDRESS_LED_3, led_R3);
                }
                else if (device == FAN)
                {
                    if (status == ON_STATUS) { LED_turn_on(ROOM3_PORT, fan3_PIN); fan_R3 = ON; }
                    else { LED_turn_off(ROOM3_PORT, fan3_PIN); fan_R3 = OFF; }
                    EEPROM_write(ADDRESS_FAN_3, fan_R3);
                }
                break;
            }
            case ROOM4_MENU:
            {
                device = SPI_slave_receive_and_transmit_data(DUMMY_DATA);
                status = SPI_slave_receive_and_transmit_data(DUMMY_DATA);
                if (device == LED)
                {
                    if (status == ON_STATUS) { LED_turn_on(ROOM4_PORT, led4_PIN); led_R4 = ON; }
                    else { LED_turn_off(ROOM4_PORT, led4_PIN); led_R4 = OFF; }
                    EEPROM_write(ADDRESS_LED_4, led_R4);
                }
                else if (device == FAN)
                {
                    if (status == ON_STATUS) { LED_turn_on(ROOM4_PORT, fan4_PIN); fan_R4 = ON; }
                    else { LED_turn_off(ROOM4_PORT, fan4_PIN); fan_R4 = OFF; }
                    EEPROM_write(ADDRESS_FAN_4, fan_R4);
                }
                break;
            }
            case HOME_DOOR_MENU:
            {
                status = SPI_slave_receive_and_transmit_data(DUMMY_DATA);
                if (status == ON_STATUS) { Servo_motor_with_TIMER1_fast_pwm_ICRA_wave(90); door = ON; }
                else { Servo_motor_with_TIMER1_fast_pwm_ICRA_wave(0); door = OFF; }
                EEPROM_write(ADDRESS_DOOR, door);
                break;
            }
            case AIRCONDITIONING_MENU:
            {
                status = SPI_slave_receive_and_transmit_data(DUMMY_DATA);
                if (status == ON_STATUS) air_cond = ON;
                else air_cond = OFF;
                EEPROM_write(ADDRESS_AIR_COND, air_cond);
                break;
            }
            case TV_MENU:
            {
                status = SPI_slave_receive_and_transmit_data(DUMMY_DATA);
                if (status == ON_STATUS) { LED_turn_on(TV_PORT, TV_PIN); tv = ON; }
                else { LED_turn_off(TV_PORT, TV_PIN); tv = OFF; }
                EEPROM_write(ADDRESS_TV, tv);
                break;
            }
            case TEMP_MENU:
            {
                SPI_slave_receive_and_transmit_data((unsigned char)temp_value);
                break;
            }
            default: break;
        }

        // Update all outputs based on states (removed redundant code)
        LED_turn_on_off(ROOM1_PORT, led1_PIN, led_R1);
        LED_turn_on_off(ROOM2_PORT, led2_PIN, led_R2);
        LED_turn_on_off(ROOM3_PORT, led3_PIN, led_R3);
        LED_turn_on_off(ROOM4_PORT, led4_PIN, led_R4);
        LED_turn_on_off(ROOM1_PORT, fan1_PIN, fan_R1);
        LED_turn_on_off(ROOM2_PORT, fan2_PIN, fan_R2);
        LED_turn_on_off(ROOM3_PORT, fan3_PIN, fan_R3);
        LED_turn_on_off(ROOM4_PORT, fan4_PIN, fan_R4);
        LED_turn_on_off(TV_PORT, TV_PIN, tv);
        if (door == ON) Servo_motor_with_TIMER1_fast_pwm_ICRA_wave(90);
        else Servo_motor_with_TIMER1_fast_pwm_ICRA_wave(0);

        // Read ADC and update temperature (fixed type casting)
        unsigned int adc_raw = ADC_u16read();
        volt = (unsigned char)(adc_raw >> 8);
        temp_value = (ADC_RESOLUTION * volt * 1000) / 10;
        EEPROM_write(ADDRESS_TEMP, (unsigned char)temp_value);
        EEPROM_write(ADDRESS_TEMP+1, (unsigned char)(temp_value >> 8));

        // Auto control AC based on temperature
        if (air_cond == ON && temp_value >= 24) LED_turn_on(AIR_COND_PORT, AIR_COND_PIN);
        else LED_turn_off(AIR_COND_PORT, AIR_COND_PIN);
    }
}

// Helper function (add to LED.h if not exists)
void LED_turn_on_off(char port, uint8_t pin, uint8_t state) {
    if (state == ON) LED_turn_on(port, pin);
    else LED_turn_off(port, pin);
}
