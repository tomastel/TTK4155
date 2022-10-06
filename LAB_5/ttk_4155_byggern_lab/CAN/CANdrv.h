/*
 * CANdrv.h
 *
 * Created: 06.10.2022 10:21:37
 *  Author: haavarok
 */ 


#ifndef CANDRV_H_
#define CANDRV_H_

#include "../MISC/common_includes.h"
#include "../MCP2515/MCP2515drv.h"

#define CAN_INTERRUPT_ISR_REGISTER INT0
#define CAN_INTERRUPT_PIN PD2

typedef struct{
	uint16_t ID;
	uint8_t length; // Length in bytes
	char *message[8];
}CAN_msg;

void CAN_init();

void CAN_send(CAN_msg msg);

void CAN_receive();

//CAN_msg CAN_read();



#endif /* CANDRV_H_ */