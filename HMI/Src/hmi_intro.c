#include "hmi_intro.h"
#include "hmi.h"
#include "hmi_types.h"


void hmi_intro_init(void)
{

}
void hmi_intro_show_screen(void)
{
    vLCD_HD44780_Clear();
    vLCD_HD44780_Puts(0, 1, "ABL Solutions");
    HAL_Delay(2000);
    hmi_set_screen(HMI_ID_SCREEN_DASHBOARD);
}

void hmi_intro_update_data(void)
{

}

void hmi_intro_update_button(button_id_t button_id, button_press_type_t button_press_type)
{

}