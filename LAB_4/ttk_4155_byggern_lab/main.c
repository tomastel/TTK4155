/*
 * ttk_4155_byggern_lab.c
 *
 * Created: 01.09.2022 09:02:45
 * Author : HOK, KH, TT
 */ 

#define F_CPU 4.9152E6

//#include <avr/io.h>
//#include <stdio.h>

#include "UARTdrv.h"
#include "SRAM/SRAMdrv.h"
#include "ADC/adc_drv.h"
#include "MISC/ext_button_drv.h"
#include "OLED/oled_drv.h"


int main(void){
	pos_t joystick_pos;
	dir_t joystick_dir;
	uint8_t slider1, slider2;
	USART_drv_init(MYUBRR);
	SRAM_init();
	adc_drv_init();
	ext_button_drv_init();
	adc_calibrate();
	oled_init();
	//oled_write_data(0b00011000);
	//oled_write_data(0b00011000);
	//oled_write_data(0b01111110);
	//oled_write_data(0b00111100);
	//oled_write_data(0b00011000);

    while (1){
		
		printf("----------------------------------\r\n");
		joystick_pos = pos_read();
		joystick_dir = dir_read(joystick_pos);
		slider1 = slider_read(LEFT_SLIDER_CHANNEL);
		slider2 = slider_read(RIGHT_SLIDER_CHANNEL);
		printf("X: %d\r\n", joystick_pos.X);
		printf("Y: %d\r\n", joystick_pos.Y);
		printf("Joystick direction: %d\r\n", joystick_dir);
		printf("Left slider: %d\r\n", slider1);
		printf("Right slider: %d\r\n", slider2);
		printf("----------------------------------\r\n");
		oled_write_data(0b00011000);
		oled_write_data(0b00011000);
		oled_write_data(0b01111110);
		oled_write_data(0b00111100);
		oled_write_data(0b00011000);
		_delay_ms(100);
		
		
    }
	
	return 0;
}
