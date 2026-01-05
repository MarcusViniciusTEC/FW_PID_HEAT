#ifndef __HMI_PID_TYPES_H
#define __HMI_PID_TYPES_H

#include "hmi_pid_cfg.h"
#include "stdint.h"

typedef enum
{
    HMI_PID_ID_KP = 0U,
    HMI_PID_ID_KD,
    HMI_PID_ID_KI,
    HMI_PID_ID_KBASE,
    HMI_PID_NUMBER_OF_IDS
}hmi_pid_item_id_t;

typedef struct 
{
    hmi_pid_item_id_t id;
    char *str;
    uint16_t value;
}hmi_pid_data_t;




#endif