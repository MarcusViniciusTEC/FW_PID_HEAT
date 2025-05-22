
#include "hmi_menu.h"
#include "LCD_HD44780.h"
#include "hmi_dashboard_types.h"
#include "stdio.h"

/******************************************************************************/

static void hmi_dashboard_show_datahour(void);
static void hmi_dashboard_show_setpoint(void);
static void hmi_dashboard_show_temperature(void);
static void hmi_dashboard_increment_setpoint(void);
static void hmi_dashboard_decrement_setpoint(void);
static void hmi_dashboard_increment_index(void);
static void hmi_dashboard_decrement_index(void);
static void hmi_dashboard_blnk_digit(uint8_t digit);

/******************************************************************************/

static hmi_edit_value_t hmi_edit_value;
static hmi_ctrl_t hmi_ctrl = {0};

/******************************************************************************/

void hmi_dashboard_init()
{
    hmi_edit_value.setpoint[INDEX_FIRST_DIGIT] = 2;
    hmi_edit_value.setpoint[INDEX_SECOND_DIGIT] = 9;
    hmi_edit_value.setpoint[INDEX_THIRD_DIGIT] = 3;

    hmi_ctrl.cursor_blnk_ms = 200;

}        

/******************************************************************************/

static void hmi_dashboard_blnk_digit(uint8_t digit)
{

}



static void hmi_dashboard_increment_setpoint(void)
{
    hmi_edit_value.setpoint[hmi_ctrl.index]++;

    if(hmi_edit_value.setpoint[hmi_ctrl.index] > MAX_DIGIT)
    {
        hmi_edit_value.setpoint[hmi_ctrl.index] = MIN_DIGIT;
        hmi_edit_value.setpoint[hmi_ctrl.index - 1] = hmi_edit_value.setpoint[hmi_ctrl.index - 1] + 1;
    }
    if(hmi_edit_value.setpoint[hmi_ctrl.index - 1] > MAX_DIGIT)
    {
        hmi_edit_value.setpoint[hmi_ctrl.index - 1] = MIN_DIGIT;
        hmi_edit_value.setpoint[hmi_ctrl.index - 2] = hmi_edit_value.setpoint[hmi_ctrl.index - 2] + 1;
    }
    
}

/******************************************************************************/

static void hmi_dashboard_decrement_setpoint(void)
{
    hmi_edit_value.setpoint[hmi_ctrl.index]--;
    if(hmi_edit_value.setpoint[hmi_ctrl.index] > MAX_DIGIT)
    {   
        hmi_edit_value.setpoint[hmi_ctrl.index] = MAX_DIGIT;
        hmi_edit_value.setpoint[hmi_ctrl.index - 1] = hmi_edit_value.setpoint[hmi_ctrl.index - 1] - 1;
    }
    if(hmi_edit_value.setpoint[hmi_ctrl.index - 1] > MAX_DIGIT)
    {
        hmi_edit_value.setpoint[hmi_ctrl.index - 1] = MAX_DIGIT;
        hmi_edit_value.setpoint[hmi_ctrl.index - 2] = hmi_edit_value.setpoint[hmi_ctrl.index - 2] - 1;
    }

}

/******************************************************************************/

static void hmi_dashboard_increment_index(void)
{
    hmi_ctrl.index ++;
    if(hmi_ctrl.index > 2)
    {
        hmi_ctrl.index = 2;
    }
}

/******************************************************************************/

static void hmi_dashboard_decrement_index(void)
{
    hmi_ctrl.index --;
    if(hmi_ctrl.index > 2)
    {
        hmi_ctrl.index = 0;
    }
}

/******************************************************************************/

static void hmi_dashboard_show_datahour(void)
{
    vLCD_HD44780_Puts(0, 3, "21/05/25");
    vLCD_HD44780_Puts(9, 3, "19:38");
}

/******************************************************************************/

static void hmi_dashboard_show_setpoint(void)
{
    char sz_string[20] = {0};
    snprintf(sz_string, sizeof(sz_string), "PV: %u%u.%u%s",
    hmi_edit_value.setpoint[INDEX_FIRST_DIGIT], 
    hmi_edit_value.setpoint[INDEX_SECOND_DIGIT],
    hmi_edit_value.setpoint[INDEX_THIRD_DIGIT], "'C");
    vLCD_HD44780_Puts(0, 0, sz_string);
}

/******************************************************************************/

static void hmi_dashboard_show_temperature(void)
{
    vLCD_HD44780_Puts(0, 1, "PV: 33.0'C");
}

/******************************************************************************/

void hmi_dashboard_show_screen()
{
    vLCD_HD44780_Clear();
    hmi_dashboard_show_datahour();
    hmi_dashboard_show_temperature();
    hmi_dashboard_show_setpoint();
}     

/******************************************************************************/

void hmi_dashboard_update_data()
{
    static uint32_t current_tick =0;
    static uint32_t last_tick = 0;

    current_tick = HAL_GetTick();

    if(current_tick - last_tick >= 500)
    {
        //vLCD_HD44780_Puts(5, 1, " ");
        last_tick = current_tick;
    }
   hmi_dashboard_show_setpoint();
}      

/******************************************************************************/

void hmi_dashboard_update_button(button_id_t button_id, button_press_type_t button_press_type)
{
    switch (button_id)
    {
    case BUTTON_UP_ID:
        hmi_dashboard_increment_setpoint();
        break;
    case BUTTON_DOWN_ID:
        hmi_dashboard_decrement_setpoint();
        break;
    case BUTTON_LEFT_ID:
        hmi_dashboard_decrement_index();
        break;
    case BUTTON_RIGHT_ID:
        hmi_dashboard_increment_index();
        break;
    default:
        break;
    }

    hmi_dashboard_show_setpoint();
}   