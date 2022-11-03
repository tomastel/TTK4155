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
	
	PIOB->PIO_CODR = PIO_PB26;
}

void doink()
{
	PIOB->PIO_SODR = PIO_PB26;
	delay_ch1_micro(10);
	PIOB->PIO_CODR = PIO_PB26;
}