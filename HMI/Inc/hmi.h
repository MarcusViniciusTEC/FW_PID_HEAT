
#ifndef __HMI_H
#define __HMI_H

#include "stdint.h"

extern volatile uint32_t hmi_execution_rate_1ms_timer;

#define hmi_pexecution_rate_1ms_timer (&hmi_execution_rate_1ms_timer)

#define HMI_EXECUTION_RATE_1MS_TIME    		30

#include "buttons_types.h"
#include "hmi_types.h"

void hmi_1ms_clock(void);
void hmi_init(void);
void hmi_update(void);
void hmi_deinit(void);
void hmi_showing_update_data(button_id_t button_id, button_press_type_t button_press_type);
void hmi_set_screen(hmi_screens_id_t hmi_screens_id);

#endif
