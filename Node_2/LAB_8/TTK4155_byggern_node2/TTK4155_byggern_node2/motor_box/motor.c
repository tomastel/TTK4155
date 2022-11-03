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

#define MJ2_DO0_PIN	PIO_PC1
#define MJ2_DO1_PIN	PIO_PC2
#define MJ2_DO2_PIN	PIO_PC3
#define MJ2_DO3_PIN	PIO_PC4
#define MJ2_DO4_PIN	PIO_PC5
#define MJ2_DO5_PIN	PIO_PC6
#define MJ2_DO6_PIN	PIO_PC7
#define MJ2_DO7_PIN	PIO_PC8

#define MJEX_MOTOR_SPEED_PIN PIO_PB16

void motor_box_init()
{
	PMC->PMC_PCER1 = PMC_PCER1_PID38;
	// Enabling PIOD pins for motor
	PIOD->PIO_PER = 0x607;
	// Enabling PIOD pins for encoder (default enabled as inputs)
	PIOC->PIO_PER = 0x1FE;
	// Enabling DAC CH1 (PB16)
	DACC->DACC_CHER = DACC_CHER_CH1;
	// Select DACC CH1 for analog output
	DACC->DACC_MR = DACC_MR_REFRESH(0x1);
	DACC->DACC_MR = DACC_MR_STARTUP_8;

	// Sets motors pins to output
	PIOD->PIO_OER = 0x607;
	
	DACC->DACC_MR = DACC_MR_USER_SEL_CHANNEL1;
	DACC->DACC_CDR = 2500;
	
	// Set MJ1 pin !OE and !RST high
	PIOD->PIO_SODR = MJ1_NOT_OE_PIN;
	PIOD->PIO_SODR = MJ1_NOT_RST_PIN;
	
}

int16_t encoder_read()
{
	int16_t encoder_value;
	PIOD->PIO_CODR = MJ1_NOT_OE_PIN;
	PIOD->PIO_CODR = MJ1_SEL_PIN;
	
	delay_ch1_micro(20);
	
	encoder_value = (MJ2_DO7_PIN << 15) |
					(MJ2_DO6_PIN << 14) |
					(MJ2_DO5_PIN << 13) |
					(MJ2_DO4_PIN << 12) |
					(MJ2_DO3_PIN << 11) |
					(MJ2_DO2_PIN << 10) |
					(MJ2_DO1_PIN << 9)  |
					(MJ2_DO0_PIN << 8);
	
	PIOD->PIO_SODR = MJ1_SEL_PIN;
	
	delay_ch1_micro(20);
	
	encoder_value = (MJ2_DO7_PIN << 7) |
					(MJ2_DO6_PIN << 6) |
					(MJ2_DO5_PIN << 5) |
					(MJ2_DO4_PIN << 4) |
					(MJ2_DO3_PIN << 3) |
					(MJ2_DO2_PIN << 2) |
					(MJ2_DO1_PIN << 1) |
					(MJ2_DO0_PIN << 0);
	
	PIOD->PIO_SODR = MJ1_NOT_OE_PIN;
	
	return encoder_value;
}

void motor(uint8_t direction_value)
{
	bool motor_dir, motor_on;

	if (direction_value < 30) {
		motor_on = true;
		motor_dir = false;
	} else if (direction_value > 70) {
		motor_on = true;
		motor_dir = true;
	} else {
		motor_on = false;
	}
	
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

