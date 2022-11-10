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
#define MAX_SUBMENUS 4 // If >6, data memory usage > 100%
#define MENU_OPTION_MAX_STRING_LENGTH 24

#include <string.h>
#include "../MISC/common_includes.h"
#include "oled_drv.h"
#include "../ADC/adc_drv.h"



typedef struct
{
	char option_name[MENU_OPTION_MAX_STRING_LENGTH];
	void(*callback)(void*);
	void *callback_parameter;
	
}option_struct;

typedef struct
{
	char title[MENU_OPTION_MAX_STRING_LENGTH];
	option_struct submenu[MAX_SUBMENUS];
	int options;
	
}menu_struct;

void end_game();

void increment_score();

void increment_goal_limit();

void decrement_goal_limit();

void print_menu_page();

void start_game_menu (void *menu_page);

void update_menu(void *menu_page);

void update_options(void *menu_page);

void menu_navigate();

void print_arrow();

void clear_arrow();

void move_arrow_up();

void move_arrow_down();

void enter();

void menu_init();

#endif /* MENU_H_ */