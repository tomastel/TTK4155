/*
 * IncFile1.h
 *
 * Created: 15.09.2022 12:41:44
 *  Author: khuongh
 */ 


#ifndef _ADC_DRV_H_
#define _ADC_DRV_H_

#include "../MISC/common_includes.h"

void adc_drv_init();

uint8_t adc_read(uint8_t channel); //volatile

adc_calibrate();

//pos_t pos_read(void);

#endif /* INCFILE1_H_ */