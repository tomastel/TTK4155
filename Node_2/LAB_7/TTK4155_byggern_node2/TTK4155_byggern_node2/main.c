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
#include "PWM/PWM_drv.h"

#define CAN_BAUDRATE_REG 0x290165

void inits(){
	SystemInit();
	LEDs_init();
	configure_uart();	
	can_init_def_tx_rx_mb(CAN_BAUDRATE_REG);
	PWM_init();
	WDT->WDT_MR = WDT_MR_WDDIS;
}

int main(void)
{
	//Set PMC timer, this has to be checked
	PMC->PMC_WPMR = PMC_WPMR_WPKEY_PASSWD;
	PMC->PMC_WPMR = 0;
	PMC->PMC_PCER0 = 0xFFFF;
	PMC->PMC_PCER1 = 0xFFFF;
	inits();
	printf("Program initialized\n\r");
	CAN_MESSAGE CAN_test = {
		.id = 818,
		.data_length = 8,
		.data = {77, 101, 108, 100, 105, 110, 103, 33}
	};
	uint32_t my_reg = PWM->PWM_SR;
	printf("this reg: %d \r\n", my_reg);
	can_send(&CAN_test, 0);
	
    while (1) 
    {
		LEDs_blink();
    }
}