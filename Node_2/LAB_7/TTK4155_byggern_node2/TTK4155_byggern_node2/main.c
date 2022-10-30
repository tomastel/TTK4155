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
#include "ADC/ADC_IR.h"

#define CAN_BAUDRATE_REG 0x290165

void inits(){
	SystemInit();
	LEDs_init();
	configure_uart();	
	can_init_def_tx_rx_mb(CAN_BAUDRATE_REG);
	PWM_init();
	ADC_init();
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	printf("Program initialized\n\r");
}

void func()
{
	printf("Running test func\n\r");
	reset_btn_value();
	
}

int main(void)
{

	inits();
	CAN_MESSAGE btn_message, ADC_message;
	PWM_set_period_percentage(0);
	
    while (1)
    {
		uint32_t sys_tick_CTRL_reg = SysTick->CTRL;
		bool time_flag = (sys_tick_CTRL_reg & 0x10000);
		
		if(time_flag){
			btn_message = can_get_messages(1);
			ADC_message = can_get_messages(0);
			int8_t x_val = ADC_message.data[0];
			//printf("%d, %d, %d \n\r\n", x_val, ADC_message.data[1], ADC_message.data[2]);
			if(btn_message.data[0] == 1){
				func();
			}
			int8_t value = ADC_message.data[0];
			//printf("value: %d\r\n", value);
			PWM_set_period_percentage(value);
			
			uint32_t val = ADC->ADC_CDR[7];
			uint32_t last_converted = ADC->ADC_LCDR;
			uint32_t ADC_status_reg = (ADC->ADC_CHSR & ADC_CHSR_CH15) >> 15;
	
			//printf("Value: %d , last: %d\r\n", val, last_converted);
			
			if(IR_check_for_goal()){
				printf("SIIUUUUUUU\n\r");
			}
			SysTick->VAL = 0;
			
		}
		
		
    }
}