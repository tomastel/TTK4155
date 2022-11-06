/*
 * ADC_IR.c
 *
 * Created: 30.10.2022 13:54:42
 *  Author: khuongh
 */ 

#include "ADC_IR.h"



#define IR_THRESHOLD 2000 //500

bool game_on = false;
uint32_t IR_last_value, IR_current_value;
uint8_t goal_counter = 0;

int ADC_init()
{
	// Enable ADC controller MCK in PMC (ADC config doesn't require clock to be enabled
	PMC->PMC_PCER1 |= PMC_PCER1_PID37;
	// 
	// Activate ADC channel (temperature sensor)
	ADC->ADC_CHER |= ADC_CHER_CH7;
	// Enable ADC conversion in ADC control register
	//ADC->ADC_CR |= ADC_CR_START;
	// Enable ADC freerun mode (never waits for trigger to convert)
	ADC->ADC_MR |= ADC_MR_FREERUN;
	
	return 0;
}

uint32_t ADC_read_IR()
{
	return ADC->ADC_CDR[7];
}

bool IR_check_for_goal()
{
	IR_current_value = ADC_read_IR();
	if((IR_current_value < IR_THRESHOLD) && IR_last_value >= IR_THRESHOLD) {
		IR_last_value = IR_current_value;
		goal_counter++;
		return true;
	} else {
		IR_last_value = IR_current_value;
		return false;
	}
}

void IR_reset_goals()
{
	goal_counter = 0;
}
