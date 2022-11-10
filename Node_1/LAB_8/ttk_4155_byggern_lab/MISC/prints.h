#ifndef PRINTS_H_
#define PRINTS_H_

#include "common_includes.h"
#include "../UART_drv/UARTdrv.h"
#include "../OLED/oled_drv.h"

static FILE stdout_oled = FDEV_SETUP_STREAM(oled_print, NULL, _FDEV_SETUP_WRITE);
static FILE stdout_uart = FDEV_SETUP_STREAM(USART_Transmit, USART_Receive, _FDEV_SETUP_RW);

void print_oled(char* string);
void print_uart(char* string);
void print_both(char* string);

#endif /* PRINTS_H_ */
