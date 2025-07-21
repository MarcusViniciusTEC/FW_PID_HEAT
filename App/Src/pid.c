

#include "pid.h"
#include "sl_lib.h"
#include "hmi_dashboard.h"
#include "app.h"

/***********************************************************************************/

volatile uint32_t pid_execution_rate_1ms_timer;

/***********************************************************************************/

static sl_pid_data_type pid_lamp;
int pid_value = 0;

/***********************************************************************************/

int get_pid_calc(void);

/***********************************************************************************/

void pid_1ms_clock(void)
{
    
}

/***********************************************************************************/

int get_pid_calc(void)
{
    return pid_value;
}


/***********************************************************************************/

void pid_init(void)
{
    sl_pid_init(&pid_lamp, 120, 1, 0, 100, 0, 900);
}

/***********************************************************************************/

void pid_update(void)
{
    uint16_t setpoint = hmi_dashboard_get_setpoint();
    uint16_t temperature = app_get_temperature();

    int error = setpoint - temperature;
    pid_value = sl_pid_calc(&pid_lamp, error);
}

/***********************************************************************************/

void pid_deinit(void)
{

}
