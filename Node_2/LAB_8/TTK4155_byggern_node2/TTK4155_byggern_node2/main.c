/*
 * TTK4155_byggern_node2.c
 *
 * Created: 13.10.2022 10:17:31
 * Author : tomasnt
 */ 

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

#define PID_DEBUG 0

#define CAN_BAUDRATE_REG 0x290165
#define ENCODER_MAX_VAL 1405
#define Kp 64
#define Ti 0
#define Td 64

CAN_MESSAGE goal_message = {
	.id = 3,
	.data_length = 1,
	.data = {1}
	};

pidData_t pid_instance_1;
bool time_flag;

void inits(){
	SystemInit();
	timer_counter_init();
	configure_uart();	
	can_init_def_tx_rx_mb(CAN_BAUDRATE_REG);
	PWM_init();
	ADC_init();
	motor_box_init();
	solenoid_init();
	pid_Init(Kp, Ti, Td, &pid_instance_1);
	WDT->WDT_MR = WDT_MR_WDDIS;
	timer_ch0_start();
	printf("Program initialized\n\r");
}


void TC0_Handler (void)
{
	time_flag = true;	
	uint32_t tc_sr0 = TC0->TC_CHANNEL[0].TC_SR;
}

int main(void)
{
	inits();
	
	CAN_MESSAGE btn_message, ADC_message, start_game_message;
	uint8_t start_game_bit;
	int8_t x_val, servo_value;
	uint16_t slider_val_mapped;
	int16_t encoder_val, pid_output;
	
	PWM_set_period_percentage(0);
	
    while (1)
    {
		start_game_message = can_get_messages(2);
		start_game_bit = start_game_message.data[0];
		if(start_game_bit) {
			if(time_flag){
				ADC_message = can_get_messages(0);
				btn_message = can_get_messages(1);
	
				x_val = ADC_message.data[0];
				if(btn_message.data[0] == 1){
					solenoid_impulse();
					reset_btn_value();
					reset_IR();	
				}
			
				if (IR_check_for_goal()) {
					can_send(&goal_message, 0);
					//printf("SIIIU\n\r");
				}
			
				servo_value = ADC_message.data[0];
				PWM_set_period_percentage(servo_value);
			
				slider_val_mapped = ADC_message.data[1]*ENCODER_MAX_VAL/100;
				encoder_val = encoder_read();
				pid_output = pid_Controller(slider_val_mapped, encoder_val, &pid_instance_1);
	
				motor(pid_output);
				
				if(PID_DEBUG) printf("Encoder value: %d\n\r PID output: %d\n\r", encoder_val, pid_output);

				time_flag = false;
			}
		}
	}
}