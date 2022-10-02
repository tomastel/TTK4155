#include "menu.h"

static uint8_t num_options_in_menu;
static uint8_t arrow_on_line;


static menu_struct *current_menu;


menu_struct Sub_menu_2 = {
	.title = "Sub Menu 2",
	.submenu = {
		{ .option_name = "Action 1", .callback = &that_end },
		{ .option_name = "Back", .callback = &update_menu }
	},
	.options = 2
};

menu_struct Sub_menu_1 = {
	.title = "Sub Menu 1",
	.submenu = {
		{ .option_name = "Action 1", .callback = &this_end },
		{ .option_name = "Back", .callback = &update_menu }
	},
	.options = 2
};

menu_struct main_menu = {
	.title = "Main Menu",
	.submenu = {
		{ .option_name = "Sub Menu 1", .callback = &update_menu},
		{ .option_name = "Sub Menu 2", .callback = &update_menu}
	},
	.options = 2
};


void this_end()
{
	print_uart("hei \r\n");
}

void that_end()
{
	print_uart("hallo \r\n");
}

void print_menu_page()
{
	char *menu_page_title = current_menu->title;
	oled_reset();
	oled_goto_line(0);
	oled_goto_column(40);
	print_oled(menu_page_title);
	
	for(uint8_t i = 0; i < current_menu->options; i++)
	{
		char *option = current_menu->submenu[i].option_name;
		oled_goto_line(i+1);
		oled_goto_column(8);
		print_oled(option);
	}
	
	oled_pos(FIRST_LINE_MENU, 0);
	print_arrow();
	arrow_on_line = FIRST_LINE_MENU;
	
}

void update_menu(void *menu_page)
{
	menu_struct *temp_menu_page = menu_page;
	current_menu = temp_menu_page;
	num_options_in_menu = temp_menu_page->options;
	print_menu_page();
}

void menu_navigate()
{	
	static dir_t last_dir;
	dir_t dir = dir_read(pos_read());
	
	
	if(dir == DOWN && dir != last_dir){
		move_arrow_down();
	}
	else if(dir == UP && dir != last_dir){
		move_arrow_up();
	}
	last_dir = dir;
}

void print_arrow()
{
	oled_write_data(0x18);
	oled_write_data(0x18);
	oled_write_data(0x7E);
	oled_write_data(0x3C);
	oled_write_data(0x18);
}

void clear_arrow()
{
	for(uint8_t i = 0; i < 5; i++) oled_write_data(0x00);
}

void move_arrow_up()
{
	if(arrow_on_line > FIRST_LINE_MENU && arrow_on_line <= num_options_in_menu)
	{
		oled_goto_line(arrow_on_line);
		oled_goto_column(0);
		clear_arrow();
		arrow_on_line--;
		oled_goto_line(arrow_on_line);
		oled_goto_column(0);
		print_arrow();
	}
}

void move_arrow_down()
{
	if(arrow_on_line >= FIRST_LINE_MENU && arrow_on_line < num_options_in_menu)
	{
		oled_goto_line(arrow_on_line);
		oled_goto_column(0);
		clear_arrow();
		arrow_on_line++;
		oled_goto_line(arrow_on_line);
		oled_goto_column(0);
		print_arrow();
	}
}

void enter()
{
	option_struct current_option = current_menu->submenu[arrow_on_line-1];
	(*current_option.callback)(current_option.callback_parameter);
}

void menu_init()
{
	main_menu.submenu[0].callback_parameter = &Sub_menu_1;
	main_menu.submenu[1].callback_parameter = &Sub_menu_2;
	Sub_menu_1.submenu[1].callback_parameter = &main_menu;
	Sub_menu_2.submenu[1].callback_parameter = &main_menu;
	update_menu(&main_menu);
}
