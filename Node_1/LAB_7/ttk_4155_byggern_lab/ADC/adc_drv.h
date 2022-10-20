/*
 * IncFile1.h
 *
 * Created: 15.09.2022 12:41:44
 *  Author: khuongh
 */ 


#ifndef _ADC_DRV_H_
#define _ADC_DRV_H_


#include "../MISC/common_includes.h"

#define LEFT_SLIDER_CHANNEL 0
#define RIGHT_SLIDER_CHANNEL 1
#define JOYSTICK_Y_CHANNEL 2
#define JOYSTICK_X_CHANNEL 3
#define ADC_EXT_CLK_SGN_PIN PD5
#define ADC_MAX 255
#define ADC_JOYSTICK_DIR_THRESHOLD 70 //Changed from 3
#define ADC_JOYSTICK_POS_THRESHOLD 4

typedef struct {
	int8_t X;
	int8_t Y;
}pos_t;

typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL,
	UP_RIGHT,
	UP_LEFT,
	DOWN_RIGHT,
	DOWN_LEFT,
}dir_t;

typedef struct {
	pos_t position;
	dir_t direction;
}fun_stick_t;

fun_stick_t adc_drv_fun_stick_get();

bool adc_drv_joystick_update();

void adc_drv_init();

uint8_t adc_read(uint8_t channel); //volatile

void adc_calibrate();

pos_t pos_read();

dir_t dir_read(pos_t positions);

int8_t adc_conv_js_val(uint8_t raw_value, uint8_t offset_value);


#endif /* INCFILE1_H_ */