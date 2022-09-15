/*
 * CFile1.c
 *
 * Created: 15.09.2022 12:40:48
 *  Author: khuongh
 */ 

//#include "MISC/bit_drv.h"
#include "adc_drv.h"

void adc_drv_init()
{
	// to do:
	// Change TCCR1A and TCCR1B as a hex value 
	// Change DDRD register to a more correct 8 bit value
	// Change wiring from USB thingy
	DDRD = 0xFF;
	
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
	uint8_t adc_value = 0;
	uint8_t adc_ch1 = 0;
	uint8_t adc_ch2 = 0;
	uint8_t adc_ch3 = 0;
	
	volatile char *adc = (char *) 0x1400;
	
	adc[0] = 0;
	_delay_us(30);
	
	//adc_ch1 = adc[0];
	
	for (uint16_t i = 0; i < 4; i++) {
		uint8_t adc_ch1 = adc[0];
		printf("ADC_CH1 value: adc[%4d] = %02X\r\n", i, adc_ch1);
	}
	
	
	
	return adc_value;
}