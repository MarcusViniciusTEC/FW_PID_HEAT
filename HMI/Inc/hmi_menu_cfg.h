#ifndef __HMI_MENU_CFG_H
#define __HMI_MENU_CFG_H


#define CURSOR_SYMBOL ">"

#define hmi_menu_vector_item_default                    \
{                                                       \
    {                                                   \
        .id = HMI_MENU_ID_PID,                          \
        .str    = "1.PID"                               \
    }                                                   \
    ,                                                   \
    {                                                   \
        .id = HMI_MENU_ID_DASHBOARD,                    \
        .str    ="2.DASHBOARD"                          \
    }                                                   \
    ,                                                   \
    {                                                   \
        .id = HMI_MENU_ID_SETTINGS,                     \
        .str    ="2.SETTINGS"                           \
    }                                                   \
}

#endif
