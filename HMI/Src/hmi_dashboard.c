

#include "hmi_menu.h"
#include "LCD_HD44780.h"

void hmi_dashboard_init()
{

}            
void hmi_dashboard_show_screen()
{
    vLCD_HD44780_Clear();
    vLCD_HD44780_Puts(5, 0, "dashboard");
}     


void hmi_dashboard_update_data()
{

}      

void hmi_dashboard_update_button(button_id_t button_id, button_press_type_t button_press_type)
{
    static uint8_t teste = 0;
    switch (button_id)
    {
    case BUTTON_UP_ID:
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

    char szString[20] = { 0 };
    sprintf(szString, "%d", teste);
    vLCD_HD44780_Puts(13, 1, szString);
}   