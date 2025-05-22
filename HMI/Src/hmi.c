
#include "hmi.h"
#include "hmi_types.h"
#include "stdint.h"

#include "LCD_HD44780.h"
#include "buttons.h"

volatile uint32_t hmi_execution_rate_1ms_timer;

hmi_screen_info_t hmi_vector_screens[HMI_NUMBER_OF_SCREENS] = vector_hmi_screens_default;
hmi_ctrl_t hmi_ctrl = {0};
button_data_t buttons_data_vector[NUMBER_OF_BUTTONS] = vector_buttons_data_default;

//====================================================================================================//

hmi_screens_id_t hmi_get_screen(void)
{
    return hmi_ctrl.screen_id;
}

/***********************************************************************************/

void hmi_set_screen(hmi_screens_id_t hmi_screens_id)
{
    hmi_ctrl.next_screen_id = hmi_screens_id;
}

/***********************************************************************************/

static void hmi_showing_screen(void)
{
    hmi_vector_screens[hmi_ctrl.screen_id].show_screen();
}

/***********************************************************************************/

static void hmi_showing_data(void)
{
    hmi_vector_screens[hmi_ctrl.screen_id].show_data();
}

/***********************************************************************************/

void hmi_showing_update_data(button_id_t button_id, button_press_type_t button_press_type)
{
    hmi_vector_screens[hmi_ctrl.screen_id].update_data_buttons(button_id,  button_press_type);
}

/***********************************************************************************/

static void hmi_buttons_update_state(void)
{
    for(uint8_t index_buttons = 0; index_buttons < NUMBER_OF_BUTTONS; index_buttons++)
    {
        read_buttons_state(&buttons_data_vector[index_buttons]);    
    }
}

/***********************************************************************************/

void hmi_1ms_clock(void)
{

}

//====================================================================================================//
void hmi_init(void)
{
    
    for(hmi_ctrl.screen_id = 0; hmi_ctrl.screen_id < HMI_NUMBER_OF_SCREENS; hmi_ctrl.screen_id++)
    {
        hmi_vector_screens[hmi_ctrl.screen_id].init();
    }
    
    hmi_ctrl.screen_id = HMI_ID_SCREEN_INTRO;
    hmi_ctrl.next_screen_id = hmi_ctrl.screen_id;
}


//====================================================================================================//

void hmi_update(void)
{
    if (hmi_ctrl.screen_id != hmi_ctrl.next_screen_id)
    {
        hmi_ctrl.last_screen_id = hmi_ctrl.screen_id;
        hmi_ctrl.screen_id = hmi_ctrl.next_screen_id;
        hmi_ctrl.state = HMI_SHOWING_SCREEN;
    }
    switch (hmi_ctrl.state)
    {
    case HMI_SHOWING_SCREEN:
        hmi_showing_screen();
        hmi_ctrl.state = HMI_SHOWING_DATA;
        break;
    case HMI_SHOWING_DATA:
        hmi_showing_data();
        hmi_ctrl.state = HMI_SHOWING_UPDATE_DATA;
        break;
    case HMI_SHOWING_UPDATE_DATA:
        hmi_buttons_update_state();
        hmi_ctrl.state = HMI_SHOWING_DATA;
        break;
    default:
        break;
    }
}

//====================================================================================================//
void hmi_deinit(void)
{

}