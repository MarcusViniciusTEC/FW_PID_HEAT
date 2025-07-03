

#include "app.h"
#include "stdio.h"
#include "adc.h"
#include "math.h"
#include "LCD_HD44780.h"

#include "hmi_dashboard.h"
#include "adc.h"

volatile uint32_t app_execution_rate_1ms_timer;


uint16_t app_get_temperature(void);

typedef enum
{
    PTC_IN_BOX_HIGH = 0U,
    PTC_IN_BOX_LOW,
    NUMBER_OF_PTCS
}ptc_locations_t;


typedef struct
{
    uint16_t adc_temp_raw[ADC_NUMBER_OF_CHANNELS];
    uint16_t adc_temp_celcius[ADC_NUMBER_OF_CHANNELS];
    uint16_t ptc_resistence[NUMBER_OF_PTCS]

}app_temp_t;

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

void app_1ms_clock(void)
{

}

/***********************************************************************************/

uint16_t float_to_int(float value_f)
{
    return value_f * 10;
}

/***********************************************************************************/

void app_init(void)
{

}

/***********************************************************************************/

uint16_t app_get_temperature(void)
{

    
}

/***********************************************************************************/

void app_update(void)
{
    uint16_t adc_val = adc_get_value(0);

    float resistencia = adc_to_resistance(adc_val);
    float temperatura = resistance_to_temperature(resistencia);

    uint16_t value = hmi_dashboard_get_setpoint();

    char sz_string1[30] = {0};
    snprintf(sz_string1, sizeof(sz_string1), "%d", float_to_int(temperatura));
    vLCD_HD44780_Puts(2, 2, sz_string1);

    char sz_string[30] = {0};
    snprintf(sz_string, sizeof(sz_string), "%d", value );
    vLCD_HD44780_Puts(8, 2, sz_string);
}

/***********************************************************************************/

void app_deinit(void)
{

}
