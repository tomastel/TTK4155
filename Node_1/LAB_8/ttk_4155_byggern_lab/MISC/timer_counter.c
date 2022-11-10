/*
 * timer_counter.c
 *
 * Created: 20.10.2022 11:21:42
 *  Author: haavarok
 */ 

#include "timer_counter.h"
#include "prints.h"
#include "common_includes.h"

void timer_init() {
	// Compare output channel A, clear on compare match, ICR (Input Capture Register)
	TCCR3A = 0x40;
	// ICR, prescaler = 1024
	TCCR3B = 0xD;
	// Enable output compare A match interrupt
	ETIMSK = 0x10;
	// Compare match on 96 (0x1D4)
	// Interrupt on: sek = 1/(F_osc/prescaler)*Compare_match [sec]
	OCR3A = 0x1D4; // Interrupt every 98 ms
}
