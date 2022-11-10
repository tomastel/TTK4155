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
#include "../MISC/prints.h"

typedef struct{
	uint16_t ID;
	uint8_t length; // Length in bytes
	char message[8];
}CAN_msg;

int8_t CAN_init();
int8_t CAN_send(CAN_msg msg);
CAN_msg CAN_receive(uint8_t buffer);
void CAN_interpret_status(uint8_t status);

#endif /* CANDRV_H_ */
