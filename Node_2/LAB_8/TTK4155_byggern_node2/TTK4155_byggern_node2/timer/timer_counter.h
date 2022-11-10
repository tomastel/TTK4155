/*
 * timer_counter.h
 *
 * Created: 03.11.2022 14:52:19
 *  Author: haavarok
 */ 


#ifndef TIMER_COUNTER_H_
#define TIMER_COUNTER_H_

#include "../misc/common_includes.h"

void timer_counter_init();
void timer_ch0_start();
void delay_ch1_micro(uint32_t microsec);

#endif /* TIMER_COUNTER_H_ */
