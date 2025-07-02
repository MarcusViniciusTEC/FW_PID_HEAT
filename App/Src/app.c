

#include "app.h"
#include "stdio.h"
#include "adc.h"
#include "math.h"
#include "LCD_HD44780.h"

volatile uint32_t app_execution_rate_1ms_timer;

/***********************************************************************************/

float adc_to_resistance(uint16_t adc_val)
{
    if (adc_val <= 750)
        return 110.0;

    if (adc_val <= 1530)
        return 110.0 + ((adc_val - 750) * (120.0 - 110.0)) / (1530 - 750);

    if (adc_val <= 2131)
        return 120.0 + ((adc_val - 1530) * (130.0 - 120.0)) / (2131 - 1530);

    return 130.0;  // limite superior conhecido
}

float resistance_to_temperature(float R)
{
    const float R0 = 100.0;
    const float A  = 0.0039083;
    const float B  = -0.0000005775;

    float disc = A*A - 4*B*(1 - (R / R0));
    if (disc < 0) return -999.0;  // erro

    return (-A + sqrtf(disc)) / (2*B);
}

void app_1ms_clock(void)
{

}

/***********************************************************************************/


void app_init(void)
{

}

/***********************************************************************************/


void app_update(void)
{


uint16_t adc_val = adc_get_value(0);

float resistencia = adc_to_resistance(adc_val);
float temperatura = resistance_to_temperature(resistencia);

    char sz_string[30] = {0};
    snprintf(sz_string, sizeof(sz_string), "%.2f", temperatura );
    vLCD_HD44780_Puts(2, 2, sz_string);
}

/***********************************************************************************/

void app_deinit(void)
{

}
