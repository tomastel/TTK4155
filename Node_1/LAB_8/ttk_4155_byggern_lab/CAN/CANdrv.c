/*
 * CANdrv.c
 *
 * Created: 06.10.2022 10:21:28
 *  Author: haavarok
 */ 

#include "CANdrv.h"
#include "../OLED/menu.h"

#define CAN_INTERRUPT_ISR_REGISTER INT0
#define CAN_INTERRUPT_PIN PD2

static uint8_t CANINT_status;
CAN_msg IR_Data;

ISR (INT0_vect)
{
	CAN_interpret_status(MCP2515_read_status());
}

int8_t CAN_init()
{
	// configure PD2 as input
	clear_bit(DDRD, CAN_INTERRUPT_PIN);
	// Disable global interrupts
	cli();
	// Enable interrupt INT0
	set_bit(GICR, CAN_INTERRUPT_ISR_REGISTER);
	// Configure interrupt falling edge
	set_bit(MCUCR, ISC01);
	clear_bit(MCUCR, ISC00);
	// Enable global interrupts
	sei();
	
	int8_t err = MCP2515_init();
	if (err < 0) {
		print_uart("error");
		return err;
	}
	return 0;
}

int8_t CAN_send(CAN_msg msg)
{
	uint8_t ID_MSB = (0x7F8 & msg.ID) >> 3;
	uint8_t ID_LSB = (0x7 & msg.ID) << 5;
	
	MCP2515_write(MCP_TXB0SIDH, ID_MSB);
	MCP2515_write(MCP_TXB0SIDL, ID_LSB);
	MCP2515_write(TXB0DLC, msg.length);
	
	uint8_t buff0_status = MCP2515_read(MCP_TXB0CTRL);
	if((buff0_status & 0x8) != 0x8) {
		if (msg.length > 8) {
			msg.length = 8;
		}
		for(uint8_t i = 0; i < msg.length; i++)
		{
			MCP2515_write(MCP_TXB0D0+i, msg.message[i]);
		}
		MCP2515_request_to_send(MCP_RTS_TX0);
		return 0;
	} else {
		print_uart("Buffer0 not available\r\n");
		return -1;
	}
}

CAN_msg CAN_receive(uint8_t buffer)
{
	CAN_msg rx_msg;
	uint8_t ID_MSB;
	uint8_t ID_LSB;
	uint8_t length;
	
	if (buffer == 0) {
		ID_MSB = MCP2515_read(MCP_RXB0SIDH);
		ID_LSB = MCP2515_read(MCP_RXB0SIDL);
		
		ID_LSB = (ID_LSB & 0xE0) >> 5;
		rx_msg.ID = ID_MSB << 3;
		rx_msg.ID = (rx_msg.ID & 0x7F8) | (ID_LSB & 0x7);
		
		length = MCP2515_read(MCP_RXB0DLC);
		rx_msg.length = (length & 0xF);
		if (rx_msg.length > 8) {
			rx_msg.length = 8;
		}
		
		for (uint8_t i=0; i < rx_msg.length; i++) {
			rx_msg.message[i] = MCP2515_read(MCP_RXB0D0 + i);
			char *temp_msg = rx_msg.message[i];
			print_uart(&temp_msg);
		}
		print_uart("\r\n");
		
		if (rx_msg.ID == 3) {
			increment_score();
		}
	}
	return rx_msg;
}

void CAN_interpret_status(uint8_t status)
{
	uint8_t buffer;
	
	if (status & rx_buff_0_full) {
		buffer = 0;
		CAN_receive(buffer);
		print_uart("RX0 Full\r\n");
	}

	if (status & rx_buff_1_full) {
		buffer = 1;
		CAN_receive(buffer);
		print_uart("RX1 Full\r\n");
	}

	if (status & tx_buff_0_busy) {
		buffer = 0;
		// Something is about to go down
		print_uart("TX0 Busy\r\n");
	}

	if (status & tx_buff_0_empty) {
		buffer = 0;
		// Something else happens
		print_uart("TX0 Empty\r\n");
	}
	MCP2515_write(MCP_CANINTF, 0x00);
}
