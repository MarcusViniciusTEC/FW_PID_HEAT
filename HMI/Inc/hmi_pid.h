#ifndef __HMI_PID_H
#define __HMI_PID_H

#include "buttons_types.h"

void hmi_pid_init(void);
void hmi_pid_show_screen(void);
void hmi_pid_update_data(void);
void hmi_pid_update_button(button_id_t button_id, button_press_type_t button_press_type);


#endif