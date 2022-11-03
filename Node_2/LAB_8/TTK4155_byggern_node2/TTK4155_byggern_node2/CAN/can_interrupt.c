/*
 * interrupt.c
 *
 * Author: Gustav O. Often and Eivind H. J�lsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 

#include "can_interrupt.h"

#include <stdio.h>
#include "sam.h"

#include "../uart_and_printf/printf.h"

#include "can_controller.h"

#define DEBUG_INTERRUPT 0
#define DEBUG_INTERRUPT_2 0


#define CAN_MESSAGE_ARRAY_SIZE 2

CAN_MESSAGE can_messages[CAN_MESSAGE_ARRAY_SIZE];

/**
 * \brief CAN0 Interrupt handler for RX, TX and bus error interrupts
 *
 * \param void
 *
 * \retval 
 */
void CAN0_Handler( void )
{
	if(DEBUG_INTERRUPT)printf("CAN0 interrupt\n\r");
	char can_sr = CAN0->CAN_SR; 
	
	//RX interrupt
	if(can_sr & (CAN_SR_MB1 | CAN_SR_MB2) )//Only mailbox 1 and 2 specified for receiving
	{
		CAN_MESSAGE message;
		if(can_sr & CAN_SR_MB1)  //Mailbox 1 event
		{
			can_receive(&message, 1);

		}
		else if(can_sr & CAN_SR_MB2) //Mailbox 2 event
		
		{
			can_receive(&message, 2);
		}
		else
		{
			printf("CAN0 message arrived in non-used mailbox\n\r");
		}
		uint8_t id = message.id;
		can_messages[id -1].id = message.id;
		can_messages[id -1].data_length = message.data_length;
		if(DEBUG_INTERRUPT_2) {
			printf("ID: %d\n\r", id);
			printf("Length: %d \n\r", message.data_length);
		}
		for (int i = 0; i < can_messages[id -1].data_length; i++) {
			can_messages[id -1].data[i] = message.data[i];
			int8_t data = can_messages[id -1].data[i];
			if(DEBUG_INTERRUPT_2)printf("data %d: %d\n\r",i, data);
		}
		
		if(DEBUG_INTERRUPT)printf("message id: %d\n\r", message.id);
		if(DEBUG_INTERRUPT)printf("message data length: %d\n\r", message.data_length);
		for (int i = 0; i < message.data_length; i++)
		{
			int8_t value = message.data[i];
			if(DEBUG_INTERRUPT)printf("%d ", value);
		}
		if(DEBUG_INTERRUPT)printf("\n\r");
	}
	
	if(can_sr & CAN_SR_MB0)
	{
		if(DEBUG_INTERRUPT) printf("CAN0 MB0 ready to send \n\r");
		
	//Disable interrupt
		CAN0->CAN_IDR = CAN_IER_MB0;

	}

	if(can_sr & CAN_SR_ERRP)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 ERRP error\n\r");

	}
	if(can_sr & CAN_SR_TOVF)
	{
		if(DEBUG_INTERRUPT)printf("CAN0 timer overflow\n\r");

	}
	if(DEBUG_INTERRUPT)printf("\n\r");
	NVIC_ClearPendingIRQ(ID_CAN0);
	//sei();*/
}

CAN_MESSAGE can_get_messages(uint8_t msg_nr)
{
	return can_messages[msg_nr];
}

void reset_btn_value()
{
	can_messages[1].data[0] = 0;
}
