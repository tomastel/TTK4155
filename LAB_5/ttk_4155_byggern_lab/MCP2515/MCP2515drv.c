/*
 * MCP2515drv.c
 *
 * Created: 06.10.2022 10:22:14
 *  Author: haavarok
 */ 

#include "MCP2515drv.h"

int8_t MCP2515_init()
 {
	 int value;
	 SPI_init(); // Initialize SPI
	 MCP2515_reset(); // Send reset - command
	 // Self - test
	 value = MCP2515_read(MCP_CANSTAT);
	 if ((value & MODE_MASK) != MODE_CONFIG){
		 print_uart("MCP2515 is NOT in configuration mode after reset!\r\n");
		 return -1;
	 }
	 
	 MCP2515_write(MCP_TXRTSCTRL, MCP_TXRTS_CONF);
	 
	 // Receive buffer0 config: receive all messages, no overflow to RXB1.
	 MCP2515_bit_modify(MCP_RXB0CTRL, 0x60, 0x60);
	 value = MCP2515_read(MCP_RXB0CTRL);
	 if (value != 0x60){
		 print_uart("Receive buffer 0 config incorrect!\r\n");
		 return -2;
	 }
	 
	 // Receive buffer1 config: receive all messages.
	 MCP2515_bit_modify(MCP_RXB1CTRL, 0x60, 0x60);
	 value = MCP2515_read(MCP_RXB1CTRL);
	 print_uart(value);
	 if (value != 0x60){
		 print_uart("Receive buffer 1 config incorrect!\r\n");
		 return -3;
	 }	 
	 
	 // Interrupt config: msg error, error flag change, TX0 empty, RX0 full
	 //MCP2515_bit_modify(MCP_CANINTE, 0xFF, 0xA5);
	 MCP2515_bit_modify(MCP_CANINTE, 0xFF, 0x5);
	 value = MCP2515_read(MCP_CANINTE);
	 if (value != 0x5){
		 print_uart("Interrupt config incorrect!\r\n");
		 return -4;
	 } 
	 
	 MCP2515_write(MCP_CANCTRL, MODE_LOOPBACK);
	 // Self - test
	 value = MCP2515_read(MCP_CANSTAT);
	 if ((value & MODE_MASK) != MODE_LOOPBACK){
		 print_uart(" MCP2515 is NOT in loopback mode!\n");
		 return -5;
	 }

	 return 0;
 }


uint8_t MCP2515_read(uint8_t read_register)
{
	uint8_t result;
	
	clear_bit(PORTB, PB4);
	
	SPI_write(MCP_READ);
	SPI_write(read_register);
	result = SPI_read();
	
	set_bit(PORTB, PB4);
	
	return result;
}

void MCP2515_write(uint8_t write_register, uint8_t data)
{
	clear_bit(PORTB, PB4);

	SPI_write(MCP_WRITE);
	SPI_write(write_register);
	SPI_write(data);

	set_bit(PORTB, PB4);
}

void MCP2515_request_to_send(uint8_t buffer)
{
	clear_bit(PORTB, PB4);
	SPI_write(buffer);
	set_bit(PORTB, PB4);
}

void MCP2515_bit_modify(uint8_t write_register, uint8_t mask, uint8_t data)
{
	clear_bit(PORTB, PB4);
	
	SPI_write(MCP_BITMOD);
	SPI_write(write_register);
	SPI_write(mask);
	SPI_write(data);
	
	set_bit(PORTB, PB4);
}

void MCP2515_reset()
{
	clear_bit(PORTB, PB4);
	SPI_write(MCP_RESET);
	set_bit(PORTB, PB4);
}

uint8_t MCP2515_read_status()
{
	uint8_t data;
	
	clear_bit(PORTB, PB4);
	SPI_write(MCP_READ_STATUS);
	data = SPI_read();
	data = SPI_read();
	set_bit(PORTB, PB4);
	
	return data;
}