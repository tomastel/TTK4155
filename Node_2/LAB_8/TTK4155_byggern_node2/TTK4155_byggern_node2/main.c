/*
 * TTK4155_byggern_node2.c
 *
 * Created: 13.10.2022 10:17:31
 * Author : tomasnt
 */ 

//#include "sam.h"
#include "misc/common_includes.h"
#include "misc/LED_blink.h"
#include "uart_and_printf/uart.h"
#include "CAN/can_controller.h"
#include "CAN/can_interrupt.h"
#include "PWM/PWM_drv.h"
#include "ADC/ADC_IR.h"
#include "motor_box/motor.h"
#include "timer/timer_counter.h"
#include "Solenoid/Solenoid.h"
#include "PID/PID.h"

// to do: 
//			Fix encoder
//			Fix PID

#define CAN_BAUDRATE_REG 0x290165

pidData_t pid_instance_1;

void inits(){
	SystemInit();
	timer_counter_init();
	LEDs_init();
	configure_uart();	
	can_init_def_tx_rx_mb(CAN_BAUDRATE_REG);
	PWM_init();
	ADC_init();
	motor_box_init();
	solenoid_init();
	pid_Init(6,3,0, &pid_instance_1);
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	printf("Program initialized\n\r");
}

void func()
{
	solenoid_impulse();
	printf("Running test func\n\r");
	reset_btn_value();
	
}

void TC0_Handler ( void )
{
	//CAN_MESSAGE ADC_DATA = can_get_messages(0);
	//printf("TC0_ch0 Handler says DOINK!\n\r");
	//pid_Controller(ADC_DATA.data[1],)
	int16_t encoder_val = encoder_read();
	
	printf("Encoder value: %d\n\r", encoder_val);
	int16_t value = pid_Controller(30, encoder_val, &pid_instance_1);
	printf("output: %d\n\r",value);
	motor(value);
	uint32_t tc_sr = TC0->TC_CHANNEL[0].TC_SR;
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
			
			uint8_t slider_val = ADC_message.data[1];
			//motor(slider_val);
			
			
			SysTick->VAL = 0;
		}
		
		
    }
}