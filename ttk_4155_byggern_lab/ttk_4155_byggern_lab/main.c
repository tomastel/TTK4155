/*
 * ttk_4155_byggern_lab.c
 *
 * Created: 01.09.2022 09:02:45
 * Author : HOK, KH, TT
 */ 

#define F_CPU 4.9152E6
//#define BAUD 9600
//#define MYUBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "UARTdrv.h"



//void USART_Flush();

int main(void){
	USART_drv_init(MYUBRR);
	//DDRB = 0xFF;
    while (1){
		//PORTB |= (1 << PB0);
		unsigned char my_char = 0x00;
		my_char = USART_Receive();
		if (my_char != 0x00){
		USART_Transmit(my_char);
		}
		//PORTB &= ~(1 << PB0);

    }
	
	return 0;
}

