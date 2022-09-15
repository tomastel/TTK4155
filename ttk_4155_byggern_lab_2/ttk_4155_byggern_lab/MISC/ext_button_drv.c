/*
 * ext_button_drv.c
 *
 * Created: 15.09.2022 19:15:46
 *  Author: khuongh
 */
#include "ext_button_drv.h"
#include <avr/interrupt.h>

ISR (INT1_vect)
{
	printf("Haavard liker kake\r\n");
}


void ext_button_drv_init(void)
{
	/*
	to do:
			
	*/
	clear_bit(DDRD,PD3);
	//Disables global interrupts
	cli();
	// Enables interrupt on pin INT1
	set_bit(GICR, INT1);
	// Configures interrupt falling edge
	set_bit(MCUCR, ISC11);
	clear_bit(MCUCR, ISC10);
	// Enables global interrupts
	sei();	
	
	
}