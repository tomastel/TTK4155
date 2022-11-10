/*
 * PWM_drv.h
 *
 * Created: 20.10.2022 16:01:09
 *  Author: haavarok
 */ 

#ifndef PWM_DRV_H_
#define PWM_DRV_H_

#include "../misc/common_includes.h"

void PWM_init();
uint32_t PWM_set_period_percentage(int16_t percentage);

#endif /* PWM_DRV_H_ */
