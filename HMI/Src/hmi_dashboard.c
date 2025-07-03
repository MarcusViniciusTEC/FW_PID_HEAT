
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
static void hmi_dashboard_hide_digit(void);
static void hmi_dashboard_blnk_cursor(void);
void hmi_dashboard_1ms(void);
uint16_t hmi_dashboard_get_setpoint(void);

/******************************************************************************/

static hmi_edit_value_t hmi_edit_value;
static hmi_dahsboard_ctrl_t hmi_dahsboard_ctrl = {0};

/******************************************************************************/

void hmi_dashboard_init()
{
    hmi_edit_value.setpoint[INDEX_FIRST_DIGIT] = 2;
    hmi_edit_value.setpoint[INDEX_SECOND_DIGIT] = 9;
    hmi_edit_value.setpoint[INDEX_THIRD_DIGIT] = 3;

    hmi_dahsboard_ctrl .cursor_state = CURSOR_BLINK_ON;

}        

/******************************************************************************/

uint16_t hmi_dashboard_get_setpoint(void)
{
    uint16_t value = 0;

    value += hmi_edit_value.setpoint[INDEX_FIRST_DIGIT] * 100;
    value += hmi_edit_value.setpoint[INDEX_SECOND_DIGIT] * 10;
    value += hmi_edit_value.setpoint[INDEX_THIRD_DIGIT];

    return value;
}

/******************************************************************************/

static void hmi_dashboard_hide_digit(void)
{
    switch ((hmi_index_digits_t)hmi_dahsboard_ctrl .index)
    {
    case INDEX_FIRST_DIGIT:
        vLCD_HD44780_Puts(4, 0, " ");
        break;
    case INDEX_SECOND_DIGIT:
        vLCD_HD44780_Puts(5, 0, " ");
        break;
    case INDEX_THIRD_DIGIT:
        vLCD_HD44780_Puts(7, 0, " ");
        break;
    default:
        break;
    }
}

/******************************************************************************/

static void hmi_dashboard_increment_setpoint(void)
{
    hmi_edit_value.setpoint[hmi_dahsboard_ctrl.index]++;

    if(hmi_edit_value.setpoint[hmi_dahsboard_ctrl.index] > MAX_DIGIT)
    {
        hmi_edit_value.setpoint[hmi_dahsboard_ctrl.index] = MIN_DIGIT;
        hmi_edit_value.setpoint[hmi_dahsboard_ctrl.index - 1] = hmi_edit_value.setpoint[hmi_dahsboard_ctrl.index - 1] + 1;
    }
    if(hmi_edit_value.setpoint[hmi_dahsboard_ctrl.index - 1] > MAX_DIGIT)
    {
        hmi_edit_value.setpoint[hmi_dahsboard_ctrl.index - 1] = MIN_DIGIT;
        hmi_edit_value.setpoint[hmi_dahsboard_ctrl.index - 2] = hmi_edit_value.setpoint[hmi_dahsboard_ctrl.index - 2] + 1;
    }
    
}

/******************************************************************************/

static void hmi_dashboard_decrement_setpoint(void)
{
    hmi_edit_value.setpoint[hmi_dahsboard_ctrl.index]--;
    if(hmi_edit_value.setpoint[hmi_dahsboard_ctrl.index] > MAX_DIGIT)
    {   
        hmi_edit_value.setpoint[hmi_dahsboard_ctrl .index] = MAX_DIGIT;
        hmi_edit_value.setpoint[hmi_dahsboard_ctrl .index - 1] = hmi_edit_value.setpoint[hmi_dahsboard_ctrl .index - 1] - 1;
    }
    if(hmi_edit_value.setpoint[hmi_dahsboard_ctrl .index - 1] > MAX_DIGIT)
    {
        hmi_edit_value.setpoint[hmi_dahsboard_ctrl.index - 1] = MAX_DIGIT;
        hmi_edit_value.setpoint[hmi_dahsboard_ctrl.index - 2] = hmi_edit_value.setpoint[hmi_dahsboard_ctrl.index - 2] - 1;
    }

}

/******************************************************************************/

static void hmi_dashboard_increment_index(void)
{
    hmi_dahsboard_ctrl.index ++;
    if(hmi_dahsboard_ctrl.index > 2)
    {
        hmi_dahsboard_ctrl.index = 2;
    }
}

/******************************************************************************/

static void hmi_dashboard_decrement_index(void)
{
    hmi_dahsboard_ctrl.index --;
    if(hmi_dahsboard_ctrl.index > 2)
    {
        hmi_dahsboard_ctrl.index = 0;
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
    
    //HAL_GPIO_WritePin(PWM_FAN_GPIO_Port, PWM_FAN_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(RELE_LAMP_GPIO_Port, RELE_LAMP_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LAMP_ENABLE_GPIO_Port, LAMP_ENABLE_Pin, GPIO_PIN_SET);
}     

/******************************************************************************/

void hmi_dashboard_1ms(void)
{

}

/******************************************************************************/

static void hmi_dashboard_blnk_cursor(void)
{
    switch (hmi_dahsboard_ctrl.cursor_blnk_state)
    {
    case CURSOR_STATE_IDLE:
        hmi_dahsboard_ctrl.cursor_blnk_state = CURSOR_STATE_SHOW_NUMBER;
        break;
    case CURSOR_STATE_SHOW_NUMBER:
        hmi_dashboard_show_setpoint();  
        hmi_dahsboard_ctrl.last_time_show_cursor = HAL_GetTick();
        hmi_dahsboard_ctrl.cursor_blnk_state = CURSOR_STATE_WAIT_SHOW_DELAY;
        break;
    case CURSOR_STATE_WAIT_SHOW_DELAY:
        if(HAL_GetTick() - hmi_dahsboard_ctrl.last_time_show_cursor >= 300)
        {
            
            hmi_dahsboard_ctrl.cursor_blnk_state = CURSOR_STATE_HIDE_NUMBER;
            
        }
        break;
    case CURSOR_STATE_HIDE_NUMBER:
        hmi_dashboard_hide_digit();
        hmi_dahsboard_ctrl.last_time_hide_cursor = HAL_GetTick();
        hmi_dahsboard_ctrl.cursor_blnk_state = CURSOR_STATE_WAIT_HIDE_DELAY;
        break;
    case CURSOR_STATE_WAIT_HIDE_DELAY:
        if(HAL_GetTick() - hmi_dahsboard_ctrl.last_time_hide_cursor >= 30)
        {
            hmi_dahsboard_ctrl.cursor_blnk_state = CURSOR_STATE_IDLE;
        }
        break;
    default:
        break;
    }
}

/******************************************************************************/

void hmi_dashboard_update_data()
{
    switch (hmi_dahsboard_ctrl.cursor_state)
    {
    case CURSOR_BLINK_ON:
        hmi_dashboard_blnk_cursor();
        if(HAL_GetTick() - hmi_dahsboard_ctrl.last_time_blnk_cursor >= TIME_BLINK_CURSOR)
        {
            hmi_dahsboard_ctrl.cursor_state = CURSOR_BLINK_OFF;
            hmi_dashboard_show_setpoint();   
        }
        break;
    case CURSOR_BLINK_OFF:
        hmi_dahsboard_ctrl.last_time_blnk_cursor = HAL_GetTick();
        break;
    default:
        break;
    }
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
    hmi_dahsboard_ctrl.cursor_state = CURSOR_BLINK_ON;
}   