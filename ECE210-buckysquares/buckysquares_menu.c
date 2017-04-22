// Name: buckysquares_menu.c
// Author: Winor Chen
// Description:	Implementation of library pertaining to general functions involved in
//							the user interface of Buckysquares.

/* Opens the main menu of Buckysquares where players can choose
 * which game mode (singleplayer or multiplayer) to play.
 *
 * Returns: integer flag corresponding to success (0) or failure (-1).
 */

#include "ece210_api.h"
#include "lab_buttons.h"
#include "buckysquares.h"

/* Resets the state of the screen by settings all pixels to black.
 */
void lcd_clear()
{
	ece210_lcd_draw_rectangle(0, 240, 0, 320, LCD_COLOR_BLACK);
}

/* Polls to see if input for the menu was received.
 *
 * Returns: choice selected.
 *					0 - none, stay at menu
 *					1 - singleplayer
 *					2 - multiplayer
 */
int update_menu(int choice)
{
	
	if(choice == 0 && ece210_ps2_read_position() == PS2_DOWN)
	{
		ece210_lcd_print_string("PLAY SINGLEPLAYER", 220, 200, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
		ece210_lcd_print_string("PLAY MULTIPLAYER", 220, 230, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
		choice = 1;
	}
	
	if(choice == 1 && ece210_ps2_read_position() == PS2_UP)
	{
		ece210_lcd_print_string("PLAY SINGLEPLAYER", 220, 200, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
		ece210_lcd_print_string("PLAY MULTIPLAYER", 220, 230, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
		choice = 0;
	}
	
	return choice;
}

/*
 *
 */
void singleplayer_menu()
{
	int next = -1;
	int choice = 0;
	int difficulty = 1;
	int old_difficulty = 1;
	int board_size = 0;
	int old_board_size = 0;
	
	char * text_difficulty = "Difficulty: Normal";
	char * text_board_size = "Board Size: Normal";
	
	lcd_clear();
	ece210_lcd_print_string("Singleplayer Setup...", 230, 20, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	ece210_lcd_print_string(text_difficulty, 220, 80, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
	ece210_lcd_print_string(text_board_size, 220, 100, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	ece210_lcd_print_string("(R) Play", 75, 300, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	ece210_lcd_print_string("(L) Back", 230, 300, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	
	while(next < 0)
	{
	
		if(choice == 0 && ece210_ps2_read_position() == PS2_LEFT) difficulty--;
		if(choice == 0 && ece210_ps2_read_position() == PS2_RIGHT) difficulty++;
		if(difficulty < 0) difficulty = 4; if(difficulty > 4) difficulty = 0;
		if(choice == 1 && ece210_ps2_read_position() == PS2_LEFT) board_size--;
		if(choice == 1 && ece210_ps2_read_position() == PS2_RIGHT) board_size++;
		if(board_size < 0) board_size = 1; if(board_size > 1) board_size = 0;
		
		switch(difficulty)
		{
			case 0:
				text_difficulty = "Difficulty: Easy";
				break;
			case 1:
				text_difficulty = "Difficulty: Normal";
				break;
			case 2:
				text_difficulty = "Difficulty: Hard";
				break;
			case 3:
				text_difficulty = "Difficulty: Very Hard";
				break;
			case 4:
				text_difficulty = "Difficulty: Divine";
				break;
		}
		
		switch(board_size)
		{
			case 0:
				text_board_size = "Board Size: Normal";
				board_size = 0;
				break;
			case 1:
				text_board_size = "Board Size: Large";
				board_size = 1;
				break;
		}
		
		if(old_difficulty != difficulty)
		{
			ece210_lcd_draw_rectangle(0, 240, 80, 20, LCD_COLOR_BLACK);
			ece210_lcd_print_string(text_difficulty, 220, 80, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
			old_difficulty = difficulty;
		}
		
		if(old_board_size != board_size)
		{
			ece210_lcd_draw_rectangle(0, 240, 100, 20, LCD_COLOR_BLACK);
			ece210_lcd_print_string(text_board_size, 220, 100, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
			old_board_size = board_size;
		}
		
		if(choice == 0 && ece210_ps2_read_position() == PS2_DOWN)
		{
			ece210_lcd_print_string(text_difficulty, 220, 80, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
			ece210_lcd_print_string(text_board_size, 220, 100, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
			choice = 1;
		}
	
		if(choice == 1 && ece210_ps2_read_position() == PS2_UP)
		{
			ece210_lcd_print_string(text_difficulty, 220, 80, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
			ece210_lcd_print_string(text_board_size, 220, 100, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
			choice = 0;
		}
		
		while(ece210_ps2_read_position() != PS2_CENTER);
		
		if(btn_right_pressed())
		{
			AlertButtons = 0;
			next = 1;
			launch_tetris_game(0, difficulty, board_size, 0, 0);
		}
		
		else if(btn_left_pressed())
		{
			AlertButtons = 0;
			next = 0;
		}
	}
}

void multiplayer_menu()
{
	lcd_clear();
	ece210_lcd_print_string("Multiplayer Setup...", 230, 20, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	ece210_lcd_print_string("Local ID:", 220, 80, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
	ece210_lcd_print_string("Remote ID:", 220, 100, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	ece210_lcd_print_string("Allow Bombarding: ", 220, 120, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	ece210_lcd_print_string("Sudden Death: ", 220, 140, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	ece210_lcd_print_string("(R) Start", 75, 300, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	ece210_lcd_print_string("(L) Back", 230, 300, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	
	while(!btn_down_pressed());
}

int prompt_menu()
{
	ece210_lcd_print_string("Welcome to...", 220, 40, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
	ece210_lcd_print_string("BUCKYSQUARES", 210, 60, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	ece210_lcd_print_string("PLAY SINGLEPLAYER", 220, 200, LCD_COLOR_CYAN, LCD_COLOR_BLUE2);
	ece210_lcd_print_string("PLAY MULTIPLAYER", 220, 230, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
	ece210_lcd_print_string("(R) Next", 75, 300, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
	int chosen = -1;
	int choice = 0;
	while(chosen < 0)
	{
		if(btn_right_pressed()) chosen = 1;
		choice = update_menu(choice);
		AlertButtons = 0;
	}
	return choice;
}

/* Tests to see if the board is currently connected to another player.
 *
 * Returns: integer flag corresponding to success (0) or failure (-1).
 */
int is_connected(int id)
{
	return -1;
}
