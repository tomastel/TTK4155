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

int main(void){
	USART_drv_init(MYUBRR);
	SRAM_init();
	//DDRB = 0xFF;
	SRAM_test();
    while (1){
		//PORTB |= (1 << PB0);
		//_delay_ms(500);
		//PORTB &= ~(1 << PB0);
		// _delay_ms(500);
		
		//unsigned char my_char = 0x00;
		//my_char = USART_Receive();
		//if (my_char != 0x00){
		//USART_Transmit(my_char);
		//}
		//printf("Hei, hallo");
		
		//latch_test();
		
		
    }
	
	return 0;
}
