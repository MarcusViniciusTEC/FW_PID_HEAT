#ifndef __HMI_PID_CFG_H
#define __HMI_PID_CFG_H

#define HMI_PID_NUMBER_OF_ITENS 4


#define hmi_pid_vector_item_default                     \
{                                                       \
    {                                                   \
        .id = HMI_PID_ID_KP,                            \
        .str    = "1.KP    =",                          \
        .value  = 10                                    \
    }                                                   \
    ,                                                   \
    {                                                   \
        .id = HMI_PID_ID_KI,                            \
        .str    ="2.KI    =",                           \
        .value  =   3                                   \
    }                                                   \
    ,                                                   \
    {                                                   \
        .id = HMI_PID_ID_KD,                            \
        .str    ="3.KD    =",                           \
        .value  =   2,                                  \
    }                                                   \
    ,                                                   \
    {                                                   \
        .id = HMI_PID_ID_KBASE,                         \
        .str    ="4.KBASE =",                           \
        .value  = 100                                   \
    }                                                   \
}


#endif