/*
 * KEYBAD.c
 *
 * Created: 16/12/2024 12:53:16 AM
 *  Author: Embedcrest Technology Private Limited
 */

#include "KEYBAD.h"


void KEYBAD_init_pull_up(void)
{
    DIO_set_pin_dir(PORT_11,0,1);
    DIO_set_pin_dir(PORT_11,1,1);
    DIO_set_pin_dir(PORT_11,2,1);
    DIO_set_pin_dir(PORT_11,3,1);

    DIO_set_pin_dir(PORT_22,4,0);
    DIO_set_pin_dir(PORT_22,5,0);
    DIO_set_pin_dir(PORT_22,6,0);
    DIO_set_pin_dir(PORT_22,7,0);

    DIO_connect_pull_up(PORT_22,4,1);
    DIO_connect_pull_up(PORT_22,5,1);
    DIO_connect_pull_up(PORT_22,6,1);
    DIO_connect_pull_up(PORT_22,7,1);
}

void KEYBAD_init(void)
{
    DIO_set_pin_dir(PORT_11,0,1);
    DIO_set_pin_dir(PORT_11,1,1);
    DIO_set_pin_dir(PORT_11,2,1);
    DIO_set_pin_dir(PORT_11,3,1);

    DIO_set_pin_dir(PORT_22,4,0);
    DIO_set_pin_dir(PORT_22,5,0);
    DIO_set_pin_dir(PORT_22,6,0);
    DIO_set_pin_dir(PORT_22,7,0);
}

char KEYBAD_check_press(void)
{
    char arr_out_val[4][4] =
    {
        {'7','8','9','/'},
        {'4','5','6','*'},
        {'1','2','3','-'},
        {'A','0','=','+'}
    };

    char key_pressed = 0xFF;      // renamed from ret_val
    char key_value;               // renamed from value
    char row_index, col_index;    // renamed from row and coloum

    for(row_index = 0; row_index < 4; row_index++)
    {
        // set all rows HIGH
        DIO_write_pin(PORT_11,0,1);
        DIO_write_pin(PORT_11,1,1);
        DIO_write_pin(PORT_11,2,1);
        DIO_write_pin(PORT_11,3,1);

        // activate one row at a time
        DIO_write_pin(PORT_11, row_index, 0);

        for(col_index = 0; col_index < 4; col_index++)
        {
            key_value = DIO_read_pin(PORT_22, (col_index + 4));

            if(key_value == 0)
            {
                key_pressed = arr_out_val[row_index][col_index];
                break;
            }
        }

        if(key_value == 0)
        {
            break; // key found → exit loop
        }
    }
    return key_pressed;
}
