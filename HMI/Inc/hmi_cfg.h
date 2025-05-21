
#ifndef __HMI_CFG_H
#define __HMI_CFG_H

#include "buttons_types.h"
#include "hmi_menu.h"
#include "hmi.h"
#include "hmi_intro.h"
#include "hmi_dashboard.h"


/*******************************************************************************/

#define HMI_NUMBER_OF_SCREENS 3

/*******************************************************************************/

#define vector_hmi_screens_default          \
{                                           \
    {                                       \
        HMI_ID_SCREEN_INTRO,                \
        hmi_intro_init,                     \
        hmi_intro_show_screen,              \
        hmi_intro_update_data,              \
        hmi_intro_update_button,            \
    }                                       \
    ,                                       \
    {                                       \
        HMI_ID_SCREEN_MENU,                 \
        hmi_menu_init,                      \
        hmi_menu_show_screen,               \
        hmi_menu_update_data,               \
        hmi_menu_update_button,             \
    }                                       \
    ,                                       \
    {                                       \
        HMI_ID_SCREEN_DASHBOARD,            \
        hmi_dashboard_init,                 \
        hmi_dashboard_show_screen,          \
        hmi_dashboard_update_data,          \
        hmi_dashboard_update_button,        \
    }                                       \
}

/*******************************************************************************/

#define vector_buttons_data_default                     \
{                                                       \
    {                                                   \
        {BT_UP_GPIO_Port, BT_UP_Pin},                   \
        hmi_showing_update_data,                        \
        BUTTON_STATE_START,                             \
        BUTTON_UP_ID,                                   \
        RESET,                                          \
        BUTTON_FIRST_TIME                               \
    }                                                   \
    ,                                                   \
    {                                                   \
        {BT_LEFT_GPIO_Port, BT_LEFT_Pin},               \
        hmi_showing_update_data,                        \
        BUTTON_STATE_START,                             \
        BUTTON_LEFT_ID,                                 \
        RESET,                                          \
        BUTTON_FIRST_TIME                               \
    }                                                   \
    ,                                                   \
    {                                                   \
        {BT_RIGHT_GPIO_Port, BT_RIGHT_Pin},             \
        hmi_showing_update_data,                        \
        BUTTON_STATE_START,                             \
        BUTTON_RIGHT_ID,                                \
        RESET,                                          \
        BUTTON_FIRST_TIME                               \
    }                                                   \
    ,                                                   \
    {                                                   \
        {BT_DOWN_GPIO_Port, BT_DOWN_Pin},               \
        hmi_showing_update_data,                        \
        BUTTON_STATE_START,                             \
        BUTTON_DOWN_ID,                                 \
        RESET,                                          \
        BUTTON_FIRST_TIME                               \
    }                                                   \
}



#endif