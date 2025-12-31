/*
 * KEYBAD.c
 *
 * Created: 21/10/2014 9.07 AM
 *  Author: Embedcrest Technology Private Limited
 */

#include "KEYBAD.h"
#include "DIO.h"

void KEYBAD_init(void)
{
    // Rows as output (PC0-PC3)
    DIO_set_pin_dir(PORT_11, 0, 1);
    DIO_set_pin_dir(PORT_11, 1, 1);
    DIO_set_pin_dir(PORT_11, 2, 1);
    DIO_set_pin_dir(PORT_11, 3, 1);
    
    // Columns as input (PC4-PC7)
    DIO_set_pin_dir(PORT_22, 4, 0);
    DIO_set_pin_dir(PORT_22, 5, 0);
    DIO_set_pin_dir(PORT_22, 6, 0);
    DIO_set_pin_dir(PORT_22, 7, 0);
    DIO_connect_pull_up(PORT_22, 4, 1);
    DIO_connect_pull_up(PORT_22, 5, 1);
    DIO_connect_pull_up(PORT_22, 6, 1);
    DIO_connect_pull_up(PORT_22, 7, 1);
}

uint8_t KEYBAD_check_press(void)  // Fixed: Return type matches KEYBAD.h
{
    const uint8_t arr_out_val[4][4] = {
        {'7','8','9','/'},
        {'4','5','6','*'},
        {'1','2','3','-'},
        {'A','0','=','+'}
    };
    
    uint8_t ret_val = NOT_pressed;  // Fixed: Proper initialization
    uint8_t value, row, col;
    
    for (row = 0; row < 4; row++) {
        // Set all rows high first, then drive current row low
        DIO_write_pin(PORT_11, 0, 1);
        DIO_write_pin(PORT_11, 1, 1);
        DIO_write_pin(PORT_11, 2, 1);
        DIO_write_pin(PORT_11, 3, 1);
        DIO_write_pin(PORT_11, row, 0);  // Scan current row
        
        for (col = 0; col < 4; col++) {
            value = DIO_read_pin(PORT_22, (col + 4));
            if (value == 0) {
                ret_val = arr_out_val[row][col];
                return ret_val;  // Fixed: Early return on key press
            }
        }
    }
    return ret_val;
}
