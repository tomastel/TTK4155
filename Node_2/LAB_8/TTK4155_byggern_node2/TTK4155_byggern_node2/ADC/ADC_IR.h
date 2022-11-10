/*
 * ADC_IR.h
 *
 * Created: 30.10.2022 13:54:27
 *  Author: khuongh
 */ 

#ifndef ADC_IR_H_
#define ADC_IR_H_

#include "../misc/common_includes.h"

void ADC_init();
uint32_t ADC_read_IR();
bool IR_check_for_goal();
void reset_IR();

#endif /* ADC_IR_H_ */
