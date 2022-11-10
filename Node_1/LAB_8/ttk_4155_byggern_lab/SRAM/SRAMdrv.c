/*
 * ttk_4155_byggern_lab.c
 *
 * Created: 01.09.2022 09:02:45
 * Author : HOK, KH, TT
 */ 

#include "SRAMdrv.h"

void SRAM_init(){
	MCUCR |= (1 << SRE); //External memory enable
	SFIOR |= (1 << XMM2); // Masking PC7-PC4 for JTAG interface
}

void latch_test(){
	PORTE |= (1 << PE1);
	PORTA = 0xAA;
	_delay_ms(5000);
	PORTE &= ~(1 << PE1);
	_delay_ms(10000);
	PORTA = 0x55;
	_delay_ms(10000);
	PORTE |= (1 << PE1);
	_delay_ms(10000);
}
