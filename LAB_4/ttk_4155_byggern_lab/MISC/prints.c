#include "prints.h"

static FILE stdout_oled = FDEV_SETUP_STREAM(oled_print, NULL, _FDEV_SETUP_WRITE);
static FILE stdout_uart = FDEV_SETUP_STREAM(USART_Transmit, USART_Receive, _FDEV_SETUP_RW);


void print_oled(char* string){
	stdout = &stdout_oled;
	printf(string);
	
}void print_uart(char* string){
	stdout = &stdout_uart;
	printf(string);
}

void print_both(char* string){
	stdout = &stdout_oled;
	printf(string);
	
	stdout = &stdout_uart;
	printf(string);
	printf("\r\n");
}