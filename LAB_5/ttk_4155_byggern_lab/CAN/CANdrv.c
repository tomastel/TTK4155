/*
 * CANdrv.c
 *
 * Created: 06.10.2022 10:21:28
 *  Author: haavarok
 */ 

#include "CANdrv.h"

ISR (INT0_vect)
{
	print_uart("CAN-controller interrupt\r\n");
}

void CAN_init()
{
	// configure PD2 as input
	clear_bit(DDRD, CAN_INTERRUPT_PIN);
	// Disable global interrupts
	cli();
	// Configure interrupt rising edge
	set_bit(GICR, CAN_INTERRUPT_ISR_REGISTER);
	// Enable global interrupts
	sei();
	
}

void CAN_send(CAN_msg msg)
{
	uint8_t ID_MSB = (0x7F8 & msg.ID) >> 3;
	uint8_t ID_LSB = (0x7 & msg.ID);
	uint8_t TXB_bytes = pow(2, msg.length) - 1;
	
	MCP2515_write(MCP_TXB0SIDH, ID_MSB);
	MCP2515_write(MCP_TXB0SIDL, ID_LSB);
	MCP2515_write(MCP_TXB0EID8, msg.length);
	
	for(uint8_t i = 0; i < msg.length; i++)
	{
		MCP2515_write(MCP_TXB0D0+1, msg.message[i]);
	}
	
	MCP2515_request_to_send(MCP_RTS_TX0);
}
