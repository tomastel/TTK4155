
#include "prints.h"

void print_oled(char* string)
{
	stdout = &stdout_oled;
	printf(string);
	
}void print_uart(char* string)
{
	stdout = &stdout_uart;
	printf(string);
}

void print_both(char* string)
{
	stdout = &stdout_oled;
	printf(string);
	
	stdout = &stdout_uart;
	printf(string);
	printf("\r\n");
}
