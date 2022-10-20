/*
 * ext_button_drv.h
 *
 * Created: 15.09.2022 19:16:14
 *  Author: khuongh
 */ 


#ifndef EXT_BUTTON_DRV_H_
#define EXT_BUTTON_DRV_H_

#include "common_includes.h"
#include "../ADC/adc_drv.h"

#define RIGHT_BUTTON_ISR_REGISTER INT1
#define JOYSTICK_BUTTON_ISR_REGISTER INT2
#define RIGHT_BUTTON_PIN PD3
#define JOYSTICK_BUTTON_PIN PE0

void ext_button_drv_init(void);

#endif /* EXT_BUTTON_DRV_H_ */
