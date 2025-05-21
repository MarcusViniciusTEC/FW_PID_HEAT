#ifndef __HMI_DASHBOARD_H
#define __HMI_DASHBOARD_H


void hmi_dashboard_init();            
void hmi_dashboard_show_screen();           
void hmi_dashboard_update_data();            
void hmi_dashboard_update_button(button_id_t button_id, button_press_type_t button_press_type);      

#endif
