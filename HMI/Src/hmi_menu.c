
#include "hmi_menu.h"
#include "hmi_menu_types.h"
#include "hmi.h"

/***********************************************************************************/

#include "LCD_HD44780.h"

static const hmi_menu_data_t hmi_menu_data[HMI_NUMBER_ID_OF_MENU_ITEM] = hmi_menu_vector_item_default;
static hmi_menu_ctrl_t hmi_menu_ctrl = {0};

/***********************************************************************************/

void hmi_menu_show_cursor(void);

static void hmi_menu_increment_item_index(void)
{
    
    hmi_menu_ctrl.item_index++;
    if(hmi_menu_ctrl.item_index > HMI_MENU_ID_SETTINGS)
    {
        hmi_menu_ctrl.item_index = HMI_MENU_ID_SETTINGS;
    }
}

/***********************************************************************************/

static void hmi_menu_decrement_item_index(void)
{
    hmi_menu_ctrl.item_index--;
    if(hmi_menu_ctrl.item_index > HMI_MENU_ID_SETTINGS)
    {
        hmi_menu_ctrl.item_index = HMI_MENU_ID_PID;
    }
}

/***********************************************************************************/

void hmi_menu_show_visible_string(void)
{
    for(uint8_t index  = 0; index < HMI_NUMBER_ID_OF_MENU_ITEM; index ++)
    {
        vLCD_HD44780_Puts(2, index, hmi_menu_data[index].str);
    }
}

/***********************************************************************************/

void hmi_menu_show_visible_itens(void)
{
    vLCD_HD44780_Clear();
    hmi_menu_show_visible_string();
    hmi_menu_show_cursor();   
}

/***********************************************************************************/

void hmi_menu_show_cursor(void)
{
   vLCD_HD44780_Puts(0, hmi_menu_ctrl.item_index, CURSOR_SYMBOL); 
}

/***********************************************************************************/

void hmi_menu_init(void)
{

}

/***********************************************************************************/

void hmi_menu_show_screen(void)
{
    hmi_menu_show_visible_itens();
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
        hmi_menu_increment_item_index();
        break;
    case BUTTON_DOWN_ID:
        hmi_menu_decrement_item_index();
        break;
    case BUTTON_LEFT_ID:
        break;
    case BUTTON_RIGHT_ID:
        switch (hmi_menu_ctrl.item_index)
        {
        case HMI_MENU_ID_PID:
            hmi_set_screen(HMI_ID_SCREEN_PID);
            break;
        case HMI_MENU_ID_DASHBOARD:
            hmi_set_screen(HMI_ID_SCREEN_DASHBOARD);
            break;
        case HMI_MENU_ID_SETTINGS:
            hmi_set_screen(HMI_ID_SCREEN_MENU);
            break;

        default:
            break;
        }
        break;
    default:
        break;
    }

    hmi_menu_show_visible_itens();
}