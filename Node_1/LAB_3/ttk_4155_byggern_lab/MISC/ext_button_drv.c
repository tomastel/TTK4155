/*
 * ext_button_drv.c
 *
 * Created: 15.09.2022 19:15:46
 *  Author: khuongh
 */
#include "ext_button_drv.h"
#include <avr/interrupt.h>

#define LEFT_BUTTON_ISR_REGISTER INT0
#define RIGHT_BUTTON_ISR_REGISTER INT1
#define JOYSTICK_BUTTON_ISR_REGISTER INT2
#define LEFT_BUTTON_PIN PD2
#define RIGHT_BUTTON_PIN PD3
#define JOYSTICK_BUTTON_PIN PE0


ISR (INT0_vect)
{
	printf("Left button pressed\r\n");


}

ISR (INT1_vect)
{
	printf("Right button pressed\r\n");
}

ISR (INT2_vect)
{
	printf("Joystick button pressed\r\n");


}



void ext_button_drv_init(void)
{
	/*
	to do:			
	*/
	clear_bit(DDRD, LEFT_BUTTON_PIN);
	clear_bit(DDRD, RIGHT_BUTTON_PIN);
	clear_bit(DDRE, JOYSTICK_BUTTON_PIN);
	//Disables global interrupts
	cli();
	// Enables interrupt on pin INT0, INT1
	set_bit(GICR, LEFT_BUTTON_ISR_REGISTER);
	set_bit(GICR, RIGHT_BUTTON_ISR_REGISTER);
	// Configures interrupt rising edge on INT2, INT1 & INT0
	set_bit(MCUCR, ISC11);
	set_bit(MCUCR, ISC10);
	set_bit(MCUCR, ISC01);
	set_bit(MCUCR, ISC00);
	//set_bit(EMCUCR, ISC2);
	//Configuring and enabling Joystick interrupt pin INT2
	clear_bit(GICR, JOYSTICK_BUTTON_PIN);
	clear_bit(EMCUCR, ISC2);
	set_bit(GIFR, INTF2);
	set_bit(GICR, JOYSTICK_BUTTON_ISR_REGISTER);
	
	// Enables global interrupts
	sei();	
	
	
}