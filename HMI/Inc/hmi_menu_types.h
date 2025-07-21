#ifndef __HMI_MENU_TYPES_H
#define __HMI_MENU_TYPES_H

#include "hmi_menu_cfg.h"

typedef enum
{
    HMI_MENU_ID_PID = 0U,
    HMI_MENU_ID_DASHBOARD,
    HMI_MENU_ID_SETTINGS,
    HMI_NUMBER_ID_OF_MENU_ITEM
}menu_item_id_t;

typedef struct 
{
    menu_item_id_t id;
    char *str;
}hmi_menu_data_t;

typedef struct 
{
    uint8_t item_index;
}hmi_menu_ctrl_t;



#endif