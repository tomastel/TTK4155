/*
 * Solenoid.c
 *
 * Created: 03.11.2022 19:18:20
 *  Author: haavarok
 */ 

#include "Solenoid.h"

void solenoid_init()
{
	// Enable IOs
	PIOB->PIO_PER = PIO_PB26;
	// Set PIN22 as output
	PIOB->PIO_OER = PIO_PB26;
	// Disable pull-up
	PIOB->PIO_PUDR = PIO_PB26;
	// Setting Pin Low
	PIOB->PIO_SODR = PIO_PB26;
}

void solenoid_impulse()
{
	//Setting and resetting pin for Solenoid
	PIOB->PIO_CODR = PIO_PB26;
	delay_ch1_micro(50000);
	PIOB->PIO_SODR = PIO_PB26;
}