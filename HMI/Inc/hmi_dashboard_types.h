#ifndef __HMI_DASHBOARD_TYPES_H
#define __HMI_DASHBOARD_TYPES_H

#include "hmi_dashboard_cfg.h"
#include "stdint.h"

typedef enum
{
    INDEX_FIRST_DIGIT =0U,
    INDEX_SECOND_DIGIT,
    INDEX_THIRD_DIGIT
}hmi_index_digits_t;


typedef enum
{
    CURSOR_STATE_IDLE = 0U,
    CURSOR_STATE_SHOW_NUMBER,
    CURSOR_STATE_WAIT_HIDE_DELAY,
    CURSOR_STATE_HIDE_NUMBER,
    CURSOR_STATE_WAIT_SHOW_DELAY
}hmi_cursor_blnk_state_t;

typedef enum
{
    CURSOR_BLINK_ON = 0U,
    CURSOR_BLINK_OFF
}hmi_cursor_state_t;

typedef struct 
{
    uint8_t setpoint[3];
}hmi_edit_value_t;

typedef struct 
{
    hmi_cursor_blnk_state_t cursor_blnk_state;
    hmi_cursor_state_t cursor_state;
    hmi_index_digits_t index;
    uint32_t last_time_show_cursor;
    uint32_t last_time_hide_cursor;
    uint32_t last_time_blnk_cursor;
    
}hmi_ctrl_t;



#endif