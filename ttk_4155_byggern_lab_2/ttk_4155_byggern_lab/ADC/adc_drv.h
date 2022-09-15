/*
 * IncFile1.h
 *
 * Created: 15.09.2022 12:41:44
 *  Author: khuongh
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#define F_CPU 4.9152E6

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

void adc_drv_init();

uint8_t adc_read(uint8_t channel); //volatile

adc_calibrate();

//pos_t pos_read(void);

#endif /* INCFILE1_H_ */