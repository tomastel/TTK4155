/*
 * motor.c
 *
 * Created: 03.11.2022 09:27:17
 *  Author: haavarok
 */ 

#include "motor.h"
#include "../timer/timer_counter.h"

#define MJ1_DIR_PIN		PIO_PD10
#define MJ1_EN_PIN		PIO_PD9
#define MJ1_SEL_PIN		PIO_PD2
#define MJ1_NOT_RST_PIN	PIO_PD1
#define MJ1_NOT_OE_PIN	PIO_PD0
#define MJEX_MOTOR_SPEED_PIN PIO_PB16

#define DACC_MAX_VALUE 2500
#define DACC_MIN_VALUE 1500
#define DACC_RANGE (DACC_MAX_VALUE-DACC_MIN_VALUE)

void motor_box_init()
{
	// Enabling DAC and PIOC peripheral
	PMC->PMC_PCER1 |= PMC_PCER1_PID38;
	PMC->PMC_PCER0 |= PMC_PCER0_PID13;
	// Enabling PIOD pins for motor
	PIOD->PIO_PER |= 0x607;
	// Enabling PIOD pins for encoder (default enabled as inputs)
	PIOC->PIO_PER |= 0x1FE;
	// Enabling DAC CH1 (PB16)
	DACC->DACC_CHER |= DACC_CHER_CH1;
	// Select DACC CH1 for analog output
	DACC->DACC_MR |= DACC_MR_REFRESH(0x1);
	DACC->DACC_MR |= DACC_MR_STARTUP_8;

	// Sets motors pins to output
	PIOD->PIO_OER |= 0x607;
	
	// Select DAC channel and set max output value
	DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;
	DACC->DACC_CDR |= DACC_MAX_VALUE;

	// Set MJ1 pin !OE and !RST high
	PIOD->PIO_SODR |= MJ1_NOT_OE_PIN;
	PIOD->PIO_SODR |= MJ1_NOT_RST_PIN;
	
	// Wait for motor to get in start position
	motor(-1405);
	motor_init_delay();
	
	PIOD->PIO_CODR |= MJ1_NOT_RST_PIN;
	delay_ch1_micro(100);
	PIOD->PIO_SODR |= MJ1_NOT_RST_PIN;
}

int16_t encoder_map(int16_t raw_encoder_value)
{
	//printf("Raw encoder value: %d\n\r", raw_encoder_value);
	int32_t encoder_mapped_value = raw_encoder_value*100/1405;
	return encoder_mapped_value;
}

int16_t encoder_read()
{
	int16_t encoder_value_low = 0;
	int16_t encoder_value_high = 0;
	int16_t encoder_value = 0;
	uint16_t mapped_encoder_value;
	PIOD->PIO_CODR = MJ1_NOT_OE_PIN;
	PIOD->PIO_CODR = MJ1_SEL_PIN;
	
	delay_ch1_micro(20);
	
	uint32_t PIOC_PIN_DATA = PIOC->PIO_PDSR;
		
	encoder_value_high =  (PIOC_PIN_DATA & (0x1FE));
	
	PIOD->PIO_SODR = MJ1_SEL_PIN;
	
	delay_ch1_micro(20);
	
	uint32_t PIOC_PIN_DATA1 = PIOC->PIO_PDSR;

	encoder_value_low = (PIOC_PIN_DATA1 & (0x1FE));
	
	//printf("Data high: %d, Data low: %d\n\r", encoder_value_high, encoder_value_low);
	
	encoder_value = (encoder_value_high << 7) |
					(encoder_value_low >> 1);
	
	PIOD->PIO_SODR = MJ1_NOT_OE_PIN;
	
	//mapped_encoder_value = encoder_map(encoder_value);
	
	return encoder_value;
}

void motor(int16_t direction_value)
{
	bool motor_dir, motor_on;
	int32_t DACC_value = abs(direction_value*DACC_RANGE/1405) + DACC_MIN_VALUE;
	
	//printf("dir val: %d, Motor DACC_value: %d\n\r", direction_value, DACC_value);

	if (direction_value < -5) {
		motor_on = true;
		motor_dir = false;
	} else if (direction_value > 5) {
		motor_on = true;
		motor_dir = true;
	} else {
		motor_on = false;
	}
	
	DACC->DACC_MR = DACC_MR_USER_SEL_CHANNEL1;
	DACC->DACC_CDR = DACC_value;

	if (motor_on) {
		if (motor_dir) {
			PIOD->PIO_SODR = MJ1_DIR_PIN;
		} else {
			PIOD->PIO_CODR = MJ1_DIR_PIN;
		}
		PIOD->PIO_SODR = MJ1_EN_PIN;
	} else {
		PIOD->PIO_CODR = MJ1_EN_PIN;
	}
}

void motor_init_delay()
{
	delay_ch1_micro(500000);
	delay_ch1_micro(500000);
	delay_ch1_micro(500000);
	delay_ch1_micro(500000);
}
