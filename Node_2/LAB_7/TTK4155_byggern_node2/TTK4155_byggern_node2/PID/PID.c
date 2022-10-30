/*
 * PID.c
 *
 * Created: 30.10.2022 17:10:09
 *  Author: khuongh
 */ 

#include "PID.h"

#define KP 1
#define TI 10
#define TD 1

uint8_t PID_calculate_gain(uint8_t ref, uint8_t val)
{
	uint8_t deviation = ref - val;
	
	
	
}