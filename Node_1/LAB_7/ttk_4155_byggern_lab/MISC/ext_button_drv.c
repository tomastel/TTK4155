/*
 * ext_button_drv.c
 *
 * Created: 15.09.2022 19:15:46
 *  Author: khuongh
 */
#include "ext_button_drv.h"
#include "prints.h"
#include "../CAN/CANdrv.h"

CAN_msg CAN_msg_btn = {
	.ID = 2,
	.length = 2,
	.message = {0 ,0}
};

ISR (INT1_vect)
{
	print_uart("Right button pressed\r\n");
	CAN_msg_btn.message[0] = 1;
	CAN_msg_btn.message[1] = 1;
	CAN_send(CAN_msg_btn);
}

ISR (INT2_vect)
{
	print_uart("Joystick button pressed\r\n");
	enter();
	
}


void ext_button_drv_init(void)
{
	clear_bit(DDRD, RIGHT_BUTTON_PIN);
	clear_bit(DDRE, JOYSTICK_BUTTON_PIN);
	//Disables global interrupts
	cli();
	// Enables interrupt on pin INT1
	set_bit(GICR, RIGHT_BUTTON_ISR_REGISTER);
	// Configures interrupt rising edge on INT1
	set_bit(MCUCR, ISC11);
	set_bit(MCUCR, ISC10);
	//set_bit(EMCUCR, ISC2);
	//Configuring and enabling Joystick interrupt pin INT2
	clear_bit(GICR, JOYSTICK_BUTTON_PIN);
	clear_bit(EMCUCR, ISC2);
	set_bit(GIFR, INTF2);
	set_bit(GICR, JOYSTICK_BUTTON_ISR_REGISTER);
	
	// Enables global interrupts
	sei();
}