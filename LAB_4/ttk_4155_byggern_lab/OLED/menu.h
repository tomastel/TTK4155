/*
 * menu.h
 *
 * Created: 29.09.2022 12:27:21
 *  Author: tomasnt
 */ 


#ifndef MENU_H_
#define MENU_H_

#define FIRST_LINE_MENU 1
#define LAST_LINE_MENU 7
#define OPTIONS_MAIN_MENU 7
#define MAX_SUBMENUS 7
#define MENU_OPTION_MAX_STRING_LENGTH 24

#include <string.h>
#include "../MISC/common_includes.h"
#include "oled_drv.h"
#include "../ADC/adc_drv.h"

typedef struct  
{
	char title[MENU_OPTION_MAX_STRING_LENGTH];
	uint8_t num_options;
	void (*command)();
	//const char options[num_options][MENU_OPTION_MAX_STRING_LENGTH];
	struct menu_struct* submenu[MAX_SUBMENUS];
	//struct menu_struct *parent_menu;
	
}menu_struct;

void this_end();

void enter();

void enter_menu(menu_struct* menu);

void menu_init();

void menu_print(int screen);

void main_menu_print();

void menu_navigate();

void menu_option_value_enter();

void print_arrow();

void clear_arrow();

void move_arrow_up();

void move_arrow_down();


#endif /* MENU.C_H_ */