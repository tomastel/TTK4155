/*
 * ttk_4155_byggern_lab.c
 *
 * Created: 01.09.2022 09:02:45
 * Author : HOK, KH, TT
 */ 

#define F_CPU 4.9152E6

//#include <avr/io.h>
//#include <stdio.h>

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
	menu_init();
	MCP2515_init();
}

int main(void)
{
	pos_t joystick_pos;
	dir_t joystick_dir;
	uint8_t slider1, slider2;

	init();

    while (1){
		_delay_ms(3000);
		menu_navigate();
		MCP2515_write(0x00, 0x6B);	
    }
	
	return 0;
}
