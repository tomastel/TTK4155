
#include "menu.h"
#include "../CAN/CANdrv.h"

static uint8_t num_options_in_menu;
static uint8_t arrow_on_line;
static menu_struct *current_menu;
uint8_t goal_limit = 5;
uint8_t score = 0;

CAN_msg CAN_msg_start_game = {
	.ID = 3,
	.length = 1,
	.message = {0}
};

menu_struct Sub_menu_2 = {
	.title = "OPTIONS",
	.submenu = {
		{ .option_name = "Increment 1", .callback = &increment_goal_limit },
		{ .option_name = "Decrement 1", .callback = &decrement_goal_limit },
		{ .option_name = "Back", .callback = &update_menu }
	},
	.options = 3
};

menu_struct Sub_menu_1 = {
	.title = "IN GAME",
	.submenu = {
		{ .option_name = "End game", .callback = &end_game }
	},
	.options = 1
};

menu_struct main_menu = {
	.title = "Main Menu",
	.submenu = {
		{ .option_name = "Start game", .callback = &start_game_menu},
		{ .option_name = "Options", .callback = &update_options}
	},
	.options = 2
};

void increment_score()
{
	uint8_t game_on = CAN_msg_start_game.message[0];
	if (game_on) {
		score ++;
		if (score >= goal_limit) {
			end_game();
		} else {
			start_game_menu(current_menu);
		}
			
	}
}

void end_game()
{
	update_menu(&main_menu);
	CAN_msg_start_game.message[0] = 0;
	CAN_send(CAN_msg_start_game);
}

void increment_goal_limit()
{
	goal_limit ++;
	if (goal_limit > 9) {
		goal_limit = 9;
	}
	update_options(current_menu);
}

void decrement_goal_limit()
{
	goal_limit --;
	if (goal_limit < 1) {
		goal_limit = 1;
	}
	update_options(current_menu);
}

void print_menu_page()
{
	char *menu_page_title = current_menu->title;
	oled_reset();
	oled_goto_line(0);
	oled_goto_column(40);
	print_oled(menu_page_title);
	
	for(uint8_t i = 0; i < current_menu->options; i++){
		char *option = current_menu->submenu[i].option_name;
		oled_goto_line(i+1);
		oled_goto_column(8);
		print_oled(option);
	}
	
	oled_pos(FIRST_LINE_MENU, 0);
	print_arrow();
	arrow_on_line = FIRST_LINE_MENU;
}

void start_game_menu (void *menu_page)
{
	menu_struct *temp_menu_page = menu_page;
	current_menu = temp_menu_page;
	num_options_in_menu = temp_menu_page->options;
	print_menu_page();
	
	oled_pos(num_options_in_menu + 3, 40);
	char *goals_scored = "Score: ";
	print_oled(goals_scored);
	
	//få info fra node 2
	char goals_limit = '0' + score;
	oled_print(goals_limit);
	
	uint8_t start_game_bit = CAN_msg_start_game.message[0];
	if (!start_game_bit) {
		score = 0;
		CAN_msg_start_game.message[0] = 1;
		CAN_send(CAN_msg_start_game);
	}
	
}

void update_menu(void *menu_page)
{	
	score = 0;
	menu_struct *temp_menu_page = menu_page;
	current_menu = temp_menu_page;
	num_options_in_menu = temp_menu_page->options;
	print_menu_page();
}

void update_options(void *menu_page)
{
	menu_struct *temp_menu_page = menu_page;
	current_menu = temp_menu_page;
	num_options_in_menu = temp_menu_page->options;
	print_menu_page();
	
	oled_pos(num_options_in_menu + 3, 24);
	char *goal_options = "Goal limit: ";
	print_oled(goal_options);
	
	char goals_limit = '0' + goal_limit;
	oled_print(goals_limit);
}

void menu_navigate()
{	
	static dir_t last_dir;
	dir_t dir = dir_read(pos_read());
	
	if(dir == DOWN && dir != last_dir) {
		move_arrow_down();
	}
	else if(dir == UP && dir != last_dir) {
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
	if(arrow_on_line > FIRST_LINE_MENU && arrow_on_line <= num_options_in_menu) {
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
	if(arrow_on_line >= FIRST_LINE_MENU && arrow_on_line < num_options_in_menu) {
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
	Sub_menu_1.submenu[0].callback_parameter = &main_menu;
	Sub_menu_2.submenu[2].callback_parameter = &main_menu;
	update_menu(&main_menu);
}
