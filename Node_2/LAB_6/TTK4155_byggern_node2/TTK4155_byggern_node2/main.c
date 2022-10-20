/*
 * TTK4155_byggern_node2.c
 *
 * Created: 13.10.2022 10:17:31
 * Author : tomasnt
 */ 

#include "sam.h"
#include "misc/common_includes.h"
#include "misc/LED_blink.h"
#include "uart_and_printf/uart.h"
#include "CAN/can_controller.h"
#include "CAN/can_interrupt.h"

#define CAN_BAUDRATE_REG 0x290165

void inits(){
	SystemInit();
	LEDs_init();
	configure_uart();	
	can_init_def_tx_rx_mb(CAN_BAUDRATE_REG);	
}

int main(void)
{
	
	inits();
	printf("dsadsa\n\r");
	CAN_MESSAGE CAN_test = {
		.id = 818,
		.data_length = 8,
		.data = {77, 101, 108, 100, 105, 110, 103, 33}
	};
	//WDT->WDT_MR = WDT_MR_WDDIS; 
	can_send(&CAN_test, 0);
    while (1) 
    {
		
		LEDs_blink();
    }
}