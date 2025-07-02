
#include "adc.h"
#include "main.h"

/***********************************************************************************/

extern uint16_t adc_buffer[1];
volatile uint32_t adc_execution_rate_1ms_timer;

/***********************************************************************************/

typedef struct 
{
    uint16_t adc_raw;
    uint8_t  adc_porcentage;
    uint8_t channel;
}adc_value_t;

// typedef struct
// {
//     ADC_0 = 0U,
//     ADC_1
// }adc_channels_t;

/***********************************************************************************/

uint16_t adc_get_value(uint8_t channel);
uint16_t filter_adc(uint8_t channel);

static adc_value_t adc_value = {0};

/***********************************************************************************/

uint16_t adc_get_value(uint8_t channel)
{
    adc_value.channel = channel;
    return adc_value.adc_raw;
}

/***********************************************************************************/

uint16_t filter_adc(uint8_t channel)
{
    uint32_t adc_filtered = 0;

    for(uint16_t samples = 0; samples < NUMBER_OF_SAMPLES; samples++)
    {
        adc_filtered += adc_buffer[channel];
    }
    return (adc_filtered/NUMBER_OF_SAMPLES);
}

/***********************************************************************************/

void adc_1ms_clock(void)
{

}

/***********************************************************************************/

void adc_init(void)
{

}

/***********************************************************************************/

void adc_update(void)
{
    adc_value.adc_raw = filter_adc(adc_value.channel);
}

/***********************************************************************************/

void adc_deinit(void)
{

}
