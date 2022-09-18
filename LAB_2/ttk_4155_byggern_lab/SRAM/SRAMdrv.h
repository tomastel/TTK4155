#ifndef __SRAMDRV__
#define __SRAMDRV__

#define F_CPU 4.9152E6

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

void SRAM_init();
void latch_test();
void SRAM_test();

#endif __SRAMDRV__