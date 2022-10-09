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


void init(){
	USART_drv_init(MYUBRR);
	SRAM_init();
	adc_drv_init();
	ext_button_drv_init();
	adc_calibrate();
	oled_init();
	//menu_init();
	CAN_init();
}

int main(void)
{
	pos_t joystick_pos;
	dir_t joystick_dir;
	uint8_t slider1, slider2;

	init();
	
	CAN_msg CAN_test = {
		.ID = 818,
		.length = 8,
		.message = {65, 66, 67, 68, 69, 70, 71, 72}
	};

    while (1){
		CAN_send(CAN_test);
		_delay_ms(3000);
		//uint8_t bla = MCP2515_read(MCP_RXF0SIDL);
    }
	
	return 0;
}
