/*
 * PID.h
 *
 * Created: 30.10.2022 17:10:22
 *  Author: khuongh
 */ 


#ifndef PID_H_
#define PID_H_

#include "../misc/common_includes.h"

uint8_t PID_calculate_gain(uint8_t ref, uint8_t val);



#endif /* PID_H_ */