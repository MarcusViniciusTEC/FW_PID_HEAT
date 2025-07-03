
#include "adc.h"
#include "main.h"

/***********************************************************************************/

extern uint16_t adc_buffer[ADC_NUMBER_OF_CHANNELS];
volatile uint32_t adc_execution_rate_1ms_timer;

/***********************************************************************************/

uint16_t adc_get_value(adc_channels_t adc);
uint16_t filter_adc(adc_channels_t adc);
static adc_value_t adc_value = {0};

/***********************************************************************************/

uint16_t adc_get_value(adc_channels_t adc)
{
    return adc_value.adc_raw[adc];
}

/***********************************************************************************/

uint16_t filter_adc(adc_channels_t adc)
{
    uint32_t adc_filtered[ADC_NUMBER_OF_CHANNELS]  = {0}; 

    for(uint16_t samples = 0; samples < NUMBER_OF_SAMPLES; samples++)
    {
        adc_filtered[adc] += adc_buffer[adc];
    }
    return (adc_filtered[adc]/NUMBER_OF_SAMPLES);
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
    for(uint8_t channel = 0; channel < ADC_NUMBER_OF_CHANNELS; channel++ )
    {
        adc_value.adc_raw[channel] = filter_adc(channel);
    }
}

/***********************************************************************************/

void adc_deinit(void)
{

}
