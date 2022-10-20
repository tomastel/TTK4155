/*
 * PWM_drv.c
 *
 * Created: 20.10.2022 16:00:46
 *  Author: haavarok
 */ 

//PWM->PWM_WPCR = 0x50574DFC;


#include "PWM_drv.h"
#include "../misc/common_includes.h"
#include "sam3x8e.h"

#define PWM_WPCR_KEY 0x50574D

void PWM_init()
{
	PIOC->PIO_PER = PIO_PC22;
	// Disable PWM control register write protect
	PWM_WPCR_WPKEY(PWM_WPCR_KEY);
	// Disable write protection on all PWM register groups (ref ATSAM datasheet page 1037)
	PWM->PWM_WPCR = PWM_WPCR_WPRG0 | PWM_WPCR_WPRG1 | PWM_WPCR_WPRG2 | PWM_WPCR_WPRG3 | PWM_WPCR_WPRG4 | PWM_WPCR_WPRG5;
	PWM_WPCR_WPCMD(0x0);

	// Set CLKA prescaler to MCK/64
	PWM_CLK_PREA(0x6);
	// Set CLKA to be selected by PREA
	PWM_CLK_DIVA(0x1);
	
	//Sets CLK for PWM channel 0 to CLKA
	PWM->PWM_CH_NUM[5].PWM_CMR = PWM_CMR_CPRE_CLKA;
	//Sets channel 0 period update to 20 ms (with prescaler = 64)
	PWM->PWM_CH_NUM[5].PWM_CPRD = PWM_CPRD_CPRD(0xC35);
	//Sets channel 0 Duty Cycle to 1,5 ms, mid position for servo
	PWM->PWM_CH_NUM[5].PWM_CDTY = PWM_CDTY_CDTY(0xEA);
	
	//Enables PWM channel 0
	PWM->PWM_ENA = PWM_ENA_CHID5;
	
	PWM_WPCR_WPKEY(PWM_WPCR_KEY);
	// Disable write protection on all PWM register groups (ref ATSAM datasheet page 1037)
	PWM->PWM_WPCR = PWM_WPCR_WPRG0 | PWM_WPCR_WPRG1 | PWM_WPCR_WPRG2 | PWM_WPCR_WPRG3 | PWM_WPCR_WPRG4 | PWM_WPCR_WPRG5;
	PWM_WPCR_WPCMD(0x1);
	
}