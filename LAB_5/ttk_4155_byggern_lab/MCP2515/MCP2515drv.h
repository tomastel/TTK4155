/*
 * MCP2515drv.h
 *
 * Created: 06.10.2022 10:22:03
 *  Author: haavarok
 */ 


#ifndef MCP2515DRV_H_
#define MCP2515DRV_H_

#include "../MISC/common_includes.h"
#include "MCP2515_registers.h"
#include "../SPI/SPIdrv.h"
#include "../MISC/prints.h"

#define MCP_FOSC 16E6
#define MCP_TXRTS_CONF 0x07
#define MCP_BRP 0

int8_t MCP2515_init();

uint8_t MCP2515_read(uint8_t read_register);

void MCP2515_write(uint8_t write_register, uint8_t data);

void MCP2515_request_to_send(uint8_t buffer);

void MCP2515_bit_modify(uint8_t write_register, uint8_t mask, uint8_t data);

void MCP2515_reset();

uint8_t MCP2515_read_status();


#endif /* MCP2515DRV_H_ */