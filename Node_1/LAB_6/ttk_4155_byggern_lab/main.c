/*
 * ttk_4155_byggern_lab.c
 *
 * Created: 01.09.2022 09:02:45
 * Author : HOK, KH, TT
 */ 

#define F_CPU 4.9152E6

#include "UART_drv/UARTdrv.h"
#include "SRAM/SRAMdrv.h"
#include "ADC/adc_drv.h"
#include "MISC/ext_button_drv.h"
#include "OLED/oled_drv.h"
#include "MISC/prints.h"
#include "MCP2515/MCP2515drv.h"
#include "CAN/CANdrv.h"
#include "MISC/timer_counter.h"

void init() {
	USART_drv_init(MYUBRR);
	SRAM_init();
	adc_drv_init();
	ext_button_drv_init();
	adc_calibrate();
	oled_init();
	menu_init();
	CAN_init();
	timer_init();
}

ISR (TIMER3_COMPA_vect) {
	if(adc_drv_joystick_update()){
		fun_stick_t my_fun_stick = adc_drv_fun_stick_get();
		CAN_msg fun_stick_CAN_msg = {
			.ID = 69,
			.length = 3,
			.message = {my_fun_stick.position.X, my_fun_stick.position.Y, my_fun_stick.direction}
		};
		CAN_send(fun_stick_CAN_msg);
		print_uart("Joystick sent\n\r");
	}
}

int main(void)
{
	//fun_stick_t my_fun_stick;
	uint8_t slider1, slider2;

	init();
	print_uart("Program initialized\r\n");
	
	CAN_msg CAN_test = {
		.ID = 818,
		.length = 8,
		.message = {77, 101, 108, 100, 105, 110, 103, 33}
	};
	
    while (1){
		//_delay_ms(100);
		menu_navigate();
    }
	
	return 0;
}
