/*
 * CFile1.c
 *
 * Created: 15.09.2022 12:40:48
 *  Author: khuongh
 */ 

#include "adc_drv.h"

uint8_t offset_x = 0;
uint8_t offset_y = 0;

void adc_drv_init()
{
	// to do:
	// Change TCCR1A and TCCR1B as a hex value 
	// Change DDRD register to a more correct 8 bit value
	// Change wiring from USB thingy
	set_bit(DDRD, ADC_EXT_CLK_SGN_PIN);
	
	TCCR1B |= (1 << WGM13); // Choosing fast PWM
	TCCR1B |= (1 << WGM12);	// Choosing fast PWM
	TCCR1A |= ( 1 << WGM11 ); //Choosing fast PWM
	TCCR1A |= ( 1 << WGM10); // Choosing fast PWM
	
	TCCR1A &= ~( 1 << COM1A1); // Toggle Compare
	TCCR1A |= ( 1 << COM1A0); // Toggle Compare
	TCCR1A &= ~( 1 << COM1B1); // Set on Compare
	TCCR1A &= ~( 1 << COM1B0); // Set on Compare
	
		
	TCCR1B &= ~( 1 << CS12); // Prescaler
	TCCR1B &= ~( 1 << CS11); // Prescaler
	TCCR1B |= ( 1 << CS10); // Prescaler
	
	
	TCCR1A &= ~(1 << FOC1A);
	TCCR1A &= ~(1 << FOC1B);
		
}

uint8_t adc_read(uint8_t channel)
{
	volatile uint8_t adc_value[4] = { 0 };
	volatile char *adc = (char *) 0x1400;
	
	//Writing to ADC register to start getting adc value
	adc[0] = 0;
	//control the delay!!
	_delay_us(30);
	
	//adc_ch1 = adc[0];
	
	for (uint16_t i = 0; i < 4; i++) {
		adc_value[i] = adc[i];
	}
	
	
	
	return adc_value[channel];
}

void adc_calibrate()
{
	offset_x = adc_read(JOYSTICK_X_CHANNEL);
	offset_y = adc_read(JOYSTICK_Y_CHANNEL);
	printf("offset_x: %d, offset_y: %d\r\n", offset_x, offset_y);
}

int8_t adc_conv_js_val(uint8_t raw_value, uint8_t offset_value)
{

	if (raw_value >= offset_value) {
		return ((raw_value - offset_value) *100 / (ADC_MAX - offset_value));
	}
	return ((raw_value - offset_value) * 100 / offset_value );
}

pos_t pos_read()
{
	pos_t positions;
	positions.X = adc_conv_js_val(adc_read(JOYSTICK_X_CHANNEL), offset_x);
	positions.Y = adc_conv_js_val(adc_read(JOYSTICK_Y_CHANNEL), offset_y);
	
	return positions;
}

dir_t dir_read(pos_t positions)
{	
	if (abs(positions.X) <= ADC_JOYSTICK_THRESHOLD) {
		if (abs(positions.Y) <= ADC_JOYSTICK_THRESHOLD) {
			return NEUTRAL;
		} else if (positions.Y > ADC_JOYSTICK_THRESHOLD) {
			return UP;
		} else if (positions.Y < ADC_JOYSTICK_THRESHOLD) {
			return DOWN;
		}
	} else if (positions.X > ADC_JOYSTICK_THRESHOLD) {
		if (abs(positions.Y) <= ADC_JOYSTICK_THRESHOLD) {
			return RIGHT;
		} else if (positions.Y > ADC_JOYSTICK_THRESHOLD) {
			return UP_RIGHT;
		} else if (positions.Y < ADC_JOYSTICK_THRESHOLD) {
			return DOWN_RIGHT;
		}
	} else if (positions.X < ADC_JOYSTICK_THRESHOLD) {
		if (abs(positions.Y) <= ADC_JOYSTICK_THRESHOLD) {
			return LEFT;
		} else if (positions.Y > ADC_JOYSTICK_THRESHOLD) {
			return UP_LEFT;
		} else if (positions.Y < ADC_JOYSTICK_THRESHOLD) {
			return DOWN_LEFT;
		}
	}
}

uint8_t slider_read(uint8_t channel)
{
	return (100 * adc_read(channel) / ADC_MAX);
}