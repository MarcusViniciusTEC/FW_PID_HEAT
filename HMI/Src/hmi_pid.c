
/******************************************************************************/

#include "hmi_pid_types.h"
#include "hmi_pid.h"
#include "LCD_HD44780.h"
#include "stdio.h"

/******************************************************************************/

static const hmi_pid_data_t hmi_pid_data[HMI_PID_NUMBER_OF_ITENS] = hmi_pid_vector_item_default;

/******************************************************************************/

void hmi_pid_show_visible_itens(void)
{
    vLCD_HD44780_Clear();
    for(uint8_t index  = 0; index < HMI_PID_NUMBER_OF_ITENS; index ++)
    {
        char sz_string[20] = {0};
        snprintf(sz_string, sizeof(sz_string), "%s %d", hmi_pid_data[index].str, hmi_pid_data[index].value );
        vLCD_HD44780_Puts(1, index, sz_string);
    }
}

/******************************************************************************/

void hmi_pid_init(void)
{

}

/******************************************************************************/

void hmi_pid_show_screen(void)
{
    hmi_pid_show_visible_itens();
}

/******************************************************************************/

void hmi_pid_update_data(void)
{

}

/******************************************************************************/

void hmi_pid_update_button(button_id_t button_id, button_press_type_t button_press_type)
{

}