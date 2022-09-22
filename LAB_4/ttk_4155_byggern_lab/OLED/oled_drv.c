/*
 * oled_drv.c
 *
 * Created: 22.09.2022 10:09:07
 *  Author: haavarok
 */ 

#include "oled_drv.h"

void oled_write_cmd(char command)
{
	volatile char *oled_cmd_reg = (char *) 0x1000;
	oled_cmd_reg[0] = command;
}

void oled_init()
{
	oled_write_cmd(0xae); // display off
	oled_write_cmd(0xa1); //segment remap
	oled_write_cmd(0xda); //common pads hardware: alternative
	oled_write_cmd(0x12);
	oled_write_cmd(0xc8); //common output scan direction:com63~com0
	oled_write_cmd(0xa8); //multiplex ration mode:63
	oled_write_cmd(0x3f);
	oled_write_cmd(0xd5); //display divide ratio/osc. freq. mode
	oled_write_cmd(0x80);
	oled_write_cmd(0x81); //contrast control
	oled_write_cmd(0xFF);
	oled_write_cmd(0xd9); //set pre-charge period
	oled_write_cmd(0x21);
	oled_write_cmd(0x20); //Set Memory Addressing Mode (Horizontal)
	oled_write_cmd(0x00);
	oled_write_cmd(0xdb); //VCOM deselect level mode
	oled_write_cmd(0x30);
	oled_write_cmd(0xad); //master configuration
	oled_write_cmd(0x00);
	oled_write_cmd(0xa4); //out follows RAM content
	oled_write_cmd(0xa6); //set normal display
	oled_write_cmd(0xaf); // display on
}

void oled_reset()
{
	
}

void oled_home()
{
	
}

void oled_goto_line(/*line*/)
{
	
}

void oled_clear_line(/*line*/)
{
	
}

void oled_pos(/*row, column*/)
{
	
}

void oled_write_data(char data) // Volatile
{
	volatile char *oled_data_reg = (char *) 0x1200;
	oled_data_reg[0] = data;
}

void oled_print(/*char**/)
{
	
}

void oled_set_brightness(uint8_t lvl_percent)
{
	uint8_t lvl = lvl_percent * 255 / 100 + 1;
	oled_write_cmd(0x81); //contrast control
	oled_write_cmd(lvl);
}





