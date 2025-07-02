#ifndef __ADC_H_
#define __ADC_H_


#include "stdint.h"

extern volatile uint32_t adc_execution_rate_1ms_timer;

#define adc_pexecution_rate_1ms_timer (&adc_execution_rate_1ms_timer)

#define ADC_EXECUTION_RATE_1MS_TIME    100


#define NUMBER_OF_SAMPLES (uint16_t)100


void adc_1ms_clock(void);
void adc_init(void);
void adc_update(void);
void adc_deinit(void);

uint16_t adc_get_value(uint8_t channel);


#endif