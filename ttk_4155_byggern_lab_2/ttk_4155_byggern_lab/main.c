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


int main(void){
	USART_drv_init(MYUBRR);
	SRAM_init();
	adc_drv_init();
	ext_button_drv_init();

    while (1){
		
		printf("----------------------------------\r\n");
		printf("Left slider: %d \r\n", adc_read(0));
		//printf("Right slider: %d\r\n",adc_read(1));
		//printf("Joystick y: %d\r\n",adc_read(2));
		//printf("Joystick x: %d\r\n",adc_read(3));//something wrong with this
		printf("----------------------------------\r\n");
		_delay_ms(2000);
		
		
    }
	
	return 0;
}
