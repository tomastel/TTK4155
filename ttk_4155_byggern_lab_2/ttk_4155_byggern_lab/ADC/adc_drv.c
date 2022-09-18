/*
 * CFile1.c
 *
 * Created: 15.09.2022 12:40:48
 *  Author: khuongh
 */ 

#include "adc_drv.h"

#define LEFT_SLIDER_CHANNEL 0
#define RIGHT_SLIDER_CHANNEL 1
#define JOYSTICK_Y_CHANNEL 2
#define JOYSTICK_X_CHANNEL 3
#define ADC_EXT_CLK_SGN_PIN PD5

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
		printf("%d: %d\r\n", i, adc[i]);
		//adc_value[i] = adc[i];
	}
	
	
	
	//return adc_value[channel];
	return 0;
}