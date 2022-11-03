/*
 * IncFile1.h
 *
 * Created: 13.10.2022 10:29:52
 *  Author: tomasnt
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#include "common_includes.h"
#include "../uart_and_printf/printf.h"
#include "../uart_and_printf/uart.h"

#define LED1ON (PIOA->PIO_SODR = PIO_PA19)
#define LED1OFF (PIOA->PIO_CODR = PIO_PA19)
#define LED1TOGGLE ((PIOA->PIO_ODSR & PIO_PA19) ? LED1OFF : LED1ON)

#define LED2ON (PIOA->PIO_SODR = PIO_PA20)
#define LED2OFF (PIOA->PIO_CODR = PIO_PA20)
#define LED2TOGGLE ((PIOA->PIO_ODSR & PIO_PA20) ? LED2OFF : LED2ON)

void LEDs_init();

void LEDs_blink();

#endif /* INCFILE1_H_ */