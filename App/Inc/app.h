#ifndef __APP_H_
#define __APP_H_


#include "stdint.h"
#include "adc.h"

extern volatile uint32_t app_execution_rate_1ms_timer;

#define app_pexecution_rate_1ms_timer (&app_execution_rate_1ms_timer)

#define APP_EXECUTION_RATE_1MS_TIME    100

#define R0  (float) 100.0
#define A   (float) 0.0039083
#define B   (float)-0.0000005775


#define LAMP_ENABLE()                 HAL_GPIO_WritePin(LAMP_ENABLE_GPIO_Port, LAMP_ENABLE_Pin, GPIO_PIN_SET)
#define LAMP_DISABLE()                HAL_GPIO_WritePin(LAMP_ENABLE_GPIO_Port, LAMP_ENABLE_Pin, GPIO_PIN_RESET)

#define LED_HEAT_ON()               HAL_GPIO_WritePin(LED_HEAT_ON_GPIO_Port, LED_HEAT_ON_Pin, GPIO_PIN_SET)
#define LED_HEAT_OFF()              HAL_GPIO_WritePin(LED_HEAT_ON_GPIO_Port, LED_HEAT_ON_Pin, GPIO_PIN_RESET)

#define RELAY_ENABLE_HEATING()      HAL_GPIO_WritePin(RELE_LAMP_GPIO_Port, RELE_LAMP_Pin, GPIO_PIN_SET)
#define RELAY_DISABLE_HEATING()     HAL_GPIO_WritePin(RELE_LAMP_GPIO_Port, RELE_LAMP_Pin, GPIO_PIN_RESET)

/***********************************************************************************/

typedef enum
{
    HEAT_OFF = 0U,
    HEAT_ON
}app_heat_state_t;

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
    uint16_t ptc_resistence[NUMBER_OF_PTCS];
    uint16_t avarage_celcius;

}app_temp_t;

typedef struct
{
    app_heat_state_t heat_state;


}app_temp_ctrl_t;


/***********************************************************************************/


void app_1ms_clock(void);
void app_init(void);
void app_update(void);
void app_deinit(void);

app_heat_state_t app_get_heat_state(void);
uint16_t app_get_temperature(void);


#endif