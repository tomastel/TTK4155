#ifndef PRINTS_H_
#define PRINTS_H_

#include "common_includes.h"
#include "../UART_drv/UARTdrv.h"
#include "../OLED/oled_drv.h"


void print_oled(char* string);
void print_uart(char* string);
void print_both(char* string);

#endif /* PRINTS_H_ */