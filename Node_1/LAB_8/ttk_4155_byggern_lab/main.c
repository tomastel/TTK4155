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
	print_uart("Program initialized\r\n");
}

ISR (TIMER3_COMPA_vect) {
	if(adc_drv_joystick_update() || right_slider_update()) {
		fun_stick_t my_fun_stick = adc_drv_fun_stick_get();
		uint8_t right_slider_val = right_slider_get();
		CAN_msg fun_stick_CAN_msg = {
			.ID = 1,
			.length = 3,
			.message = {my_fun_stick.position.X, right_slider_val, my_fun_stick.direction}
		};
		CAN_send(fun_stick_CAN_msg);
	}
}

int main(void)
{
	init();
	
    while (1){
		menu_navigate();
    }
	return 0;
}
