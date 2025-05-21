
#include "hmi_menu.h"
#include "hmi_menu_types.h"

/***********************************************************************************/

#include "LCD_HD44780.h"

/***********************************************************************************/

void hmi_menu_init(void)
{

}

/***********************************************************************************/

void hmi_menu_show_screen(void)
{

    
}

/***********************************************************************************/

void hmi_menu_update_data(void)
{

}

/***********************************************************************************/

void hmi_menu_update_button(button_id_t button_id, button_press_type_t button_press_type)
{
    switch (button_id)
    {
    case BUTTON_UP_ID:
        uint8_t teste = 0;
        teste++;
        break;
    case BUTTON_DOWN_ID:
        /* code */
        break;
    case BUTTON_LEFT_ID:
        /* code */
        break;
    case BUTTON_RIGHT_ID:
        /* code */
        break;
    default:
        break;
    }
}