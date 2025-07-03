#ifndef __APP_H_
#define __APP_H_


#include "stdint.h"

extern volatile uint32_t app_execution_rate_1ms_timer;

#define app_pexecution_rate_1ms_timer (&app_execution_rate_1ms_timer)

#define APP_EXECUTION_RATE_1MS_TIME    100

#define R0  (float) 100.0
#define A   (float) 0.0039083
#define B   (float)-0.0000005775


void app_1ms_clock(void);
void app_init(void);
void app_update(void);
void app_deinit(void);


#endif