

#include "app.h"
#include "stdio.h"
#include "adc.h"
#include "math.h"
#include "LCD_HD44780.h"

#include "hmi_dashboard.h"
#include "adc.h"

#include "main.h"
#include "stm32f1xx_hal_tim.h"

extern TIM_HandleTypeDef htim3;

volatile uint32_t app_execution_rate_1ms_timer;

extern uint16_t adc_buffer[ADC_NUMBER_OF_CHANNELS];

uint16_t app_get_temperature(void);


/***********************************************************************************/

app_heat_state_t get_app_heat_state(void);
static void app_calc_temperature(void);

/***********************************************************************************/


static app_temp_t app_temp = {0};
static app_temp_ctrl_t app_temp_ctrl = {0};

/***********************************************************************************/

float adc_to_resistance(uint16_t adc_val)
{
    if (adc_val <= 750)
        return 110.0;
    if (adc_val <= 1530)
        return 110.0 + ((adc_val - 750) * (120.0 - 110.0)) / (1530 - 750);
    if (adc_val <= 2131)
        return 120.0 + ((adc_val - 1530) * (130.0 - 120.0)) / (2131 - 1530);
    return 130.0;  
}

/***********************************************************************************/

float resistance_to_temperature(float R)
{
    float disc = A*A - 4*B*(1 - (R / R0));
    if (disc < 0) return -999.0;  
    return (-A + sqrtf(disc)) / (2*B);
}

/***********************************************************************************/

static void app_read_button_heat_state(void)
{
    if(HAL_GPIO_ReadPin(BT_HEAT_ON_GPIO_Port, BT_HEAT_ON_Pin) == GPIO_PIN_RESET)
    {
        app_temp_ctrl.heat_state = HEAT_ON;
    }
    if(HAL_GPIO_ReadPin(BT_HEAT_OFF_GPIO_Port, BT_HEAT_OFF_Pin) == GPIO_PIN_SET)
    {
        app_temp_ctrl.heat_state = HEAT_OFF;
    }

}

/***********************************************************************************/


static void app_set_heat_state(void)
{
    switch (app_temp_ctrl.heat_state)
    {
    case HEAT_ON:
        LED_HEAT_ON();
        RELAY_ENABLE_HEATING();
        break;
    case HEAT_OFF:
        LED_HEAT_OFF();
        RELAY_DISABLE_HEATING();
        break;
    default:
        break;
    }
}

/***********************************************************************************/

app_heat_state_t app_get_heat_state(void)
{
    return app_temp_ctrl.heat_state;
}

/***********************************************************************************/


void app_1ms_clock(void)
{

}

/***********************************************************************************/

static void app_set_fan_porcentage(uint8_t porcentage)
{
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, (uint16_t)((porcentage * 999)/100));
}

/***********************************************************************************/

static void app_led_mcu_status(void)
{
    static uint32_t last_blink = 0;
    if(HAL_GetTick() - last_blink >= 1000)
    {
        HAL_GPIO_TogglePin(LED_STATUS_1_GPIO_Port, LED_STATUS_1_Pin);
        last_blink = HAL_GetTick();
    }
}

/***********************************************************************************/

uint16_t float_to_int(float value_f)
{
    return value_f * 10;
}

/***********************************************************************************/

void app_init(void)
{
    app_temp_ctrl.heat_state = HEAT_OFF;
}

/***********************************************************************************/

uint16_t app_get_temperature(void)
{
    return app_temp.avarage_celcius;
}

/***********************************************************************************/


static void app_calc_temperature()
{
    for(uint8_t index = 0; index < NUMBER_OF_PTCS ; index++)
    {
        app_temp.adc_temp_raw[index] = adc_get_value(index);
        app_temp.ptc_resistence[index] = adc_to_resistance(app_temp.adc_temp_raw[index]);
        app_temp.adc_temp_celcius[index] = resistance_to_temperature(app_temp.ptc_resistence[index]);
    }
    app_temp.avarage_celcius = ((float_to_int(app_temp.adc_temp_celcius[PTC_IN_BOX_LOW])+ float_to_int(app_temp.adc_temp_celcius[PTC_IN_BOX_HIGH]))/2);
}

/***********************************************************************************/

void app_update(void)
{
    app_calc_temperature();
    app_read_button_heat_state();
    app_set_heat_state();
    app_led_mcu_status();

    uint16_t setpoint_value = hmi_dashboard_get_setpoint();
    switch (app_temp_ctrl.heat_state)
    {
    case HEAT_ON:
        if (app_temp.avarage_celcius >= setpoint_value)
        {
            app_set_fan_porcentage(30);
            LAMP_DISABLE();
        }
        else if (app_temp.avarage_celcius <= (setpoint_value - 20))
        {
            LAMP_ENABLE();
            app_set_fan_porcentage(2);
        }
        break;
    case HEAT_OFF:
        LAMP_DISABLE();
        app_set_fan_porcentage(0);
        break;
    default:
        break;
    }  


}

/***********************************************************************************/

void app_deinit(void)
{

}
