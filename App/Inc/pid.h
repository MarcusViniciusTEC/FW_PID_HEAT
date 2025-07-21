#ifndef __PID_H_
#define __PID_H_

#include "stdint.h"

extern volatile uint32_t pid_execution_rate_1ms_timer;

#define pid_pexecution_rate_1ms_timer (&adc_execution_rate_1ms_timer)

#define PID_EXECUTION_RATE_1MS_TIME    50

void pid_1ms_clock(void);
void pid_init(void);
void pid_update(void);
void pid_deinit(void);

int get_pid_calc(void);



#endif