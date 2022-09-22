/*
 * oled_drv.h
 *
 * Created: 22.09.2022 10:09:26
 *  Author: haavarok
 */ 


#ifndef OLED_DRV_H_
#define OLED_DRV_H_

#include "../MISC/common_includes.h"

#define OLED_RES 1024

void oled_write_cmd(char command);

void oled_init();

void oled_reset();

void oled_home();

void oled_goto_line(/*line*/);

void oled_clear_line(/*line*/);

void oled_pos(/*row, column*/);

void oled_write_data(char data); // Volatile

void oled_print(/*char**/);

void oled_set_brightness(uint8_t lvl_percent);

void oled_testingtesting();

#endif /* OLED_DRV_H_ */