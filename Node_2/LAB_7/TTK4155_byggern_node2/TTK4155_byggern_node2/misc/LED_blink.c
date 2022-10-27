/*
 * LED_blink.c
 *
 * Created: 13.10.2022 10:30:21
 *  Author: tomasnt
 */ 

#include "LED_blink.h"

void LEDs_init(){
	// Enable IOs
	PIOA->PIO_PER = PIO_PA19;
	PIOA->PIO_PER = PIO_PA20;
	// Set to output
	PIOA->PIO_OER = PIO_PA19;
	PIOA->PIO_OER = PIO_PA20;
	// Disable pull-up
	PIOA->PIO_PUDR = PIO_PA19;
	PIOA->PIO_PUDR = PIO_PA20;
	
	// Set start value of SysTick reload register
	// Resets every 20ms, (MCLK/prescaler)*percentage of a second.
	SysTick->LOAD = 0x33450;
	SysTick->CTRL = 0x1;
}

void LEDs_blink(){
	uint32_t sys_tick_CTRL_reg = SysTick->CTRL;
	bool time_flag = (sys_tick_CTRL_reg & 0x10000);
	
	if(time_flag){
		LED1TOGGLE;
		LED2TOGGLE;
		SysTick->VAL = 0;
	}
}