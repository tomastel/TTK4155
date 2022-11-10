/*
 * encoder.h
 *
 * Created: 03.11.2022 09:27:03
 *  Author: haavarok
 */ 


#ifndef ENCODER_H_
#define ENCODER_H_

#include "../misc/common_includes.h"

void motor_box_init();
int16_t encoder_read();
void motor(int16_t direction_value);

#endif /* ENCODER_H_ */
